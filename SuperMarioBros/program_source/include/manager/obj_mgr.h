/*
 * <���� ��¥>
 * 2017-10-30
 *
 * <���� ����>
 * ������Ʈ�� �ܺ� ������ �����մϴ�.
 * ���������� ������Ʈ�� �����̹Ƿ� �Ŵ����� ���� ��մϴ�.
 */

#ifndef SIDESCROLLING__OBJECT_MANAGER_H_
#define SIDESCROLLING__OBJECT_MANAGER_H_

#include "common.h"
#include "global_data.h"

namespace object
{
	class Player;
	class Bullet;
	class Monster;
}

namespace manager
{

	class ObjMgr
	{
		DEFINE_SINGLETON_CLASS(ObjMgr);
	public:
		OBJECT_STATE Initialize();
		OBJECT_STATE InitializePlayer();
		OBJECT_STATE UpdateObject();
		OBJECT_STATE RenderObject();
		OBJECT_STATE ReleaseObject();

		void CreateBullet(const Position2D& pos, OBJECT_DIRECTION direction);
		void RenderBullet(INT32 bulletIndex);
		void CreateMonster(const Position2D& pos);
		void RenderMonster(INT32 monsterIndex);
		void ResetObject();

		bool CheckPlayerFallDown();
		bool CheckPlayerArriveGoal();
		bool CheckPlayerCollision();
		bool CheckPlayerGameOver();
		bool CheckBulletRendering(INT32 x, INT32 y, INT32* pBulletIndex);
		bool CheckMonsterRendering(INT32 x, INT32 y, INT32* pMonsterIndex);
		bool CheckMonsterCollisionPos(INT32 x, INT32 y);

		void ResetPlayer();
		void ResetBullet();
		void ResetMonster();

		// getter
		obj::Player* getPlayer() const
		{
			return m_pPlayer.get();
		}

		// setter
		void setMaxCurrentMonsterCount(INT32 monsterCount)
		{
			m_maxCurrentMonsterCount = monsterCount;
		}

	private:
		std::shared_ptr<obj::Player>    m_pPlayer;
		obj::Bullet*                    m_pBulletTable[MAX_BULLET]; // ���� ũ�Ⱑ ������ �迭
		obj::Monster**                  m_ppMonsterTable;           // ���������� ũ�Ⱑ ���ϴ� �迭
		
		INT32                           m_maxCurrentMonsterCount;
		INT32                           m_currentMonsterCount;
	};

} // namespace manager end

#endif