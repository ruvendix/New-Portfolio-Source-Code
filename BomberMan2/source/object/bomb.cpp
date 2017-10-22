/*
 * <작성 날짜>
 * 2017-10-14
 *
 * <파일 설명>
 * 폭탄 오브젝트를 구현합니다.
 * 플레이어가 폭탄을 사용하면 그 자리에서 설치됩니다.
 * 폭탄은 일정 시간이 지난 후에 폭발합니다.
 * 이때 폭발 범위가 다른 폭탄에 영향을 끼치면 그 폭탄도 같이 폭발합니다.
 * 폭탄이 폭발하면 폭발 이펙트가 생성되고 마찬가지로 일정 시간이 지난 뒤에 사라집니다.
 */

#include "bomb.h"

#include "../manager/collision_manager.h"
#include "../manager/effect_manager.h"
#include "../manager/game_manager.h"
#include "../manager/random_manager.h"
#include "../manager/time_manager.h"

const INT32 BOMB_NUM_INVALIDITY = -1;

namespace object
{

	INT32 Bomb::Initialize()
	{
		m_bombDropTime  = std::chrono::steady_clock::now();
		m_explosionTime = m_bombDropTime;

		CopyPos(&m_bombDirectionTable[static_cast<INT32>(OBJECT_DIRECTION::LEFT)], -1, 0);
		CopyPos(&m_bombDirectionTable[static_cast<INT32>(OBJECT_DIRECTION::UP)], 0, -1);
		CopyPos(&m_bombDirectionTable[static_cast<INT32>(OBJECT_DIRECTION::RIGHT)], +1, 0);
		CopyPos(&m_bombDirectionTable[static_cast<INT32>(OBJECT_DIRECTION::DOWN)], 0, +1);

		m_bChainExplosion = false;

		cmn::InitializeBoolArray(m_bChainExplosionDirection, BOMB_DIRECTION_MAX, false);

		return 0;
	}

	INT32 Bomb::Update()
	{
		mgr::TimeManager::ActivateManager().MeasureTimePoint(&m_explosionTime);

		// 폭탄이 설치된 후 BOMB_EXPLOSION_TIME만큼 시간이 지나면 폭발합니다.
		if (mgr::TimeManager::ActivateManager().CalculateTimeInterval(m_bombDropTime, m_explosionTime) > BOMB_EXPLOSION_TIME)
		{
#ifndef _NDEBUG
			//cmn::ShowMessageAutoNewLine("뻥~");
#endif
			return static_cast<INT32>(_Explode());
		}
		// 연쇄 폭발인 경우에는 시간과 무관하게 처리합니다.
		// 즉, 연쇄 폭발이 확정되면 그 위치에서 즉시 폭발합니다.
		else if (m_bChainExplosion)
		{
			return static_cast<INT32>(_Explode());
		}

		return 0;
	}

	INT32 Bomb::Render()
	{
		return 0;
	}

	INT32 Bomb::Release()
	{
		return 0;
	}

