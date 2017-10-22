/*
 * <작성 날짜>
 * 2017-10-12
 *
 * <파일 설명>
 * 플레이어를 구현합니다.
 * 플레이어는 사용자가 직접 조작할 수 있는 오브젝트입니다.
 */

#include "player.h"

#include "../manager/collision_manager.h"
#include "../manager/debug_manager.h"
#include "../manager/game_manager.h"
#include "../manager/user_input_manager.h"

#include "../object/item/power.h"
#include "../object/item/transparency.h"
#include "../object/item/wall_push.h"

namespace object
{

	INT32 Player::Initialize()
	{
		CopyPos(&m_nowPos, 1, 1);     // 시작 위치
		CopyPos(&m_oldPos, m_nowPos); // 이전 위치

		m_bombPower = 1;
		m_bombDropCount = 0;

		m_bIsDropBomb       = true;
		m_bIsTransparency   = false;
		m_bIsWallPush       = false;
		m_bTransparencyMode = false;
		m_bIsWallPushMode   = false;
		m_bIsWallCollision  = false;

		//cmn::InitializeBoolArray(m_bEmptyArrBomb, sizeof(m_bEmptyArrBomb), true);
		cmn::InitializeArray(&m_arrItem);

		return 0;
	}

	INT32 Player::Update()
	{
		INT32 playerUpdateResult = 0;

		// 키보드에서 입력을 받습니다.
		mgr::UserInputManager::ActivateManager().InputKeyboard();

		Position2D movePos;
		cmn::InitializeMemory(&movePos);

		_CalculateMovePos(&movePos);

		// 현재 좌표를 이전 좌표에 보존합니다.
		CopyPos(&m_oldPos, m_nowPos);

		// 투명화 및 벽 밀기 적용은 여기서 결정합니다.
		_MovePlayer(&movePos);

		// 현재 갖고 있는 아이템 중에서 실제로 적용 가능한 아이템만 적용합니다.
		_ApplyItemAbility();

		// 플레이어의 다음 위치를 연산한 뒤에 벽 밀기를 적용합니다.
		if (m_bIsWallPush == true)
		{
			_PushWall();
		}

		// 폭탄 설치
		_DropBomb();

		// 폭탄 폭발
		playerUpdateResult = _ExplosionBomb();

		for (INT32 i = 0; i < PLAYER_ITEM_MAX_COUNT; ++i)
		{
			if (m_arrItem[i] != nullptr)
			{
				m_arrItem[i]->Update();
			}
		}

		return playerUpdateResult;
	}

	INT32 Player::Render()
	{
#ifndef _NDEBUG
		printf("플레이어 x 좌표 : %d\n", m_nowPos.x);
		printf("플레이어 y 좌표 : %d\n", m_nowPos.y);
		printf("벽 충돌 상태    : %s\n", (m_bIsWallCollision == true) ? ("충돌") : ("충돌 안함"));
#endif

		cmn::ShowMessageAutoNewLine("---------------------------------------------------------");

		// 맵의 위치에 플레이어를 출력하는 게 맞지만
		// 현재는 좌표를 조정하지 않으므로 맵에서 처리합니다.

		for (Bomb* i : m_listBomb)
		{
			if (i != nullptr)
			{
				i->Render();
			}
		}

		for (item::ItemBase* i : m_arrItem)
		{
			if (i != nullptr)
			{
				i->Render();
			}
		}

		return 0;
	}

	INT32 Player::Release()
	{
		for (LIST<Bomb*>::iterator i = m_listBomb.begin(); i != m_listBomb.end(); )
		{
			if (*i != nullptr)
			{
				cmn::SafeDelete(&(*i));
				m_listBomb.erase(i++);
			}
			else
			{
				++i;
			}
		}
		m_listBomb.clear();

		for (INT32 i = 0; i < PLAYER_ITEM_MAX_COUNT; ++i)
		{
			if (m_arrItem[i] != nullptr)
			{
				cmn::SafeDelete(&m_arrItem[i]);
			}
		}

		return 0;
	}

	void Player::EnrollChainBomb(INT32 bombNum, const OBJECT_DIRECTION& explosionDirection)
	{
		/*for ()
		{
		}*/

		//m_arrBomb[bombNum]->setExplosionChain(true);
		//m_arrBomb[bombNum]->setExplosionChainDirection(explosionDirection, true);
	}

