/*
 * <제작 날짜>
 * 2017-10-30
 *
 * <파일 설명>
 * 오브젝트의 외부 정보를 관리합니다.
 * 스테이지는 오브젝트의 집합이므로 매니저를 따로 운영합니다.
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
		obj::Bullet*                    m_pBulletTable[MAX_BULLET]; // 고정 크기가 정해진 배열
		obj::Monster**                  m_ppMonsterTable;           // 유동적으로 크기가 변하는 배열
		
		INT32                           m_maxCurrentMonsterCount;
		INT32                           m_currentMonsterCount;
	};

} // namespace manager end

#endif