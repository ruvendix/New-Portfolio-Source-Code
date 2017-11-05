/*
 * <제작 날짜>
 * 2017-11-03
 *
 * <파일 설명>
 * 몬스터의 구현입니다.
 * 현재는 몬스터가 이동만 합니다.
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
		m_pMonsterInfo->setShape("♠");
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

		// 다음 x좌표가 유효한 좌표인지 확인합니다.
		INT32 nextPosX = m_pMonsterInfo->getNowPosX() + m_pMonsterInfo->getDeltaDirection();
		if ( (cmn::CheckUnderIndex(nextPosX, 0)) ||
			 (cmn::CheckOverIndex(nextPosX, stageInfo.width - 1)) )
		{
			m_pMonsterInfo->ChangeDirection();
			m_pMonsterInfo->DecideDirection();

			// 스테이지 영역을 벗어나서 방향을 변경한 상태인데도
			// 변경된 다음 좌표에 벽돌 또는 아래에 아무것도 없다면 좌표를 유지합니다.
			if (_CheckExceptionTile(*m_pMonsterInfo->getNowPos()))
			{
				return;
			}
		}
		// 몬스터의 좌표가 스테이지 영역 안에 있을 때는
		// 양 옆의 다음 좌표에 어떤 형식의 타일이 있는지 확인합니다.
		else
		{
			bool bStopLeft  = false;
			bool bStopRight = false;

			// 이전 방향을 보존합니다.
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

			// 확인이 끝나면 이전 방향 정보로 복원합니다.
			m_pMonsterInfo->setDirection(direction);
			m_pMonsterInfo->DecideDirection();

			// 양쪽 다 벽돌 또는 아래에 아무것도 없다면 좌표를 유지합니다.
			if ( (bStopLeft) &&
				 (bStopRight) )
			{
				return;
			}
			// 둘 중 한쪽만 벽돌 또는 아래에 아무것도 없다면 방향을 변경합니다.
			else if ( (bStopLeft) ||
				      (bStopRight) )
			{
				// 양 옆에 벽돌 또는 아래에 아무것도 없다면
				// 바로 아래에 아무것도 없는지도 확인해야 합니다.
				// 그래야 해당 몬스터가 추락 중인지 아닌지를 알 수 있습니다.
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

		// 다음 좌표를 검사한 결과 결정된 방향을 적용해서 실제 좌표에 적용합니다.
		et_math::AddPosX(m_pMonsterInfo->getDeltaDirection(), m_pMonsterInfo->getNowPos());
	}

	void Monster::_DescendPos()
	{
		const StageInfo& stageInfo = g_pStageMgr->getStage()->getStageInfo();

		// 점프 상태가 아니므로 플레이어의 다음 y좌표로 스테이지 추락을 판단해야 합니다.
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