	void Player::_CalculateMovePos(Position2D* pMovePos)
	{
		if (mgr::UserInputManager::ActivateManager().IsInputKey(KEY_W))
		{
			pMovePos->y = -1;
		}
		else if (mgr::UserInputManager::ActivateManager().IsInputKey(KEY_A))
		{
			pMovePos->x = -1;
		}
		else if (mgr::UserInputManager::ActivateManager().IsInputKey(KEY_S))
		{
			pMovePos->y = +1;
		}
		else if (mgr::UserInputManager::ActivateManager().IsInputKey(KEY_D))
		{
			pMovePos->x = +1;
		}
	}

	void Player::_AddItemDummy()
	{

	}

	void Player::_AddItemPower()
	{
		// 아이템을 먹으면 해당 위치는 길로 변경됩니다.
		mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos(m_nowPos, MAP_OBJECT_SHAPE::ROAD);

		if (m_bombPower >= MAX_PLAYER_BOMB_POWER)
		{
			return;
		}

		// 파워 증가 아이템을 먹으면 이후부터는 파워만 증가시킵니다.
		if (m_arrItem[static_cast<INT32>(PLAYER_HAVE_ITEM::POWER)] == nullptr)
		{
			item::ItemBase* pItem = new item::ItemPower;
			assert(pItem != nullptr);
			pItem->Initialize();

			m_arrItem[static_cast<INT32>(PLAYER_HAVE_ITEM::POWER)] = pItem;
		}

		m_bombPower++;
	}

	void Player::_AddItemTransparency()
	{
		mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos(m_nowPos, MAP_OBJECT_SHAPE::ROAD);

		if (m_bIsTransparency == true)
		{
			return;
		}

		if (m_arrItem[static_cast<INT32>(PLAYER_HAVE_ITEM::TRANSPARENCY)] == nullptr)
		{
			item::ItemBase* pItem = new item::ItemTransparency;
			assert(pItem != nullptr);
			pItem->Initialize();

			m_arrItem[static_cast<INT32>(PLAYER_HAVE_ITEM::TRANSPARENCY)] = pItem;
		}

		m_bIsTransparency   = true;
		m_bTransparencyMode = true;
	}

	void Player::_AddItemWallPush()
	{
		mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos(m_nowPos, MAP_OBJECT_SHAPE::ROAD);

		if (m_bIsWallPush == true)
		{
			return;
		}

		if (m_arrItem[static_cast<INT32>(PLAYER_HAVE_ITEM::WALL_PUSH)] == nullptr)
		{
			item::ItemBase* pItem = new item::ItemWallPush;
			assert(pItem != nullptr);
			pItem->Initialize();

			m_arrItem[static_cast<INT32>(PLAYER_HAVE_ITEM::WALL_PUSH)] = pItem;
		}

		m_bIsWallPush     = true;
		m_bIsWallPushMode = false;
	}

	void Player::_ApplyItemAbility()
	{
		// 조건을 여러 개 따질 경우에는 가장 까다로운 조건부터 검사하는 게 좋습니다.
		// 가장 간단한 조건부터 검사하게 되면 해당 조건만 참이되어야 할 때 검사할 조건이 두 개 이상이라면
		// 해당되는 조건 중 하나만 참이되어도 참으로 결정되기 때문입니다.
		// 따라서 가장 까다로운 조건부터 검사하면서 단계를 내려가는 게 좋습니다.
		// 하지만 여기에서는 조건이 하나이므로 내부적으로는 Short Curcuit Evaluation만 작동됩니다.

		// 투명화, 벽 밀기를 보유하고 있을 때
		if ( (m_bIsTransparency == true) &&
			 (m_bIsWallPush == true) )
		{
			// 벽 밀기가 발동된 경우라면 투명화는 발동하지 않습니다.
			(m_bIsWallPushMode == true) ? (m_bTransparencyMode = false) : (m_bTransparencyMode = true);
		}
	}

