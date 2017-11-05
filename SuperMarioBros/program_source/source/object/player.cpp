/*
 * <제작 날짜>
 * 2017-10-28
 *
 * <파일 설명>
 * 플레이어의 기본 구현입니다.
 */

#include "object/player.h"

#include "manager_linker.h"

#include "object/player_info.h"
#include "object/stage.h"
#include "object/tile_info.h"

namespace object
{
	Player::Player()
	{
		m_pPlayerInfo = nullptr;
	}

	Player::~Player()
	{

	}

	OBJECT_STATE Player::Initialize()
	{
		m_pPlayerInfo = std::make_shared<PlayerInfo>();
		m_pPlayerInfo->InitializeInfo();
		return OBJECT_STATE::INIT_OBJECT_SUCCESS;
	}

	OBJECT_STATE Player::Update()
	{
		g_pUserInputMgr->InputKeyboard();
		g_pUserInputMgr->InputMouse();

		_MovePos();
		_DescendPosNotJump();
		_JumpPos();

		if (_CheckPlayerArriveGoal())
		{
			m_pPlayerInfo->setGoal(true);
			return OBJECT_STATE::UPDATE_OBJECT_SUCCESS;
		}

		_EatItem();
		_ShootBullet();

		return OBJECT_STATE::UPDATE_OBJECT_SUCCESS;
	}

	OBJECT_STATE Player::Render()
	{
		g_pSystemMgr->AdjustRenderingPos(*m_pPlayerInfo->getRenderPos());
		g_pSystemMgr->AdjustRenderColor(m_pPlayerInfo->getRenderColor());

		if (m_pPlayerInfo->getGrowth())
		{
			Position2D growthRenderPos = *m_pPlayerInfo->getRenderPos();

			if (growthRenderPos.y - 1 < 0)
			{
				growthRenderPos.y = m_pPlayerInfo->getNowPosY() + 1;
			}

			g_pSystemMgr->AdjustRenderingPos(growthRenderPos);
			printf("%s", m_pPlayerInfo->getDownShape());

			et_math::SubtractPosY(1, &growthRenderPos);
			g_pSystemMgr->AdjustRenderingPos(growthRenderPos);
			printf("%s", m_pPlayerInfo->getShape());
		}
		else
		{
			g_pSystemMgr->AdjustRenderingPos(*m_pPlayerInfo->getRenderPos());
			printf("%s", m_pPlayerInfo->getShape());
		}

#ifndef NDEBUG
		g_pSystemMgr->AdjustRenderColor(RENDERING_COLOR::LIGHT_WHITE);

		Position2D test = { 0, g_pStageMgr->getStage()->getStageInfo().heightBorderRenderBegin +
		g_pStageMgr->getStage()->getStageInfo().heightBorderRenderEnd + 9};
		g_pSystemMgr->AdjustRenderingPos(test);
		printf("플레이어의 시작 좌표(%d, %d)\n", g_pStageMgr->getStage()->getStageInfo().startPos.x,
			g_pStageMgr->getStage()->getStageInfo().startPos.y);
		printf("플레이어의 목표 좌표(%d, %d)\n", g_pStageMgr->getStage()->getStageInfo().endPos.x,
			g_pStageMgr->getStage()->getStageInfo().endPos.y);
		printf("플레이어의 현재 좌표(%d, %d)\n", m_pPlayerInfo->getNowPosX(), m_pPlayerInfo->getNowPosY());
		printf("플레이어의 출력 좌표(%d, %d)\n", m_pPlayerInfo->getRenderPosX(), m_pPlayerInfo->getRenderPosY());
#endif
		return OBJECT_STATE::RENDER_OBJECT_SUCCESS;
	}

	OBJECT_STATE Player::Release()
	{

		return OBJECT_STATE::RELEASE_OBJECT_SUCCESS;
	}

