/*
 * <�ۼ� ��¥>
 * 2017-10-12
 *
 * <���� ����>
 * �÷��̾ �����մϴ�.
 * �÷��̾�� ����ڰ� ���� ������ �� �ִ� ������Ʈ�Դϴ�.
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
		CopyPos(&m_nowPos, 1, 1);     // ���� ��ġ
		CopyPos(&m_oldPos, m_nowPos); // ���� ��ġ

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

		// Ű���忡�� �Է��� �޽��ϴ�.
		mgr::UserInputManager::ActivateManager().InputKeyboard();

		Position2D movePos;
		cmn::InitializeMemory(&movePos);

		_CalculateMovePos(&movePos);

		// ���� ��ǥ�� ���� ��ǥ�� �����մϴ�.
		CopyPos(&m_oldPos, m_nowPos);

		// ����ȭ �� �� �б� ������ ���⼭ �����մϴ�.
		_MovePlayer(&movePos);

		// ���� ���� �ִ� ������ �߿��� ������ ���� ������ �����۸� �����մϴ�.
		_ApplyItemAbility();

		// �÷��̾��� ���� ��ġ�� ������ �ڿ� �� �б⸦ �����մϴ�.
		if (m_bIsWallPush == true)
		{
			_PushWall();
		}

		// ��ź ��ġ
		_DropBomb();

		// ��ź ����
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
		printf("�÷��̾� x ��ǥ : %d\n", m_nowPos.x);
		printf("�÷��̾� y ��ǥ : %d\n", m_nowPos.y);
		printf("�� �浹 ����    : %s\n", (m_bIsWallCollision == true) ? ("�浹") : ("�浹 ����"));
#endif

		cmn::ShowMessageAutoNewLine("---------------------------------------------------------");

		// ���� ��ġ�� �÷��̾ ����ϴ� �� ������
		// ����� ��ǥ�� �������� �����Ƿ� �ʿ��� ó���մϴ�.

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
		// �������� ������ �ش� ��ġ�� ��� ����˴ϴ�.
		mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos(m_nowPos, MAP_OBJECT_SHAPE::ROAD);

		if (m_bombPower >= MAX_PLAYER_BOMB_POWER)
		{
			return;
		}

		// �Ŀ� ���� �������� ������ ���ĺ��ʹ� �Ŀ��� ������ŵ�ϴ�.
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
		// ������ ���� �� ���� ��쿡�� ���� ��ٷο� ���Ǻ��� �˻��ϴ� �� �����ϴ�.
		// ���� ������ ���Ǻ��� �˻��ϰ� �Ǹ� �ش� ���Ǹ� ���̵Ǿ�� �� �� �˻��� ������ �� �� �̻��̶��
		// �ش�Ǵ� ���� �� �ϳ��� ���̵Ǿ ������ �����Ǳ� �����Դϴ�.
		// ���� ���� ��ٷο� ���Ǻ��� �˻��ϸ鼭 �ܰ踦 �������� �� �����ϴ�.
		// ������ ���⿡���� ������ �ϳ��̹Ƿ� ���������δ� Short Curcuit Evaluation�� �۵��˴ϴ�.

		// ����ȭ, �� �б⸦ �����ϰ� ���� ��
		if ( (m_bIsTransparency == true) &&
			 (m_bIsWallPush == true) )
		{
			// �� �бⰡ �ߵ��� ����� ����ȭ�� �ߵ����� �ʽ��ϴ�.
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
					// ��ź�� ������ ��ź ��ġ ����
					if (m_bIsDropBomb == false)
					{
						m_bIsDropBomb = true;
					}

					// ��ź�� ���ߵǸ� �ش� ��ġ�� ��� �����մϴ�.
					mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos((*i)->getNowPos(), MAP_OBJECT_SHAPE::ROAD);

					cmn::SafeDelete(&(*i));
					m_listBomb.erase(i++);
					m_bombDropCount--;

					// ��ź�� ���� ��� ������ �ڿ� ���߿� �ָ��� �÷��̾ ó���ؾ� �մϴ�.
					// ������ ������ �Լ� ȣ���� ���� ���α׷����� �ƴ�����...
					// ������Ʈ���� ���谡 �������� ���� �̷� ��찡 ���մϴ�...
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
		// �β��� ��, ���� ������ �浹 �˻��Դϴ�.
		if ( (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue, 
			  static_cast<INT32>(MAP_OBJECT_SHAPE::HARD_WALL))) ||
			 (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue, 
			  static_cast<INT32>(MAP_OBJECT_SHAPE::SOFT_WALL))) )
		{
			m_bIsWallCollision = true;
			return true;
		}

		// ��ź���� �浹 �˻��Դϴ�.
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
			// ����ȭ �ߵ� ���̸鼭 ���� �浹�� ���´� �� ���� �ִ� ���¸� �ǹ��մϴ�.
			// �̷� ���� ���� �� �� �����ϴ�.
			if ( (m_bTransparencyMode == true) &&
				 (m_bIsWallCollision == true) )
			{
				return false;
			}

			m_bIsWallPushMode = !m_bIsWallPushMode;
		}

		// �� �б� ���°� Ȱ��ȭ�Ǿ��� �÷��̾ ���� �浹���� ���� ���� �� �� �ֽ��ϴ�.
		if ( (m_bIsWallPushMode == false) ||
			 (m_bIsWallCollision == false) )
		{
			return false;
		}

		// "���� ��ǥ - ���� ��ǥ"�� ��ȭ������ ���� �� ������ ���մϴ�.
		Position2D deltaPos = { 0, 0 }; // ���п����� �� ���� ���̸� ��Ÿ���̶�� �մϴ�.
		SubtractPos(&deltaPos, m_nowPos, m_oldPos);

		OBJECT_DIRECTION wallPushDirection = OBJECT_DIRECTION::END;

		// "���� x��ǥ - ���� x��ǥ"�� +1�� ���� ���������� �̵��� �����Դϴ�.
		if (deltaPos.x == +1)
		{
			wallPushDirection = OBJECT_DIRECTION::RIGHT;
		}
		// "���� x��ǥ - ���� x��ǥ"�� -1�� ���� �������� �̵��� �����Դϴ�.
		else if (deltaPos.x == -1)
		{
			wallPushDirection = OBJECT_DIRECTION::LEFT;
		}
		// "���� y��ǥ - ���� y��ǥ"�� +1�� ���� �Ʒ��� �̵��� �����Դϴ�.
		else if (deltaPos.y == +1)
		{
			wallPushDirection = OBJECT_DIRECTION::DOWN;
		}
		// "���� y��ǥ - ���� y��ǥ"�� - 1�� ���� ���� �̵��� �����Դϴ�.
		else if (deltaPos.x == -1)
		{
			wallPushDirection = OBJECT_DIRECTION::UP;
		}
		
		// �ڽ� ���Ŀ� �θ� ������ �ִ� ���� "�ٿ� ĳ����"�̶�� �մϴ�.
		// �̹� �θ� ���Ŀ� ���� ���ε��� ������ �ڽ� �����̶�� ������ ĳ����������
		// �θ� �������� ���� ���ε��� ���¿��� �ٿ� ĳ������ �ϸ� �����մϴ�.
		// ��, �� ĳ������ �� �Ŀ� �ٿ� ĳ������ �ؾ� �մϴ�.
		// ��ó�� �ٿ� ĳ������ ������ �����ϹǷ� �����ϰ� ����ؾ� �մϴ�.
		// �ٿ� ĳ������ ������� �������� ���� ��ü�� �����ؾ� �մϴ�.
		// ���� ��� �θ� Ŭ������ AdjustItemData(INT32 itemData)�� �����ϰ� �ڽ��� �������̵��ؼ� ȣ���ϴ� ����� �ֽ��ϴ�.
		//
		// �ٿ� ĳ������ �����ִ� �����ڴ� dynamic_cast�Դϴ�.
		// �� �����ڴ� RTTI(Run Time Type Information)�� Ȱ��ȭ��Ų ���¿��� ����ؾ� �մϴ�.
		// dynamic_cast�� �����ϸ� nullptr�� ��ȯ�ϹǷ� assert()�� �̿��� �� �ֽ��ϴ�.
		item::ItemWallPush* pItem = 
			dynamic_cast<item::ItemWallPush*>(m_arrItem[static_cast<INT32>(PLAYER_HAVE_ITEM::WALL_PUSH)]);
		assert(pItem != nullptr);

		// dynamic_cast�� ����� nullptr�̸� �Լ��� �����ؼ� ������ ������ �����մϴ�.
		if (pItem == nullptr)
		{
			return false;
		}

		pItem->setWallPushDirection(wallPushDirection);

		// ���� �и� ������ �������� ���� ���� �и� ��ǥ�� ���ؾ� �մϴ�.
		Position2D pushPos = { 0, 0 };
		AddPos(&pushPos, m_nowPos, deltaPos);

		// �ø��� �Ŵ����� ��ϵ� ���� ������Ʈ���� �����մϴ�.
		// �׷��� ���� �� �� ���� �� ���� ������ ������ �� �ֽ��ϴ�.
		INT32 collisonValue = m_collisionValue;

		// �ø��� �Ŵ����� ���� �и� ��ǥ�� �ִ� ������Ʈ���� ����մϴ�.
		mgr::GameManager::ActivateManager().EnrollMapObjectCollisionValue(&m_collisionValue, pushPos);

		// ���� �и� ��ǥ�� �ִ� ������Ʈ�� ��, �������� ���� ���� �� �� ����
		if ( (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
			  static_cast<INT32>(MAP_OBJECT_SHAPE::ROAD))) ||
			 (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
			  static_cast<INT32>(MAP_OBJECT_SHAPE::ITEM_POWER))) ||
			 (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
			  static_cast<INT32>(MAP_OBJECT_SHAPE::ITEM_TRANSPARENCY))) ||
			 (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
			  static_cast<INT32>(MAP_OBJECT_SHAPE::ITEM_WALL_PUSH))) )
		{
			// ���� �а� �Ǹ� ���� ��ǥ�� �ִ� ������Ʈ�� ��� �����մϴ�.
			mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos(pushPos, static_cast<MAP_OBJECT_SHAPE>(collisonValue));
			mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos(m_nowPos, MAP_OBJECT_SHAPE::ROAD);

			// ���⼭ �÷��̾��� ���� ��ǥ�� �����ϸ� ���ڸ����� ���� �а� �˴ϴ�.
			//CopyPos(&m_nowPos, m_oldPos);

			return true;
		}
		// ���� �� �� ���ٸ� ���� ������ �����մϴ�.
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

		// ���� �Ŵ����� �̿��ؼ� �÷��̾� ��ġ�� �ִ� �� ������Ʈ�� �ø��� �Ŵ����� ���� �ø������� ����մϴ�.
		mgr::GameManager::ActivateManager().EnrollMapObjectCollisionValue(&m_collisionValue, m_nowPos);

		// ���� �̵� ��ǥ�� ����մϴ�.
		// CheckBasePointExistInsidePoint()�� �ݴ�� CheckBasePointNotExistOutsidePoint()�Դϴ�.
		// "���ο� �ִ� ��"�̶�� ���� "�ܺο� �ִ� ��"�� �ƴ϶�� ���� �����ϴ�.
		if (mgr::CollisionManager::ActivateManager().CheckBasePosExistInsidePos(m_nowPos.x, m_nowPos.y,
			MAP_START_BORDER_WIDTH, MAP_START_BORDER_HEIGHT, MAP_END_BORDER_WIDTH, MAP_END_BORDER_HEIGHT))
		{
			// �β��� ��, ���� ��, ��ź�� ���� �浹 �˻��Դϴ�.
			if (_CheckCollisionMapObject())
			{
				// ���� �浹�� ���¸� ���� �����մϴ�.
				// �浹�� ��ź�� �浹�� ��쵵 �ֱ� �����Դϴ�.
				// ����ȭ�� �� �б� �� �� �� �浹 ���¸� �˾ƾ� ������ �� �ֽ��ϴ�.
				if (m_bIsWallCollision == true)
				{
					// ����ȭ�� �ߵ��� ����Դϴ�.
					if (m_bTransparencyMode == true)
					{
						return static_cast<INT32>(PLAYER_STATE::MOVE_TRANSPARENCY);
					}
					// �� �бⰡ �ߵ��� ����Դϴ�.
					else if (m_bIsWallPushMode == true)
					{
						return static_cast<INT32>(PLAYER_STATE::MOVE_WALL_PUSH);
					}
				}

				// ����ȭ, �� �бⰡ �ߵ��� �� �ƴ϶�� ���� ��ǥ�� �����մϴ�.
				CopyPos(&m_nowPos, m_oldPos);
			}
			else
			{
				// �����ۿ� ���� �浹 �˻��Դϴ�.
				_AddItem();
			}
		}
		else
		{
			// ���� ��踦 ����� ���� ��ǥ�� �����մϴ�.
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

			// ����ȭ�� �ߵ��� ���¿��� ���̳� ��ź ���� ������ ��ź�� ��ġ�� �� �����ϴ�.
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
			pBomb->setNowPos(m_nowPos); // �÷��̾��� ��ġ�� ��ź�� ��ġ�մϴ�.

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

			// ��ź�� ��ġ �������� �˻��մϴ�.
			if (m_listBomb.size() <= PLAYER_BOMB_MAX_COUNT)
			{
				m_listBomb.push_back(pBomb);
				m_bombDropCount++;
				
				// ��ź�� �� ������Ʈ�� ����մϴ�.
				mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos(m_nowPos, MAP_OBJECT_SHAPE::BOMB);

				return static_cast<INT32>(PLAYER_STATE::DROP_BOMB);
			}
		}

		return 0;
	}

	INT32 Player::_AddItem()
	{
		// �ݹ��� �̿��ϱ� ���� �Լ� �����͸� �����մϴ�.
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

		// �� ���ǿ� ���� ���ε��� �ݹ� �Լ��� ȣ��˴ϴ�.
		addItem();

		return 0;
	}

} // namespac object end