	INT32 Player::_ExplosionBomb()
	{
		BOMB_STATE bombState = BOMB_STATE::NONE;

		for (LIST<Bomb*>::iterator i = m_listBomb.begin(); i != m_listBomb.end(); )
		{
			if (*i != nullptr)
			{
				bombState = static_cast<BOMB_STATE>((*i)->Update());

				if ( (bombState == BOMB_STATE::EXPLOSION) ||
					 (bombState == BOMB_STATE::EXPLOSION_HIT_PLAYER) )
				{
					// 폭탄이 터지면 폭탄 설치 가능
					if (m_bIsDropBomb == false)
					{
						m_bIsDropBomb = true;
					}

					// 폭탄이 폭발되면 해당 위치를 길로 변경합니다.
					mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos((*i)->getNowPos(), MAP_OBJECT_SHAPE::ROAD);

					cmn::SafeDelete(&(*i));
					m_listBomb.erase(i++);
					m_bombDropCount--;

					// 폭탄을 먼저 길로 변경한 뒤에 폭발에 휘말린 플레이어를 처리해야 합니다.
					// 순서가 정해진 함수 호출은 좋은 프로그래밍이 아니지만...
					// 오브젝트끼리 관계가 많아지다 보면 이런 경우가 흔합니다...
					if (bombState == BOMB_STATE::EXPLOSION_HIT_PLAYER)
					{
						return static_cast<INT32>(PLAYER_STATE::DIE_BOMB);
					}
				}
				else
				{
					++i;
				}
			}
		}

		return 0;
	}