	void Player::_MovePos()
	{
		obj::Stage* pStage    = g_pStageMgr->getStage();
		StageInfo   stageInfo = pStage->getStageInfo();
		TileInfo*   pTileInfo = nullptr;

		if (g_pUserInputMgr->IsInputValue(KEY_W))
		{
			et_math::AddPosY(1, m_pPlayerInfo->getNowPos());
		}

		bool bInputLeft  = g_pUserInputMgr->IsInputValue(KEY_A);
		bool bInputRight = g_pUserInputMgr->IsInputValue(KEY_D);

		if ( (bInputLeft) ||
			 (bInputRight) )
		{
			if (bInputLeft)
			{
 				m_pPlayerInfo->setDirection(OBJECT_DIRECTION::LEFT);
			}
			else if (bInputRight)
			{
				m_pPlayerInfo->setDirection(OBJECT_DIRECTION::RIGHT);
			}

			m_pPlayerInfo->DecideDirection();

			et_math::AddPosX(m_pPlayerInfo->getDeltaDirection(), m_pPlayerInfo->getNowPos());

			if ( (cmn::CheckUnderIndex(m_pPlayerInfo->getNowPosX(), 0)) ||
				 (cmn::CheckOverIndex(m_pPlayerInfo->getNowPosX(), stageInfo.width - 1)) )
			{
				et_math::SubtractPosX(m_pPlayerInfo->getDeltaDirection(), m_pPlayerInfo->getNowPos());
			}

			pTileInfo = pStage->getTileInfo(*m_pPlayerInfo->getNowPos());
			if ( (pTileInfo->getTileType() == TILE_TYPE::BLOCK) ||
				 (_CheckGrowthCollision(0, -1, TILE_TYPE::BLOCK)) )
			{
				et_math::SubtractPosX(m_pPlayerInfo->getDeltaDirection(), m_pPlayerInfo->getNowPos());
			}
		}

		// 렌더링할 좌표를 따로 연산합니다.
		if (m_pPlayerInfo->getNowPosX() < g_pStageMgr->getStage()->getCameraPosX())
		{
			et_math::setPosX(m_pPlayerInfo->getNowPosX(), m_pPlayerInfo->getRenderPos());
			et_math::MultiplyPosX(2, m_pPlayerInfo->getRenderPos());
		}
		else if ( (m_pPlayerInfo->getNowPosX()) >=
			      (stageInfo.width - stageInfo.widthBorder + pStage->getCameraPosX()) )
		{
			INT32 fixX = m_pPlayerInfo->getNowPosX() - (stageInfo.width - stageInfo.widthBorder);
			et_math::setPosX(fixX, m_pPlayerInfo->getRenderPos());
			et_math::MultiplyPosX(2, m_pPlayerInfo->getRenderPos());
		}
		// 스테이지가 스크롤될 때는 카메라 기준 x좌표 - 1로 고정시킵니다.
		// 1을 빼는 이유는 스크롤되는 좌표가 카메라 기준 x좌표부터인데
		// 스크롤되기 전까지가 카메라 기준 x좌표 -1이기 때문입니다.
		else
		{
			INT32 scrollX = pStage->getCameraPosX() - 1;
			et_math::setPosX(scrollX, m_pPlayerInfo->getRenderPos());
			et_math::MultiplyPosX(2, m_pPlayerInfo->getRenderPos());
		}
	}

	void Player::_DescendPosNotJump()
	{
		// 점프 상태가 아닐 때만 처리합니다.
		if (m_pPlayerInfo->getJump())
		{
			m_pPlayerInfo->setDescent(false);
			return;
		}

		// 점프 상태가 아니므로 플레이어의 다음 y좌표로 스테이지 추락을 판단해야 합니다.
		if (m_pPlayerInfo->getNowPosY() + 1 >= g_pStageMgr->getStage()->getStageInfo().height)
		{
			m_pPlayerInfo->setFallDown(true);
			return;
		}

		m_pPlayerInfo->setDescent(false);
		_SyncRenderingPos();

		TileInfo* pTileInfo = g_pStageMgr->getStage()->getTileInfo(m_pPlayerInfo->getNowPosX(),
			m_pPlayerInfo->getNowPosY() + 1);

		if ( (pTileInfo->getTileType() == TILE_TYPE::EMPTY) ||
			 (pTileInfo->getTileType() == TILE_TYPE::ITEM_GROWTH) ||
			 (pTileInfo->getTileType() == TILE_TYPE::ITEM_SHOOT) ||
			 (pTileInfo->getTileType() == TILE_TYPE::COIN) )
		{
			et_math::AddPosY(1, m_pPlayerInfo->getNowPos());
			m_pPlayerInfo->setDescent(true);
		}
	}

