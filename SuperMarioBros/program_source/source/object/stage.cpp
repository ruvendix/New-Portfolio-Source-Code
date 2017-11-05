/*
 * <제작 날짜>
 * 2017-10-25
 *
 * <파일 설명>
 * 스테이지의 구현입니다.
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

		m_cameraPos.x = m_pStageInfo->widthBorder / 2; // 스크롤 기준은 플레이어가 중간에 왔을 때입니다.
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

			// 스테이지의 출력 범위를 고정시킵니다.
			renderBeginY = m_pStageInfo->startPos.y - m_pStageInfo->heightBorderRenderBegin;

			// 플레이어의 출력 좌표도 고정시킵니다.
			et_math::setPosY(m_pStageInfo->heightBorderRenderBegin + 1, pPlayerInfo->getRenderPos());
		}

		for ( ; renderBeginY < renderEndY; ++renderBeginY)
		{
			INT32 renderBeginX = 0;
			INT32 renderEndX   = 0;

			// 플레이어의 x좌표가 카메라 기준 x좌표보다 작을 때는 스테이지를 스크롤하지 않습니다.
			if (pPlayerInfo->getNowPosX() < m_cameraPos.x)
			{
				renderBeginX = 0;
				renderEndX   = m_pStageInfo->widthBorder;
			}
			// 플레이어의 x좌표가 스테이지의 가로 길이 - 스테이지의 가로 경계 + 카메라 기준 x좌표보다
			// 커질 때는 스크롤하지 않습니다.
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
		printf("스테이지의 가로 길이 : %d\n", g_pStageMgr->getStage()->getStageInfo().width);
		printf("스테이지의 세로 길이 : %d\n", g_pStageMgr->getStage()->getStageInfo().height);
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
		// 불러올 스테이지 번호가 유효한 스테이지 번호인지 확인합니다.
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
		// 스테이지 매니저를 이용해서 가져온 스테이지 정보를
		// 이용해서 게임에 사용할 스테이지 크기만큼 동적할당합니다.
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

		// 플레이어의 위치를 기준으로 렌더링될 스테이지의 세로 부분의 좌표입니다.
		// 플레이어의 시작 위치를 기준으로 위로 몇 칸, 아래로 몇 칸만 렌더링됩니다.
		// 여기서 구한 렌더링 좌표는 말 그대로 렌더링을 위한 좌표이고, 플레이어를 따라다니는 카메라 좌표가 별도로 존재합니다.
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