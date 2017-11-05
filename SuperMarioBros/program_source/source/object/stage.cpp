/*
 * <���� ��¥>
 * 2017-10-25
 *
 * <���� ����>
 * ���������� �����Դϴ�.
 */

#include "object/stage.h"

#include "manager_linker.h"

#include "object/bullet.h"
#include "object/monster.h"
#include "object/player.h"
#include "object/player_info.h"
#include "object/tile_info.h"

namespace object
{

	Stage::Stage()
	{
		m_pStageInfo = nullptr;
		m_ppBoard    = nullptr;
	}

	OBJECT_STATE Stage::Initialize()
	{
		g_pTimeMgr->MeasureTimePoint(g_pStageMgr->getStartLimitTime());

		_LoadStage(g_pStageMgr->getNowStage());
		_BindData();

		m_cameraPos.x = m_pStageInfo->widthBorder / 2; // ��ũ�� ������ �÷��̾ �߰��� ���� ���Դϴ�.
		m_cameraPos.y = m_pStageInfo->heightBorder;

		return OBJECT_STATE::INIT_OBJECT_SUCCESS;
	}

	OBJECT_STATE Stage::Update()
	{
		g_pTimeMgr->MeasureTimePoint(g_pStageMgr->getCurrentLimitTime());
		return OBJECT_STATE::UPDATE_OBJECT_SUCCESS;
	}

	OBJECT_STATE Stage::Render()
	{
		obj::PlayerInfo* pPlayerInfo = g_pObjectMgr->getPlayer()->getPlayerInfo();

		INT32 renderBeginY = pPlayerInfo->getNowPosY() - m_pStageInfo->heightBorderRenderBegin;
		INT32 renderEndY   = pPlayerInfo->getNowPosY() + m_pStageInfo->heightBorderRenderEnd;

		if (renderBeginY < 0)
		{
			renderBeginY = 0;
		}

		if (renderEndY > m_pStageInfo->height)
		{
			renderEndY = m_pStageInfo->height;

			// ���������� ��� ������ ������ŵ�ϴ�.
			renderBeginY = m_pStageInfo->startPos.y - m_pStageInfo->heightBorderRenderBegin;

			// �÷��̾��� ��� ��ǥ�� ������ŵ�ϴ�.
			et_math::setPosY(m_pStageInfo->heightBorderRenderBegin + 1, pPlayerInfo->getRenderPos());
		}

		for ( ; renderBeginY < renderEndY; ++renderBeginY)
		{
			INT32 renderBeginX = 0;
			INT32 renderEndX   = 0;

			// �÷��̾��� x��ǥ�� ī�޶� ���� x��ǥ���� ���� ���� ���������� ��ũ������ �ʽ��ϴ�.
			if (pPlayerInfo->getNowPosX() < m_cameraPos.x)
			{
				renderBeginX = 0;
				renderEndX   = m_pStageInfo->widthBorder;
			}
			// �÷��̾��� x��ǥ�� ���������� ���� ���� - ���������� ���� ��� + ī�޶� ���� x��ǥ����
			// Ŀ�� ���� ��ũ������ �ʽ��ϴ�.
			else if ( (pPlayerInfo->getNowPosX()) >=
				      (m_pStageInfo->width - m_pStageInfo->widthBorder + m_cameraPos.x) )
			{
				renderBeginX = m_pStageInfo->width - m_pStageInfo->widthBorder;
				renderEndX   = m_pStageInfo->width;
			}
			else
			{
				renderBeginX = pPlayerInfo->getNowPosX() - m_cameraPos.x + 1;
				renderEndX   = pPlayerInfo->getNowPosX() + m_cameraPos.x + 1;
			}

			for ( ; renderBeginX < renderEndX; ++renderBeginX)
			{
				g_pSystemMgr->AdjustRenderColor(m_ppBoard[renderBeginY][renderBeginX].getRenderColor());
				
				INT32 objectIndex = -1;
				if (g_pObjectMgr->CheckBulletRendering(renderBeginX, renderBeginY, &objectIndex))
				{
					assert(objectIndex != -1);
					if (objectIndex != -1)
					{
						g_pObjectMgr->RenderBullet(objectIndex);
					}
				}
				else if (g_pObjectMgr->CheckMonsterRendering(renderBeginX, renderBeginY, &objectIndex))
				{
					assert(objectIndex != -1);
					if (objectIndex != -1)
					{
						g_pObjectMgr->RenderMonster(objectIndex);
					}
				}
				else
				{
					printf("%s", m_ppBoard[renderBeginY][renderBeginX].getShape());
				}
			}

			printf("\n");
		}

#ifndef NDEBUG
		g_pSystemMgr->AdjustRenderColor(RENDERING_COLOR::LIGHT_WHITE);

		Position2D test = { 0, getStageInfo().heightBorderRenderBegin +
			getStageInfo().heightBorderRenderEnd + 6 };
		g_pSystemMgr->AdjustRenderingPos(test);
		printf("���������� ���� ���� : %d\n", g_pStageMgr->getStage()->getStageInfo().width);
		printf("���������� ���� ���� : %d\n", g_pStageMgr->getStage()->getStageInfo().height);
#endif

		return OBJECT_STATE::RENDER_OBJECT_SUCCESS;
	}

	OBJECT_STATE Stage::Release()
	{	
		for (INT32 i = 0; i < m_pStageInfo->height; ++i)
		{
			cmn::SafeArrayDelete(&m_ppBoard[i]);
		}

		delete[] m_ppBoard;
		m_ppBoard = nullptr;

		return OBJECT_STATE::RELEASE_OBJECT_SUCCESS;
	}

