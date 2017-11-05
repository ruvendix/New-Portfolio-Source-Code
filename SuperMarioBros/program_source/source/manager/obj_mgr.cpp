/*
 * <제작 날짜>
 * 2017-10-30
 *
 * <파일 설명>
 * 오브젝트의 외부 정보를 관리합니다.
 * 스테이지는 오브젝트의 집합이므로 매니저를 따로 운영합니다.
 */

#include "obj_mgr.h"

#include "manager_linker.h"

#include "object/bullet.h"
#include "object/monster.h"
#include "object/player.h"
#include "object/player_info.h"

namespace manager
{

	OBJECT_STATE ObjMgr::Initialize()
	{
		cmn::InitializeArrayMemory(m_pBulletTable, _countof(m_pBulletTable));

		m_ppMonsterTable         = nullptr;
		m_maxCurrentMonsterCount = 2;
		m_currentMonsterCount    = 0;

		return OBJECT_STATE::INIT_OBJECT_SUCCESS;
	}

	OBJECT_STATE ObjMgr::InitializePlayer()
	{
		m_pPlayer = std::make_shared<obj::Player>();
		assert(m_pPlayer != nullptr);
		m_pPlayer->Initialize();
		return OBJECT_STATE::INIT_OBJECT_SUCCESS;
	}

	OBJECT_STATE ObjMgr::UpdateObject()
	{
		m_pPlayer->Update();

		for (INT32 i = 0; i < m_pPlayer->getPlayerInfo()->getCurrentBulletCount(); )
		{
			assert(m_pBulletTable[i] != nullptr);
			if (m_pBulletTable[i] != nullptr)
			{
				OBJECT_STATE bulletState = m_pBulletTable[i]->Update();

				if (bulletState == OBJECT_STATE::UPDATE_OBJECT_DELETE)
				{
					cmn::SafeDelete(&m_pBulletTable[i]);
					m_pPlayer->getPlayerInfo()->MinusCurrentBulletCount();

					// 마지막 인덱스는 따로 처리합니다.
					for (INT32 j = i; j < MAX_BULLET - 1; ++j)
					{
						m_pBulletTable[j] = m_pBulletTable[j + 1];
					}

					m_pBulletTable[MAX_BULLET - 1] = nullptr;
				}
				else
				{
					++i;
				}
			}
		}

		for (INT32 i = 0; i < m_currentMonsterCount; )
		{
			assert(m_ppMonsterTable[i] != nullptr);
			if (m_ppMonsterTable[i] != nullptr)
			{
				OBJECT_STATE monsterState = m_ppMonsterTable[i]->Update();

				if ( (monsterState == OBJECT_STATE::UPDATE_OBJECT_DELETE) ||
					 (m_ppMonsterTable[i]->getFallDown()) )
				{
					cmn::SafeDelete(&m_ppMonsterTable[i]);
					--m_currentMonsterCount;

					for (INT32 j = i; j < m_maxCurrentMonsterCount - 1; ++j)
					{
						m_ppMonsterTable[j] = m_ppMonsterTable[j + 1];
					}

					m_ppMonsterTable[m_maxCurrentMonsterCount - 1] = nullptr;
				}
				else
				{
					++i;
				}
			}
		}

		return OBJECT_STATE::UPDATE_OBJECT_SUCCESS;
	}

	OBJECT_STATE ObjMgr::RenderObject()
	{
		m_pPlayer->Render();

		// 총알과 몬스터 렌더링은 스테이지에서 합니다.

		return OBJECT_STATE::RENDER_OBJECT_SUCCESS;
	}

	OBJECT_STATE ObjMgr::ReleaseObject()
	{
		m_pPlayer->Release();

		for (INT32 i = 0; i < m_pPlayer->getPlayerInfo()->getCurrentBulletCount(); ++i)
		{
			cmn::SafeDelete(&m_pBulletTable[i]);
		}

		for (INT32 i = 0; i < m_currentMonsterCount; ++i)
		{
			cmn::SafeDelete(&m_ppMonsterTable[i]);
		}

		if (m_currentMonsterCount != 0)
		{
			cmn::SafeArrayDelete(m_ppMonsterTable);
		}

		return OBJECT_STATE::RELEASE_OBJECT_SUCCESS;
	}

	void ObjMgr::ResetPlayer()
	{
		bool bLifeInit = CheckPlayerGameOver();
		m_pPlayer->getPlayerInfo()->InitializeInfo(bLifeInit);
	}

	void ObjMgr::ResetBullet()
	{
		for (INT32 i = 0; i < m_pPlayer->getPlayerInfo()->getCurrentBulletCount(); ++i)
		{
			cmn::SafeDelete(&m_pBulletTable[i]);
		}
	}

	void ObjMgr::ResetMonster()
	{
		for (INT32 i = 0; i < m_currentMonsterCount; ++i)
		{
			cmn::SafeDelete(&m_ppMonsterTable[i]);
		}

		m_currentMonsterCount    = 0;
		m_maxCurrentMonsterCount = 2;
	}