	void Player::_JumpPos()
	{
		if (m_pPlayerInfo->getDescent())
		{
			return;
		}

		if (g_pUserInputMgr->IsInputValue(KEY_SPACE))
		{
			if ( (m_pPlayerInfo->getNowPosY() > 0) &&
				 (m_pPlayerInfo->getJump() == false) )
			{
				m_pPlayerInfo->setJump(true);
				m_pPlayerInfo->setJumpState(PLAYER_JUMP_STATE::UP);
				g_pSoundMgr->PlayOnSound("jump.wav");
			}
		}

		obj::Stage* pStage    = g_pStageMgr->getStage();
		StageInfo   stageInfo = pStage->getStageInfo();

		switch (m_pPlayerInfo->getJumpState())
		{
		case PLAYER_JUMP_STATE::UP:
			if (m_pPlayerInfo->getDeltaJump() <= MAX_PLAYER_JUMP)
			{
				// 점프를 하면 플레이어의 y좌표가 감소됩니다.
				et_math::SubtractPosY(1, m_pPlayerInfo->getNowPos());

				if (m_pPlayerInfo->getNowPosY() < 0)
				{
					et_math::setPosY(0, m_pPlayerInfo->getNowPos());
				}

				_SyncRenderingPos();

				TileInfo* pTileInfo = pStage->getTileInfo(
					m_pPlayerInfo->getNowPosX(), m_pPlayerInfo->getNowPosY());

				if ( (pTileInfo->getTileType() == TILE_TYPE::BLOCK) ||
					 (_CheckGrowthCollision(0, -1, TILE_TYPE::BLOCK)) )
				{
					g_pStageMgr->CreateItem(pTileInfo, m_pPlayerInfo->getGrowth());
					et_math::AddPosY(1, m_pPlayerInfo->getNowPos());

					_SyncRenderingPos();

					m_pPlayerInfo->AddScore(100);
					m_pPlayerInfo->setJumpState(PLAYER_JUMP_STATE::DOWN);
					g_pSoundMgr->PlayOnSound("break_block.wav");
				}
				else
				{
					m_pPlayerInfo->PlusDeltaJump();
				}
			}
			else
			{
				m_pPlayerInfo->setJumpState(PLAYER_JUMP_STATE::DOWN);
			}
			break;
		case PLAYER_JUMP_STATE::DOWN:
			m_pPlayerInfo->setDeltaJump(0);
			et_math::AddPosY(1, m_pPlayerInfo->getNowPos());

			// 점프 상태가 내려가는 경우일 때 스테이지를 벗어나는지 확인해야 합니다.
			// 스테이지의 세로 크기가 10이라면 인덱스는 0부터 시작하니까 끝 인덱스값은 9지만
			// 플레이어의 다음 진행 좌표로 판단하기 때문에 벽돌이 있는지는 9로 판단해야 합니다.
			// 따라서 9 다음인 10이 되면 스테이지를 벗어났다는 의미가 됩니다.
			if (m_pPlayerInfo->getNowPosY() >= stageInfo.height)
			{
				et_math::setPosY(stageInfo.height - 1, m_pPlayerInfo->getNowPos());
				m_pPlayerInfo->setFallDown(true);
				break;
			}

			_SyncRenderingPos();

			TileInfo* pTileInfo = pStage->getTileInfo(
				m_pPlayerInfo->getNowPosX(), m_pPlayerInfo->getNowPosY());

			if (pTileInfo->getTileType() == TILE_TYPE::BLOCK)
			{
				m_pPlayerInfo->InitializeJumpInfo();
				et_math::SubtractPosY(1, m_pPlayerInfo->getNowPos());

				_SyncRenderingPos();
			}
			break;
		}
	}

