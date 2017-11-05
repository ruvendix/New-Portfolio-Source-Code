/*
 * <제작 날짜>
 * 2017-10-28
 *
 * <파일 설명>
 * 플레이어의 기본 구현입니다.
 */

#ifndef SIDESCROLLING__PLAYER_H_
#define SIDESCROLLING__PLAYER_H_

#include "object/object_base.h"
#include "global_data.h"

namespace object
{
	class PlayerInfo;
}

namespace object
{

	class Player : public ObjectBase
	{
	public:
		Player();
		virtual ~Player();

		virtual OBJECT_STATE Initialize() override;
		virtual OBJECT_STATE Update()     override;
		virtual OBJECT_STATE Render()     override;
		virtual OBJECT_STATE Release()    override;

		void _MovePos();
		void _DescendPosNotJump();
		void _JumpPos();
		void _EatItem();
		void _ShootBullet();
		void _SyncRenderingPos();
		
		bool _CheckPlayerArriveGoal();
		bool _CheckGrowthCollision(INT32 dx, INT32 dy, TILE_TYPE tileType);

		// 사용되지 않는 함수입니다.
		__declspec(deprecated) bool _CheckPlayerFallDown();

		// getter
		PlayerInfo* getPlayerInfo() const
		{
			return m_pPlayerInfo.get();
		}

	private:
		std::shared_ptr<PlayerInfo>    m_pPlayerInfo;
	};

} // namespace object end

#endif