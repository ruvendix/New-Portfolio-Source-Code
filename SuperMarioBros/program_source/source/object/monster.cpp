/*
 * <���� ��¥>
 * 2017-11-03
 *
 * <���� ����>
 * ������ �����Դϴ�.
 * ����� ���Ͱ� �̵��� �մϴ�.
 */

#include "object/monster.h"

#include "manager_linker.h"
#include "object/object_base_info.h"
#include "object/player.h"
#include "object/player_info.h"
#include "object/stage.h"
#include "object/tile_info.h"

namespace object
{

	Monster::Monster()
	{
		m_pMonsterInfo = nullptr;
	}

	Monster::~Monster()
	{

	}

	OBJECT_STATE Monster::Initialize()
	{
		m_pMonsterInfo = std::make_shared<ObjectBaseInfo>();
		assert(m_pMonsterInfo != nullptr);

		m_pMonsterInfo->setDeltaDirection(-1);
		m_pMonsterInfo->setDirection(OBJECT_DIRECTION::LEFT);
		m_pMonsterInfo->setShape("��");
		m_pMonsterInfo->setRenderColor(RENDERING_COLOR::INTENSITY_RED);

		m_bFallDown = false;

		return OBJECT_STATE::INIT_OBJECT_SUCCESS;
	}

	OBJECT_STATE Monster::Update()
	{
		if (m_pMonsterInfo->getCollisionState())
		{
			return OBJECT_STATE::UPDATE_OBJECT_DELETE;
		}

		_MovePos();
		_DescendPos();
		_CheckPlayerCollsion();

		if (m_bFallDown)
		{
			return OBJECT_STATE::UPDATE_OBJECT_DELETE;
		}

		return OBJECT_STATE::UPDATE_OBJECT_SUCCESS;
	}

	OBJECT_STATE Monster::Render()
	{
		g_pSystemMgr->AdjustRenderColor(m_pMonsterInfo->getRenderColor());
		printf("%s", m_pMonsterInfo->getShape());
		return OBJECT_STATE::RENDER_OBJECT_SUCCESS;
	}

	OBJECT_STATE Monster::Release()
	{
		return OBJECT_STATE::RELEASE_OBJECT_SUCCESS;
	}

	void Monster::_MovePos()
	{
		if (m_bFallDown == true)
		{
			return;
		}

		const StageInfo& stageInfo = g_pStageMgr->getStage()->getStageInfo();

		// ���� x��ǥ�� ��ȿ�� ��ǥ���� Ȯ���մϴ�.
		INT32 nextPosX = m_pMonsterInfo->getNowPosX() + m_pMonsterInfo->getDeltaDirection();
		if ( (cmn::CheckUnderIndex(nextPosX, 0)) ||
			 (cmn::CheckOverIndex(nextPosX, stageInfo.width - 1)) )
		{
			m_pMonsterInfo->ChangeDirection();
			m_pMonsterInfo->DecideDirection();

			// �������� ������ ����� ������ ������ �����ε���
			// ����� ���� ��ǥ�� ���� �Ǵ� �Ʒ��� �ƹ��͵� ���ٸ� ��ǥ�� �����մϴ�.
			if (_CheckExceptionTile(*m_pMonsterInfo->getNowPos()))
			{
				return;
			}
		}
		// ������ ��ǥ�� �������� ���� �ȿ� ���� ����
		// �� ���� ���� ��ǥ�� � ������ Ÿ���� �ִ��� Ȯ���մϴ�.
		else
		{
			bool bStopLeft  = false;
			bool bStopRight = false;

			// ���� ������ �����մϴ�.
			OBJECT_DIRECTION direction = m_pMonsterInfo->getDirection();

			m_pMonsterInfo->setDirection(OBJECT_DIRECTION::LEFT);
			m_pMonsterInfo->DecideDirection();
			if (_CheckExceptionTile(*m_pMonsterInfo->getNowPos()))
			{
				bStopLeft = true;
			}

			m_pMonsterInfo->setDirection(OBJECT_DIRECTION::RIGHT);
			m_pMonsterInfo->DecideDirection();
			if (_CheckExceptionTile(*m_pMonsterInfo->getNowPos()))
			{
				bStopRight = true;
			}

			// Ȯ���� ������ ���� ���� ������ �����մϴ�.
			m_pMonsterInfo->setDirection(direction);
			m_pMonsterInfo->DecideDirection();

			// ���� �� ���� �Ǵ� �Ʒ��� �ƹ��͵� ���ٸ� ��ǥ�� �����մϴ�.
			if ( (bStopLeft) &&
				 (bStopRight) )
			{
				return;
			}
			// �� �� ���ʸ� ���� �Ǵ� �Ʒ��� �ƹ��͵� ���ٸ� ������ �����մϴ�.
			else if ( (bStopLeft) ||
				      (bStopRight) )
			{
				// �� ���� ���� �Ǵ� �Ʒ��� �ƹ��͵� ���ٸ�
				// �ٷ� �Ʒ��� �ƹ��͵� �������� Ȯ���ؾ� �մϴ�.
				// �׷��� �ش� ���Ͱ� �߶� ������ �ƴ����� �� �� �ֽ��ϴ�.
				obj::TileInfo* pTileInfo = g_pStageMgr->getStage()->getTileInfo(m_pMonsterInfo->getNowPosX(),
					m_pMonsterInfo->getNowPosY() + 1);
				if ( (pTileInfo != nullptr) &&
					 (pTileInfo->getTileType() == TILE_TYPE::EMPTY) )
				{
					return;
				}

				m_pMonsterInfo->ChangeDirection();
				m_pMonsterInfo->DecideDirection();
			}
			else
			{
				obj::TileInfo* pTileInfo = g_pStageMgr->getStage()->getTileInfo(m_pMonsterInfo->getNowPosX(),
					m_pMonsterInfo->getNowPosY() + 1);
				if ( (pTileInfo != nullptr) &&
					 (pTileInfo->getTileType() == TILE_TYPE::EMPTY) )
				{
					return;
				}
			}
		}

		// ���� ��ǥ�� �˻��� ��� ������ ������ �����ؼ� ���� ��ǥ�� �����մϴ�.
		et_math::AddPosX(m_pMonsterInfo->getDeltaDirection(), m_pMonsterInfo->getNowPos());
	}