	BOOL Player::_CheckCollisionMapObject()
	{
		// 두꺼운 벽, 얇은 벽과의 충돌 검사입니다.
		if ( (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue, 
			  static_cast<INT32>(MAP_OBJECT_SHAPE::HARD_WALL))) ||
			 (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue, 
			  static_cast<INT32>(MAP_OBJECT_SHAPE::SOFT_WALL))) )
		{
			m_bIsWallCollision = true;
			return true;
		}

		// 폭탄과의 충돌 검사입니다.
		if (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
			static_cast<INT32>(MAP_OBJECT_SHAPE::BOMB)))
		{
			m_bIsWallCollision = false;
			return true;
		}

		m_bIsWallCollision = false;
		return false;
	}

	BOOL Player::_PushWall()
	{
		if (mgr::UserInputManager::ActivateManager().IsInputKey(KEY_Y))
		{
			// 투명화 발동 중이면서 벽에 충돌한 상태는 벽 위에 있는 상태를 의미합니다.
			// 이럴 때는 벽을 밀 수 없습니다.
			if ( (m_bTransparencyMode == true) &&
				 (m_bIsWallCollision == true) )
			{
				return false;
			}

			m_bIsWallPushMode = !m_bIsWallPushMode;
		}

		// 벽 밀기 상태가 활성화되었고 플레이어가 벽에 충돌했을 때만 벽을 밀 수 있습니다.
		if ( (m_bIsWallPushMode == false) ||
			 (m_bIsWallCollision == false) )
		{
			return false;
		}

		// "현재 좌표 - 이전 좌표"의 변화량으로 벽을 밀 방향을 구합니다.
		Position2D deltaPos = { 0, 0 }; // 수학에서는 두 값의 차이를 델타값이라고 합니다.
		SubtractPos(&deltaPos, m_nowPos, m_oldPos);

		OBJECT_DIRECTION wallPushDirection = OBJECT_DIRECTION::END;

		// "현재 x좌표 - 이전 x좌표"가 +1일 때는 오른쪽으로 이동된 상태입니다.
		if (deltaPos.x == +1)
		{
			wallPushDirection = OBJECT_DIRECTION::RIGHT;
		}
		// "현재 x좌표 - 이전 x좌표"가 -1일 때는 왼쪽으로 이동된 상태입니다.
		else if (deltaPos.x == -1)
		{
			wallPushDirection = OBJECT_DIRECTION::LEFT;
		}
		// "현재 y좌표 - 이전 y좌표"가 +1일 때는 아래로 이동된 상태입니다.
		else if (deltaPos.y == +1)
		{
			wallPushDirection = OBJECT_DIRECTION::DOWN;
		}
		// "현재 y좌표 - 이전 y좌표"가 - 1일 때는 위로 이동된 상태입니다.
		else if (deltaPos.x == -1)
		{
			wallPushDirection = OBJECT_DIRECTION::UP;
		}
		
		// 자식 형식에 부모 형식을 넣는 것을 "다운 캐스팅"이라고 합니다.
		// 이미 부모 형식에 동적 바인딩된 형식이 자식 형식이라면 안전한 캐스팅이지만
		// 부모 형식으로 동적 바인딩된 상태에서 다운 캐스팅을 하면 위험합니다.
		// 즉, 업 캐스팅을 한 후에 다운 캐스팅을 해야 합니다.
		// 이처럼 다운 캐스팅은 위험을 동반하므로 신중하게 사용해야 합니다.
		// 다운 캐스팅을 사용하지 않으려면 구조 자체를 변경해야 합니다.
		// 예를 들면 부모 클래스에 AdjustItemData(INT32 itemData)를 정의하고 자식이 오버라이딩해서 호출하는 방법이 있습니다.
		//
		// 다운 캐스팅을 도와주는 연산자는 dynamic_cast입니다.
		// 이 연산자는 RTTI(Run Time Type Information)를 활성화시킨 상태에서 사용해야 합니다.
		// dynamic_cast는 실패하면 nullptr을 반환하므로 assert()에 이용할 수 있습니다.
		item::ItemWallPush* pItem = 
			dynamic_cast<item::ItemWallPush*>(m_arrItem[static_cast<INT32>(PLAYER_HAVE_ITEM::WALL_PUSH)]);
		assert(pItem != nullptr);

		// dynamic_cast의 결과가 nullptr이면 함수를 종료해서 이후의 연산을 생략합니다.
		if (pItem == nullptr)
		{
			return false;
		}

		pItem->setWallPushDirection(wallPushDirection);

		// 벽이 밀릴 방향을 구했으니 이제 벽이 밀릴 좌표를 구해야 합니다.
		Position2D pushPos = { 0, 0 };
		AddPos(&pushPos, m_nowPos, deltaPos);

		// 컬리전 매니저에 등록된 이전 오브젝트값을 보존합니다.
		// 그래야 벽을 밀 수 없을 때 이전 값으로 복원할 수 있습니다.
		INT32 collisonValue = m_collisionValue;

		// 컬리전 매니저에 벽이 밀릴 좌표에 있는 오브젝트값을 등록합니다.
		mgr::GameManager::ActivateManager().EnrollMapObjectCollisionValue(&m_collisionValue, pushPos);

		// 벽이 밀릴 좌표에 있는 오브젝트가 길, 아이템일 때만 벽을 밀 수 있음
		if ( (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
			  static_cast<INT32>(MAP_OBJECT_SHAPE::ROAD))) ||
			 (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
			  static_cast<INT32>(MAP_OBJECT_SHAPE::ITEM_POWER))) ||
			 (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
			  static_cast<INT32>(MAP_OBJECT_SHAPE::ITEM_TRANSPARENCY))) ||
			 (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
			  static_cast<INT32>(MAP_OBJECT_SHAPE::ITEM_WALL_PUSH))) )
		{
			// 벽을 밀게 되면 이전 좌표에 있는 오브젝트를 길로 변경합니다.
			mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos(pushPos, static_cast<MAP_OBJECT_SHAPE>(collisonValue));
			mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos(m_nowPos, MAP_OBJECT_SHAPE::ROAD);

			// 여기서 플레이어의 이전 좌표로 복원하면 제자리에서 벽만 밀게 됩니다.
			//CopyPos(&m_nowPos, m_oldPos);

			return true;
		}
		// 벽을 밀 수 없다면 이전 값으로 복원합니다.
		else
		{
			CopyPos(&m_nowPos, m_oldPos);
			mgr::GameManager::ActivateManager().EnrollMapObjectCollisionValue(&m_collisionValue, m_nowPos);
		}

		return false;
	}

	INT32 Player::_MovePlayer(Position2D* pMovePos)
	{
		m_nowPos.x += pMovePos->x;
		m_nowPos.y += pMovePos->y;

		// 게임 매니저를 이용해서 플레이어 위치에 있는 맵 오브젝트를 컬리전 매니저를 통해 컬리전값에 등록합니다.
		mgr::GameManager::ActivateManager().EnrollMapObjectCollisionValue(&m_collisionValue, m_nowPos);

		// 다음 이동 좌표를 계산합니다.
		// CheckBasePointExistInsidePoint()의 반대는 CheckBasePointNotExistOutsidePoint()입니다.
		// "내부에 있는 점"이라는 말은 "외부에 있는 점"이 아니라는 말과 같습니다.
		if (mgr::CollisionManager::ActivateManager().CheckBasePosExistInsidePos(m_nowPos.x, m_nowPos.y,
			MAP_START_BORDER_WIDTH, MAP_START_BORDER_HEIGHT, MAP_END_BORDER_WIDTH, MAP_END_BORDER_HEIGHT))
		{
			// 두꺼운 벽, 얇은 벽, 폭탄에 대한 충돌 검사입니다.
			if (_CheckCollisionMapObject())
			{
				// 벽에 충돌한 상태를 따로 구분합니다.
				// 충돌은 폭탄에 충돌한 경우도 있기 때문입니다.
				// 투명화와 벽 밀기 둘 다 벽 충돌 상태를 알아야 적용할 수 있습니다.
				if (m_bIsWallCollision == true)
				{
					// 투명화가 발동된 경우입니다.
					if (m_bTransparencyMode == true)
					{
						return static_cast<INT32>(PLAYER_STATE::MOVE_TRANSPARENCY);
					}
					// 벽 밀기가 발동된 경우입니다.
					else if (m_bIsWallPushMode == true)
					{
						return static_cast<INT32>(PLAYER_STATE::MOVE_WALL_PUSH);
					}
				}

				// 투명화, 벽 밀기가 발동된 게 아니라면 이전 좌표로 복원합니다.
				CopyPos(&m_nowPos, m_oldPos);
			}
			else
			{
				// 아이템에 대한 충돌 검사입니다.
				_AddItem();
			}
		}
		else
		{
			// 맵의 경계를 벗어나면 이전 좌표로 복원합니다.
			CopyPos(&m_nowPos, m_oldPos);
		}

		return 0;
	}

	INT32 Player::_DropBomb()
	{
		if (mgr::UserInputManager::ActivateManager().IsInputKey(KEY_T))
		{
			if (m_bombDropCount >= PLAYER_BOMB_MAX_COUNT)
			{
				m_bIsDropBomb = false;
				return static_cast<INT32>(PLAYER_STATE::CANNOT_DROP_BOMB_MAX);
			}

			// 투명화가 발동된 상태에서 벽이나 폭탄 위에 있으면 폭탄을 설치할 수 없습니다.
			if (m_bIsTransparency)
			{
				if (_CheckCollisionMapObject())
				{
					return static_cast<INT32>(PLAYER_STATE::CANNOT_DROP_BOMB_TRANSPARENCY);
				}
			}

			Bomb* pBomb = new Bomb;
			assert(pBomb != nullptr);

			pBomb->Initialize();
			pBomb->setNowPos(m_nowPos); // 플레이어의 위치에 폭탄을 설치합니다.

			for (Bomb* i : m_listBomb)
			{
				if (i != nullptr)
				{
					if (CheckSamePos(pBomb->getNowPos(), i->getNowPos()))
					{
						return static_cast<INT32>(PLAYER_STATE::CANNOT_DROP_BOMB_OVERLAP);
					}
				}
			}

			// 폭탄이 설치 가능한지 검사합니다.
			if (m_listBomb.size() <= PLAYER_BOMB_MAX_COUNT)
			{
				m_listBomb.push_back(pBomb);
				m_bombDropCount++;
				
				// 폭탄을 맵 오브젝트에 등록합니다.
				mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos(m_nowPos, MAP_OBJECT_SHAPE::BOMB);

				return static_cast<INT32>(PLAYER_STATE::DROP_BOMB);
			}
		}

		return 0;
	}

	INT32 Player::_AddItem()
	{
		// 콜백을 이용하기 위해 함수 포인터를 저장합니다.
		std::function<void()> addItem = std::bind(&Player::_AddItemDummy, this);

		if (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
			static_cast<INT32>(MAP_OBJECT_SHAPE::ITEM_POWER)))
		{
			addItem = std::bind(&Player::_AddItemPower, this);
		}
		else if (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
			static_cast<INT32>(MAP_OBJECT_SHAPE::ITEM_TRANSPARENCY)))
		{
			addItem = std::bind(&Player::_AddItemTransparency, this);
		}
		else if (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
			static_cast<INT32>(MAP_OBJECT_SHAPE::ITEM_WALL_PUSH)))
		{
			addItem = std::bind(&Player::_AddItemWallPush, this);
		}

		// 각 조건에 따라 바인딩된 콜백 함수가 호출됩니다.
		addItem();

		return 0;
	}

} // namespac object end