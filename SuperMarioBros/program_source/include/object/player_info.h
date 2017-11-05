/*
 * <제작 날짜>
 * 2017-10-28
 *
 * <파일 설명>
 * 플레이어의 정보입니다.
 */

#ifndef SIDESCROLLING__PLAYER_INFO_H_
#define SIDESCROLLING__PLAYER_INFO_H_

#include "common.h"

#include "object/object_base_info.h"

const INT32 MAX_PLAYER_JUMP = 2;

enum class PLAYER_JUMP_STATE : INT32
{
	NONE = 0,
	UP,
	DOWN,
	END,
};

struct PlayerJumpInfo
{
	INT32                m_deltaJump;
	PLAYER_JUMP_STATE    m_jumpState;
	bool                 m_bJump;
};

namespace object
{

	class PlayerInfo : public ObjectBaseInfo
	{
	public:
		PlayerInfo();
		virtual ~PlayerInfo();

		void AddScore(INT32 score)
		{
			m_score += score;
		}

		void AddCurrentBulletCount()
		{
			++m_currentBulletCount;
		}

		void MinusCurrentBulletCount()
		{
			--m_currentBulletCount;
		}

		void MinusLife()
		{
			--m_life;
		}

		void PlusDeltaJump()
		{
			++m_jumpInfo.m_deltaJump;
		}

		void InitializeInfo(bool bLifeInit = true);
		void MinusRenderPosY();
		void InitializeRenderPosY(); // 안씀
		void InitializeJumpInfo();

		// getter
		INT32 getScore() const noexcept
		{
			return m_score;
		}

		INT32 getLife() const noexcept
		{
			return m_life;
		}

		bool getFallDown() const noexcept
		{
			return m_bFallDown;
		}

		bool getGoal() const noexcept
		{
			return m_bGoal;
		}

		INT32 getDeltaJump() const noexcept
		{
			return m_jumpInfo.m_deltaJump;
		}

		PLAYER_JUMP_STATE getJumpState() const noexcept
		{
			return m_jumpInfo.m_jumpState;
		}

		bool getJump() const noexcept
		{
			return m_jumpInfo.m_bJump;
		}

		bool getGrowth() const noexcept
		{
			return m_bGrowth;
		}

		bool getShoot() const noexcept
		{
			return m_bShoot;
		}

		bool getDescent() const noexcept
		{
			return m_bDescent;
		}

		const ASCII* getDownShape() const noexcept
		{
			return m_strDownShape.strData;
		}

		INT32 getCurrentBulletCount() const noexcept
		{
			return m_currentBulletCount;
		}

		// setter
		void setScore(INT32 score)
		{
			m_score = score;
		}

		void setLife(INT32 life)
		{
			m_life = life;
		}

		void setFallDown(bool bFalldown)
		{
			m_bFallDown = bFalldown;
		}

		void setGoal(bool bGoal)
		{
			m_bGoal = bGoal;
		}

		void setDeltaJump(INT32 deltaJump)
		{
			m_jumpInfo.m_deltaJump = deltaJump;
		}

		void setJumpState(const PLAYER_JUMP_STATE& jumpState)
		{
			m_jumpInfo.m_jumpState = jumpState;
		}

		void setJump(bool bJump)
		{
			m_jumpInfo.m_bJump = bJump;
		}

		void setGrowth(bool bGrowth)
		{
			m_bGrowth = bGrowth;
		}

		void setShoot(bool bShoot)
		{
			m_bShoot = bShoot;
		}

		void setDescent(bool bDescent)
		{
			m_bDescent = bDescent;
		}

	private:
		INT32             m_score;
		INT32             m_life;
		INT32             m_currentBulletCount;
			
		bool              m_bDescent;
		bool              m_bFallDown;
		bool              m_bGoal;
		bool              m_bGrowth;
		bool              m_bShoot;

		StringBuffer      m_strDownShape;
		PlayerJumpInfo    m_jumpInfo;
	};

} // namespace object end

#endif