	void ObjMgr::CreateBullet(const Position2D& pos, OBJECT_DIRECTION direction)
	{
		obj::PlayerInfo* pPlayerInfo = m_pPlayer->getPlayerInfo();

		if (pPlayerInfo->getCurrentBulletCount() >= MAX_BULLET)
		{
			return;
		}

		obj::Bullet* pBullet = new obj::Bullet;
		assert(pBullet != nullptr);

		if (pBullet->Initialize() == OBJECT_STATE::INIT_OBJECT_FAIL)
		{
			cmn::SafeDelete(&pBullet);
		}

		pBullet->getBulletInfo()->setDirection(direction);
		et_math::setPos(pos, pBullet->getBulletInfo()->getNowPos());

		m_pBulletTable[pPlayerInfo->getCurrentBulletCount()] = pBullet;
		pPlayerInfo->AddCurrentBulletCount();
	}

	void ObjMgr::RenderBullet(INT32 bulletIndex)
	{
		m_pBulletTable[bulletIndex]->Render();
	}

	void ObjMgr::CreateMonster(const Position2D& pos)
	{
		obj::Monster* pMonster = new obj::Monster;
		assert(pMonster != nullptr);

		if (pMonster->Initialize() == OBJECT_STATE::INIT_OBJECT_FAIL)
		{
			cmn::SafeDelete(&pMonster);
		}

		et_math::setPos(pos, pMonster->getMonsterInfo()->getNowPos());
		
		if (m_ppMonsterTable == nullptr)
		{
			m_ppMonsterTable = new obj::Monster*[m_maxCurrentMonsterCount];
		}

		// 현재 생성된 몬스터의 개수가 제한된 개수와 같으면 메모리를 늘립니다 => 메모리풀
		if (m_currentMonsterCount == m_maxCurrentMonsterCount)
		{
			cmn::IncreaseArrayMemoryDouble(&m_ppMonsterTable, &m_maxCurrentMonsterCount);
		}

		m_ppMonsterTable[m_currentMonsterCount] = pMonster;
		++m_currentMonsterCount;
	}

	void ObjMgr::RenderMonster(INT32 monsterIndex)
	{
		m_ppMonsterTable[monsterIndex]->Render();
	}

	void ObjMgr::ResetObject()
	{
		ResetPlayer();
		ResetBullet();
		ResetMonster();
	}

	bool ObjMgr::CheckPlayerFallDown()
	{
		return m_pPlayer->getPlayerInfo()->getFallDown();
	}

	bool ObjMgr::CheckPlayerArriveGoal()
	{
		return m_pPlayer->getPlayerInfo()->getGoal();
	}

	bool ObjMgr::CheckPlayerCollision()
	{
		return m_pPlayer->getPlayerInfo()->getCollisionState();
	}

	bool ObjMgr::CheckPlayerGameOver()
	{
		if (m_pPlayer->getPlayerInfo()->getLife() < 0)
		{
			return true;
		}

		return false;
	}

	bool ObjMgr::CheckBulletRendering(INT32 x, INT32 y, INT32* pBulletIndex)
	{
		for (INT32 i = 0; i < m_pPlayer->getPlayerInfo()->getCurrentBulletCount(); ++i)
		{
			assert(m_pBulletTable[i] != nullptr);
			if ( (m_pBulletTable[i] != nullptr) &&
				 (et_math::CheckSamePos(x, y, *(m_pBulletTable[i]->getBulletInfo()->getNowPos()))) )
			{
				bool bInvaildIndex = (i < 0) || (i >= MAX_BULLET);
				//assert(bInvaildIndex != true);

				if (bInvaildIndex == true)
				{
					return false;
				}

				*pBulletIndex = i;
				return true;
			}
		}

		return false;
	}

	bool ObjMgr::CheckMonsterRendering(INT32 x, INT32 y, INT32* pMonsterIndex)
	{
		for (INT32 i = 0; i < m_currentMonsterCount; ++i)
		{
			assert(m_ppMonsterTable[i] != nullptr);
			if ( (m_ppMonsterTable[i] != nullptr) &&
				 (et_math::CheckSamePos(x, y, *(m_ppMonsterTable[i]->getMonsterInfo()->getNowPos()))) )
			{
				bool bInvaildIndex = (i < 0) || (i >= m_currentMonsterCount);
				assert(bInvaildIndex != true);

				if (bInvaildIndex == true)
				{
					return false;
				}

				*pMonsterIndex = i;
				return true;
			}
		}

		return false;
	}

	bool ObjMgr::CheckMonsterCollisionPos(INT32 x, INT32 y)
	{
		for (INT32 i = 0; i < m_currentMonsterCount; ++i)
		{
			if ( (et_math::CheckSamePos(x, y, *m_ppMonsterTable[i]->getMonsterInfo()->getNowPos()) ||
				 (et_math::CheckSamePos(x, y,
					 m_ppMonsterTable[i]->getMonsterInfo()->getNowPosX() +
					 m_ppMonsterTable[i]->getMonsterInfo()->getDeltaDirection(),
					 m_ppMonsterTable[i]->getMonsterInfo()->getNowPosY()))) )
			{
				m_ppMonsterTable[i]->getMonsterInfo()->setCollisionState(true);
				return true;
			}
		}

		return false;
	}

} // namespace manager end