	BOMB_STATE Bomb::_Explode()
	{
		INT32 playerBombPower = mgr::GameManager::ActivateManager().getPlayerBombPower();

		BOMB_STATE bombState  = BOMB_STATE::EXPLOSION;

		// 두꺼운 벽과의 충돌 정보를 저장하기 위한 변수입니다.
		BOOL bArrHardWall[BOMB_DIRECTION_MAX];
		cmn::InitializeBoolArray(bArrHardWall, BOMB_DIRECTION_MAX, false);
		
		// 얇은 벽과의 충돌 정보를 저장하기 위한 변수입니다.
		BOOL bArrSoftWall[BOMB_DIRECTION_MAX];
		cmn::InitializeBoolArray(bArrSoftWall, BOMB_DIRECTION_MAX, false);
		
		// 폭발과의 충돌 정보를 저장하기 위한 변수입니다.
		BOOL bArrExplosionChain[BOMB_DIRECTION_MAX];
		cmn::InitializeBoolArray(bArrExplosionChain, BOMB_DIRECTION_MAX, false);

		for (INT32 i = 0; i < playerBombPower; ++i)
		{
			// 폭탄의 좌, 우, 위, 아래를 검사해서 컬리전 매니저에
			// 등록된 맵 오브젝트와 충돌했는지 검사합니다.
			for (INT32 j = 0; j < static_cast<INT32>(OBJECT_DIRECTION::END); ++j)
			{
				// 이미 폭발된 폭탄의 방향은 연산을 생략합니다.
				if (m_bChainExplosionDirection[j] == true)
				{
					continue;
				}

				Position2D explosionPos     = { 0, 0 };
				Position2D bombDirectionPos = { 0, 0 };

				// 폭탄의 폭발력만큼 방향을 더해서 폭발 좌표를 연산합니다.
				MultiplePos(&bombDirectionPos, m_bombDirectionTable[j], i + 1);
				AddPos(&explosionPos, m_nowPos, bombDirectionPos);

				// 폭발 지점이 맵 경계 안에 있는지 검사합니다.
				if (mgr::CollisionManager::ActivateManager().CheckBasePosExistInsidePos(explosionPos.x, explosionPos.y,
					MAP_START_BORDER_WIDTH, MAP_START_BORDER_HEIGHT, MAP_END_BORDER_WIDTH, MAP_END_BORDER_HEIGHT))
				{
					Position2D playerPos = mgr::GameManager::ActivateManager().getPlayerPos();

					// 좌, 위, 우, 아래 순으로 컬리전 매니저에 컬리전값을 등록합니다.
					mgr::GameManager::ActivateManager().EnrollMapObjectCollisionValue(&m_collisionValue, explosionPos);

					// 두꺼운 벽은 폭발되지 않습니다.
					if (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
						static_cast<INT32>(MAP_OBJECT_SHAPE::HARD_WALL)))
					{
						bArrHardWall[j] = true;
					}

					if (bArrHardWall[j] == false)
					{
						// 폭발 좌표를 이용해서 폭발 이펙트를 생성합니다.
						mgr::EffectManager::AcitvateInstance().CreateEffect(explosionPos, "※", EFFECT_TYPE::EXPLOSION);

						// 얇은 벽은 폭발됩니다.
						if (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
							static_cast<INT32>(MAP_OBJECT_SHAPE::SOFT_WALL)))
						{
							// 이미 폭발된 방향은 연산하지 않습니다.
							// 즉, 아이템도 등장하지 않습니다.
							if ( (bArrSoftWall[j] == false) &&
								 (bArrExplosionChain[j] == false) )
							{
								// 일정 확률에 따라 아이템이 등장합니다.
								_AppearItem(explosionPos);

								bArrSoftWall[j] = true;
							}
						}

						// 연쇄 폭발이 일어난다면 어떤 방향에서 폭발이 왔는지 확인합니다.
						// 예를 들어 아래에 폭탄이 있고 위에 있는 폭탄이 폭발했다면
						// 아래에 있는 폭탄은 위로 폭발되는 좌표를 연산하지 않아도 됩니다.
						if (bArrSoftWall[j] == false)
						{
							// 폭발 범위가 다른 폭탄을 건드렸다면 연쇄 폭발로 인정됩니다.
							// 폭탄이 어떤 폭탄을 건드렸는지 판단한 뒤에 게임 매니저를 통해 플레이어 정보에 등록합니다.
							if (_CheckExplosionChain(explosionPos, static_cast<OBJECT_DIRECTION>(j)))
							{
								bArrExplosionChain[j] = true;
							}

							// 플레이어가 폭발에 휘말리면 죽습니다.
							// 플레이어는 얇은 벽, 폭발에 맞았을 때만 죽습니다.
							// 폭탄의 위치, 폭발 방향에 영향을 받습니다.
							if ( (CheckSamePos(explosionPos, playerPos)) ||
								 (CheckSamePos(m_nowPos, playerPos)) )
							{
								bombState = BOMB_STATE::EXPLOSION_HIT_PLAYER;
							}
						}

						// 아이템이 폭발에 휘말리면 사라집니다.
						if (_CheckExplosionItem())
						{
							mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos(explosionPos, MAP_OBJECT_SHAPE::ROAD);
						}
					}
				}
			}
		}

		// 폭탄이 폭발하면 폭탄의 위치에도 폭발 이펙트를 생성해야 합니다.
		mgr::EffectManager::AcitvateInstance().CreateEffect(m_nowPos, "※", EFFECT_TYPE::EXPLOSION);

		return bombState;
	}

	void Bomb::_AppearItem(const Position2D& explosionPos) const
	{
		INT32 itemProbability = mgr::RandomManager::ActivateManager().GenerateIntRandomNumber(0, 100);

		// 등장 확률이 80%라면 0 ~ 80 안에 난수가 존재해야 합니다.
		// 다시 말하면 81 ~ 100은 제외되므로 이 범위 안에 난수가 존재한다면
		// 20% 확률에 당첨된 것과 같습니다. 따라서 확률 계산은 낮은 확률 -> 높은 확률 순서로 처리해야 합니다.
		//
		// 아이템이 등장할 확률은 70%입니다.
		if (itemProbability <= 70)
		{
			// 아이템이 종류별로 등장할 확률을 따로 구합니다.
			itemProbability = mgr::RandomManager::ActivateManager().GenerateIntRandomNumber(0, 100);

			if (itemProbability <= 20)
			{
				mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos(explosionPos, MAP_OBJECT_SHAPE::ITEM_WALL_PUSH);
			}
			else if (itemProbability <= 60)
			{
				mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos(explosionPos, MAP_OBJECT_SHAPE::ITEM_TRANSPARENCY);
			}
			else if (itemProbability <= 80)
			{
				mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos(explosionPos, MAP_OBJECT_SHAPE::ITEM_POWER);
			}
			// 아이템이 종류별로 등장할 확률이 100%가 아니므로 나머지 확률에 대해서도 처리해야 합니다.
			// 하지만 파워 아이템이 등장할 확률은 80%이므로 일반적으로는 아이템이 등장한다고 봐도 됩니다.
			else
			{
				mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos(explosionPos, MAP_OBJECT_SHAPE::ROAD);
			}
		}
		else
		{
			// 벽을 파괴했는데도 아이템이 등장하지 않을 수 있습니다.
			mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos(explosionPos, MAP_OBJECT_SHAPE::ROAD);
		}
	}

	BOOL Bomb::_CheckExplosionItem() const
	{
		if ( (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
			  static_cast<INT32>(MAP_OBJECT_SHAPE::ITEM_POWER))) ||
			 (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
			  static_cast<INT32>(MAP_OBJECT_SHAPE::ITEM_TRANSPARENCY))) ||
			 (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
			  static_cast<INT32>(MAP_OBJECT_SHAPE::ITEM_WALL_PUSH))) )
		{
			return true;
		}

		return false;
	}

	BOOL Bomb::_CheckExplosionChain(const Position2D& explosionPos, OBJECT_DIRECTION explosionDirection) const
	{
		if (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
			static_cast<INT32>(MAP_OBJECT_SHAPE::BOMB)) == false)
		{
			return false;
		}

		Bomb* pChainBomb = nullptr;

		// 폭발 좌표에 폭탄이 있는 게 확인되면 해당 위치에 있는 폭탄을 검색합니다.
		LIST<Bomb*> listBomb = mgr::GameManager::ActivateManager().getListBomb();
		for (Bomb* i : listBomb)
		{
			if (i != nullptr)
			{
				// 폭발 좌표에 폭탄이 있는지 검사합니다.
				if (CheckSamePos(explosionPos, i->getNowPos()))
				{
					pChainBomb = i;
					break;
				}
			}
		}

		OBJECT_DIRECTION chainExplosionDirection = OBJECT_DIRECTION::END;

		// 연쇄 폭발에 맞은 방향을 연산합니다.
		// 폭발 검사 순서는 좌, 위, 우, 아래이므로
		// 연쇄 폭발에 맞은 방향은 우, 아래, 좌, 위가 됩니다.
		switch (explosionDirection)
		{
		case OBJECT_DIRECTION::LEFT:
			chainExplosionDirection = OBJECT_DIRECTION::RIGHT;
			break;
		case OBJECT_DIRECTION::UP:
			chainExplosionDirection = OBJECT_DIRECTION::DOWN;
			break;
		case OBJECT_DIRECTION::RIGHT:
			chainExplosionDirection = OBJECT_DIRECTION::LEFT;
			break;
		case OBJECT_DIRECTION::DOWN:
			chainExplosionDirection = OBJECT_DIRECTION::UP;
			break;
		}

		pChainBomb->setExplosionChain(true);
		pChainBomb->setExplosionChainDirection(chainExplosionDirection, true);

		return true;
	}

} // namespace object end