	OBJECT_STATE Stage::_LoadStage(INT32 stageIdx)
	{
		// �ҷ��� �������� ��ȣ�� ��ȿ�� �������� ��ȣ���� Ȯ���մϴ�.
		bool bInvalidStageCount = (stageIdx <= 0) || (stageIdx > g_pStageMgr->getStageCount());
		assert(bInvalidStageCount != true);
		if (bInvalidStageCount == true)
		{
			return OBJECT_STATE::INVALID_OBJECT;
		}

		m_pStageInfo = g_pStageMgr->getStageInfo(stageIdx);
		g_pFileMgr->OpenFileStream(m_pStageInfo->name, "rt");

		_AllocateBoard(m_pStageInfo->width, m_pStageInfo->height);

		for (INT32 i = 0; i < m_pStageInfo->height; ++i)
		{
			for (INT32 j = 0; j < m_pStageInfo->width; ++j)
			{
				INT32 readData = 0;
				g_pFileMgr->ReadFile(&readData, 1);

				if (readData == '\n')
				{
					--j;
					continue;
				}

				m_ppBoard[i][j].setTileType(static_cast<TILE_TYPE>(readData - '0'));
				et_math::setPos(j, i, m_ppBoard[i][j].getNowPos());

				if (m_ppBoard[i][j].getTileType() == TILE_TYPE::MONSTER)
				{
					m_ppBoard[i][j].setTileType(TILE_TYPE::EMPTY);
					g_pObjectMgr->CreateMonster(*m_ppBoard[i][j].getNowPos());
				}
			}
		}

		g_pFileMgr->CloseFileStream();

		return OBJECT_STATE::LOAD_OBJECT_SUCCESS;
	}

	void Stage::_AllocateBoard(INT32 width, INT32 height)
	{
		// �������� �Ŵ����� �̿��ؼ� ������ �������� ������
		// �̿��ؼ� ���ӿ� ����� �������� ũ�⸸ŭ �����Ҵ��մϴ�.
		m_ppBoard = new TileInfo*[height];
		for (INT32 i = 0; i < height; ++i)
		{
			m_ppBoard[i] = new TileInfo[width];
		}
	}

	void Stage::_BindData()
	{
		for (INT32 i = 0; i < m_pStageInfo->height; ++i)
		{
			for (INT32 j = 0; j < m_pStageInfo->width; ++j)
			{
				TILE_TYPE tileType = m_ppBoard[i][j].getTileType();

				if (tileType == TILE_TYPE::START)
				{
					m_pStageInfo->startPos = { j, i };
				}
				else if (tileType == TILE_TYPE::GOAL)
				{
					m_pStageInfo->endPos = { j, i };
				}

				INT32 shapeIndex = static_cast<INT32>(tileType);
				m_ppBoard[i][j].setShape(g_tileShapeTable[shapeIndex]);
				m_ppBoard[i][j].setRenderColor(static_cast<RENDERING_COLOR>(shapeIndex));

				et_math::setPos(j, i, m_ppBoard[i][j].getNowPos());
			}
		}

		// �÷��̾��� ��ġ�� �������� �������� ���������� ���� �κ��� ��ǥ�Դϴ�.
		// �÷��̾��� ���� ��ġ�� �������� ���� �� ĭ, �Ʒ��� �� ĭ�� �������˴ϴ�.
		// ���⼭ ���� ������ ��ǥ�� �� �״�� �������� ���� ��ǥ�̰�, �÷��̾ ����ٴϴ� ī�޶� ��ǥ�� ������ �����մϴ�.
		m_pStageInfo->heightBorderRenderEnd = m_pStageInfo->height - m_pStageInfo->startPos.y;
	}

	void Stage::ChangeTileInfo(INT32 x, INT32 y, const TILE_TYPE& tileType)
	{
		TileInfo* pTileInfo = getTileInfo(x, y);
		pTileInfo->setTileType(tileType);
		pTileInfo->setShape(g_tileShapeTable[static_cast<INT32>(tileType)]);
	}

	void Stage::ChangeTileInfo(const Position2D& tilePos, const TILE_TYPE& tileType)
	{
		TileInfo* pTileInfo = getTileInfo(tilePos.x, tilePos.y);
		pTileInfo->setTileType(tileType);
		pTileInfo->setShape(g_tileShapeTable[static_cast<INT32>(tileType)]);
	}

	TileInfo* Stage::getTileInfo(INT32 x, INT32 y)
	{
		bool bVaildIndexX = cmn::CheckValidIndex(x, 0, getStageInfo().width - 1);
		bool bVaildIndexY = cmn::CheckValidIndex(y, 0, getStageInfo().height - 1);

		if ( (bVaildIndexX == false) ||
			 (bVaildIndexY == false) )
		{
			return nullptr;
		}

		return &m_ppBoard[y][x];
	}

	TileInfo * Stage::getTileInfo(const Position2D & tilePos)
	{
		bool bVaildIndexX = cmn::CheckValidIndex(tilePos.x, 0, getStageInfo().width - 1);
		bool bVaildIndexY = cmn::CheckValidIndex(tilePos.y, 0, getStageInfo().height - 1);

		if ((bVaildIndexX == false) ||
			(bVaildIndexY == false))
		{
			return nullptr;
		}

		return &m_ppBoard[tilePos.y][tilePos.x];
	}

} // namespace object end