	void Player::_EatItem()
	{
		TileInfo* pTileInfo = g_pStageMgr->getStage()->getTileInfo(*m_pPlayerInfo->getNowPos());

		if (pTileInfo == nullptr)
		{
			return;
		}

		if ( (pTileInfo->getTileType() == TILE_TYPE::COIN) ||
			 (_CheckGrowthCollision(0, -1, TILE_TYPE::COIN)) )
		{
			g_pStageMgr->getStage()->ChangeTileInfo(*pTileInfo->getNowPos(), TILE_TYPE::EMPTY);
			m_pPlayerInfo->AddScore(200);

			if (m_pPlayerInfo->getGrowth())
			{
				Position2D growthPos = *m_pPlayerInfo->getNowPos();
				pTileInfo = g_pStageMgr->getStage()->getTileInfo(growthPos.x, growthPos.y - 1);
				g_pStageMgr->getStage()->ChangeTileInfo(*pTileInfo->getNowPos(), TILE_TYPE::EMPTY);
			}

			g_pSoundMgr->PlayOnSound("coin.wav");
		}
		else if ( (pTileInfo->getTileType() == TILE_TYPE::ITEM_GROWTH) ||
			      (_CheckGrowthCollision(0, -1, TILE_TYPE::ITEM_GROWTH)) )
		{
			g_pStageMgr->getStage()->ChangeTileInfo(*pTileInfo->getNowPos(), TILE_TYPE::EMPTY);
			m_pPlayerInfo->setGrowth(true);

			if (m_pPlayerInfo->getGrowth())
			{
				Position2D growthPos = *m_pPlayerInfo->getNowPos();
				pTileInfo = g_pStageMgr->getStage()->getTileInfo(growthPos.x, growthPos.y - 1);
				g_pStageMgr->getStage()->ChangeTileInfo(*pTileInfo->getNowPos(), TILE_TYPE::EMPTY);
			}

			g_pSoundMgr->PlayOnSound("growth.wav");
		}
		else if ( (pTileInfo->getTileType() == TILE_TYPE::ITEM_SHOOT) ||
			      (_CheckGrowthCollision(0, -1, TILE_TYPE::ITEM_SHOOT)) )
		{
			g_pStageMgr->getStage()->ChangeTileInfo(*pTileInfo->getNowPos(), TILE_TYPE::EMPTY);
			m_pPlayerInfo->setShoot(true);

			if (m_pPlayerInfo->getGrowth())
			{
				Position2D growthPos = *m_pPlayerInfo->getNowPos();
				pTileInfo = g_pStageMgr->getStage()->getTileInfo(growthPos.x, growthPos.y - 1);
				g_pStageMgr->getStage()->ChangeTileInfo(*pTileInfo->getNowPos(), TILE_TYPE::EMPTY);
			}

			g_pSoundMgr->PlayOnSound("growth.wav");
		}
	}

	void Player::_ShootBullet()
	{
		if (getPlayerInfo()->getShoot() == false)
		{
			return;
		}

		if (g_pUserInputMgr->IsInputValue(MOUSE_RBUTTON))
		{
			Position2D bulletPos = *m_pPlayerInfo->getNowPos();

			if (getPlayerInfo()->getGrowth())
			{
				et_math::SubtractPosY(1, &bulletPos);
			}

			g_pObjectMgr->CreateBullet(bulletPos, m_pPlayerInfo->getDirection());
			g_pSoundMgr->PlayOnSound("shoot.wav");
		}
	}

	bool Player::_CheckPlayerFallDown()
	{
		if (m_pPlayerInfo->getNowPosY() >= g_pStageMgr->getStage()->getStageInfo().height)
		{
			return true;
		}

		return false;
	}

	bool Player::_CheckPlayerArriveGoal()
	{
		if (et_math::CheckSamePos(g_pStageMgr->getStage()->getStageInfo().endPos,
			*m_pPlayerInfo->getNowPos()))
		{
			return true;
		}

		return false;
	}

	bool Player::_CheckGrowthCollision(INT32 dx, INT32 dy, TILE_TYPE tileType)
	{
		if (m_pPlayerInfo->getGrowth() == false)
		{
			return false;
		}

		TileInfo* pTileInfo = g_pStageMgr->getStage()->getTileInfo(m_pPlayerInfo->getNowPosX() + dx,
			m_pPlayerInfo->getNowPosY() + dy);

		if ( (pTileInfo != nullptr) &&
			 (pTileInfo->getTileType() == tileType) )
		{
			return true;
		}

		return false;
	}

	// 플레이어의 감소된 y좌표가 플레이어 위쪽 렌더링 크기보다 작으면 스테이지 렌더링 영역을 고정시킵니다.
	// 이때 플레이어의 y좌표와 플레이어의 렌더링 y좌표를 동기화시켜야 합니다.
	// 그래야 스테이지 렌더링 영역이 고정될 때 점프하는 플레이어를 출력시킬 수 있습니다.
	void Player::_SyncRenderingPos()
	{
		if (m_pPlayerInfo->getNowPosY() - g_pStageMgr->getStage()->getStageInfo().heightBorderRenderBegin < 0)
		{
			et_math::setPosY(m_pPlayerInfo->getNowPosY(), m_pPlayerInfo->getRenderPos());
		}
		else
		{
			et_math::setPosY(g_pStageMgr->getStage()->getStageInfo().heightBorderRenderBegin,
				m_pPlayerInfo->getRenderPos());
		}
	}

} // namespace object end