	void Monster::_DescendPos()
	{
		const StageInfo& stageInfo = g_pStageMgr->getStage()->getStageInfo();

		// ���� ���°� �ƴϹǷ� �÷��̾��� ���� y��ǥ�� �������� �߶��� �Ǵ��ؾ� �մϴ�.
		if (m_pMonsterInfo->getNowPosY() + 1 >= stageInfo.height)
		{
			m_bFallDown = true;
			return;
		}

		TileInfo* pTileInfo = g_pStageMgr->getStage()->getTileInfo(m_pMonsterInfo->getNowPosX(),
			m_pMonsterInfo->getNowPosY() + 1);

		if (pTileInfo->getTileType() == TILE_TYPE::EMPTY)
		{
			et_math::AddPosY(1, m_pMonsterInfo->getNowPos());
		}
	}

	bool Monster::_CheckExceptionTile(const Position2D& pos)
	{
		Position2D nextPos = pos;

		et_math::AddPosX(m_pMonsterInfo->getDeltaDirection(), &nextPos);
		obj::TileInfo* pTileInfo = g_pStageMgr->getStage()->getTileInfo(nextPos);
		if ( (pTileInfo != nullptr) && 
			 (pTileInfo->getTileType() == TILE_TYPE::BLOCK) )
		{
			return true;
		}

		et_math::AddPosY(1, &nextPos);
		pTileInfo = g_pStageMgr->getStage()->getTileInfo(nextPos);
		if ( (pTileInfo != nullptr) && 
			 (pTileInfo->getTileType() == TILE_TYPE::EMPTY) )
		{
			return true;
		}

		return false;
	}

	bool Monster::_CheckPlayerCollsion()
	{
		obj::PlayerInfo* pPlayerInfo = g_pObjectMgr->getPlayer()->getPlayerInfo();

		if (et_math::CheckSamePos(*m_pMonsterInfo->getNowPos(), *pPlayerInfo->getNowPos()))
		{
			if (pPlayerInfo->getGrowth())
			{
				pPlayerInfo->setGrowth(false);
				g_pSoundMgr->PlayOnSound("damage.wav");
			}
			else
			{
				pPlayerInfo->setShape("  ");
				pPlayerInfo->setCollisionState(true);
			}

			return true;
		}

		return false;
	}

} // namespace object end