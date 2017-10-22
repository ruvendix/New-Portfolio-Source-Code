/*
 * <�ۼ� ��¥>
 * 2017-10-14
 *
 * <���� ����>
 * ��ź ������Ʈ�� �����մϴ�.
 * �÷��̾ ��ź�� ����ϸ� �� �ڸ����� ��ġ�˴ϴ�.
 * ��ź�� ���� �ð��� ���� �Ŀ� �����մϴ�.
 * �̶� ���� ������ �ٸ� ��ź�� ������ ��ġ�� �� ��ź�� ���� �����մϴ�.
 * ��ź�� �����ϸ� ���� ����Ʈ�� �����ǰ� ���������� ���� �ð��� ���� �ڿ� ������ϴ�.
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

		// ��ź�� ��ġ�� �� BOMB_EXPLOSION_TIME��ŭ �ð��� ������ �����մϴ�.
		if (mgr::TimeManager::ActivateManager().CalculateTimeInterval(m_bombDropTime, m_explosionTime) > BOMB_EXPLOSION_TIME)
		{
#ifndef _NDEBUG
			//cmn::ShowMessageAutoNewLine("��~");
#endif
			return static_cast<INT32>(_Explode());
		}
		// ���� ������ ��쿡�� �ð��� �����ϰ� ó���մϴ�.
		// ��, ���� ������ Ȯ���Ǹ� �� ��ġ���� ��� �����մϴ�.
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

		// �β��� ������ �浹 ������ �����ϱ� ���� �����Դϴ�.
		BOOL bArrHardWall[BOMB_DIRECTION_MAX];
		cmn::InitializeBoolArray(bArrHardWall, BOMB_DIRECTION_MAX, false);
		
		// ���� ������ �浹 ������ �����ϱ� ���� �����Դϴ�.
		BOOL bArrSoftWall[BOMB_DIRECTION_MAX];
		cmn::InitializeBoolArray(bArrSoftWall, BOMB_DIRECTION_MAX, false);
		
		// ���߰��� �浹 ������ �����ϱ� ���� �����Դϴ�.
		BOOL bArrExplosionChain[BOMB_DIRECTION_MAX];
		cmn::InitializeBoolArray(bArrExplosionChain, BOMB_DIRECTION_MAX, false);

		for (INT32 i = 0; i < playerBombPower; ++i)
		{
			// ��ź�� ��, ��, ��, �Ʒ��� �˻��ؼ� �ø��� �Ŵ�����
			// ��ϵ� �� ������Ʈ�� �浹�ߴ��� �˻��մϴ�.
			for (INT32 j = 0; j < static_cast<INT32>(OBJECT_DIRECTION::END); ++j)
			{
				// �̹� ���ߵ� ��ź�� ������ ������ �����մϴ�.
				if (m_bChainExplosionDirection[j] == true)
				{
					continue;
				}

				Position2D explosionPos     = { 0, 0 };
				Position2D bombDirectionPos = { 0, 0 };

				// ��ź�� ���߷¸�ŭ ������ ���ؼ� ���� ��ǥ�� �����մϴ�.
				MultiplePos(&bombDirectionPos, m_bombDirectionTable[j], i + 1);
				AddPos(&explosionPos, m_nowPos, bombDirectionPos);

				// ���� ������ �� ��� �ȿ� �ִ��� �˻��մϴ�.
				if (mgr::CollisionManager::ActivateManager().CheckBasePosExistInsidePos(explosionPos.x, explosionPos.y,
					MAP_START_BORDER_WIDTH, MAP_START_BORDER_HEIGHT, MAP_END_BORDER_WIDTH, MAP_END_BORDER_HEIGHT))
				{
					Position2D playerPos = mgr::GameManager::ActivateManager().getPlayerPos();

					// ��, ��, ��, �Ʒ� ������ �ø��� �Ŵ����� �ø������� ����մϴ�.
					mgr::GameManager::ActivateManager().EnrollMapObjectCollisionValue(&m_collisionValue, explosionPos);

					// �β��� ���� ���ߵ��� �ʽ��ϴ�.
					if (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
						static_cast<INT32>(MAP_OBJECT_SHAPE::HARD_WALL)))
					{
						bArrHardWall[j] = true;
					}

					if (bArrHardWall[j] == false)
					{
						// ���� ��ǥ�� �̿��ؼ� ���� ����Ʈ�� �����մϴ�.
						mgr::EffectManager::AcitvateInstance().CreateEffect(explosionPos, "��", EFFECT_TYPE::EXPLOSION);

						// ���� ���� ���ߵ˴ϴ�.
						if (mgr::CollisionManager::ActivateManager().CheckCollisionForCollisionValue(m_collisionValue,
							static_cast<INT32>(MAP_OBJECT_SHAPE::SOFT_WALL)))
						{
							// �̹� ���ߵ� ������ �������� �ʽ��ϴ�.
							// ��, �����۵� �������� �ʽ��ϴ�.
							if ( (bArrSoftWall[j] == false) &&
								 (bArrExplosionChain[j] == false) )
							{
								// ���� Ȯ���� ���� �������� �����մϴ�.
								_AppearItem(explosionPos);

								bArrSoftWall[j] = true;
							}
						}

						// ���� ������ �Ͼ�ٸ� � ���⿡�� ������ �Դ��� Ȯ���մϴ�.
						// ���� ��� �Ʒ��� ��ź�� �ְ� ���� �ִ� ��ź�� �����ߴٸ�
						// �Ʒ��� �ִ� ��ź�� ���� ���ߵǴ� ��ǥ�� �������� �ʾƵ� �˴ϴ�.
						if (bArrSoftWall[j] == false)
						{
							// ���� ������ �ٸ� ��ź�� �ǵ�ȴٸ� ���� ���߷� �����˴ϴ�.
							// ��ź�� � ��ź�� �ǵ�ȴ��� �Ǵ��� �ڿ� ���� �Ŵ����� ���� �÷��̾� ������ ����մϴ�.
							if (_CheckExplosionChain(explosionPos, static_cast<OBJECT_DIRECTION>(j)))
							{
								bArrExplosionChain[j] = true;
							}

							// �÷��̾ ���߿� �ָ����� �׽��ϴ�.
							// �÷��̾�� ���� ��, ���߿� �¾��� ���� �׽��ϴ�.
							// ��ź�� ��ġ, ���� ���⿡ ������ �޽��ϴ�.
							if ( (CheckSamePos(explosionPos, playerPos)) ||
								 (CheckSamePos(m_nowPos, playerPos)) )
							{
								bombState = BOMB_STATE::EXPLOSION_HIT_PLAYER;
							}
						}

						// �������� ���߿� �ָ����� ������ϴ�.
						if (_CheckExplosionItem())
						{
							mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos(explosionPos, MAP_OBJECT_SHAPE::ROAD);
						}
					}
				}
			}
		}

		// ��ź�� �����ϸ� ��ź�� ��ġ���� ���� ����Ʈ�� �����ؾ� �մϴ�.
		mgr::EffectManager::AcitvateInstance().CreateEffect(m_nowPos, "��", EFFECT_TYPE::EXPLOSION);

		return bombState;
	}

	void Bomb::_AppearItem(const Position2D& explosionPos) const
	{
		INT32 itemProbability = mgr::RandomManager::ActivateManager().GenerateIntRandomNumber(0, 100);

		// ���� Ȯ���� 80%��� 0 ~ 80 �ȿ� ������ �����ؾ� �մϴ�.
		// �ٽ� ���ϸ� 81 ~ 100�� ���ܵǹǷ� �� ���� �ȿ� ������ �����Ѵٸ�
		// 20% Ȯ���� ��÷�� �Ͱ� �����ϴ�. ���� Ȯ�� ����� ���� Ȯ�� -> ���� Ȯ�� ������ ó���ؾ� �մϴ�.
		//
		// �������� ������ Ȯ���� 70%�Դϴ�.
		if (itemProbability <= 70)
		{
			// �������� �������� ������ Ȯ���� ���� ���մϴ�.
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
			// �������� �������� ������ Ȯ���� 100%�� �ƴϹǷ� ������ Ȯ���� ���ؼ��� ó���ؾ� �մϴ�.
			// ������ �Ŀ� �������� ������ Ȯ���� 80%�̹Ƿ� �Ϲ������δ� �������� �����Ѵٰ� ���� �˴ϴ�.
			else
			{
				mgr::GameManager::ActivateManager().EnrollMapObjectForObjectPos(explosionPos, MAP_OBJECT_SHAPE::ROAD);
			}
		}
		else
		{
			// ���� �ı��ߴµ��� �������� �������� ���� �� �ֽ��ϴ�.
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

		// ���� ��ǥ�� ��ź�� �ִ� �� Ȯ�εǸ� �ش� ��ġ�� �ִ� ��ź�� �˻��մϴ�.
		LIST<Bomb*> listBomb = mgr::GameManager::ActivateManager().getListBomb();
		for (Bomb* i : listBomb)
		{
			if (i != nullptr)
			{
				// ���� ��ǥ�� ��ź�� �ִ��� �˻��մϴ�.
				if (CheckSamePos(explosionPos, i->getNowPos()))
				{
					pChainBomb = i;
					break;
				}
			}
		}

		OBJECT_DIRECTION chainExplosionDirection = OBJECT_DIRECTION::END;

		// ���� ���߿� ���� ������ �����մϴ�.
		// ���� �˻� ������ ��, ��, ��, �Ʒ��̹Ƿ�
		// ���� ���߿� ���� ������ ��, �Ʒ�, ��, ���� �˴ϴ�.
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