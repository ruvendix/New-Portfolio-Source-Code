/*
 * <제작 날짜>
 * 2017-10-28
 *
 * <파일 설명>
 * 플레이어의 정보입니다.
 */

#include "object/player_info.h"

#include "manager_linker.h"

#include "object/stage.h"

namespace object
{

	PlayerInfo::PlayerInfo()
	{
		setRenderColor(RENDERING_COLOR::NONE);
		setShape("  ");

		m_score              = 0;
		m_life               = 3;
		m_currentBulletCount = 0;

		m_bDescent        = false;
		m_bFallDown       = false;
		m_bGoal           = false;
		m_bGrowth         = false;
		m_bShoot          = false;
		m_bCollisionState = false;
		
		strncpy_s(m_strDownShape.strData, "  ", sizeof(3));
		InitializeJumpInfo();

		m_renderPos = { 0, 0 };

		m_deltaDirection = 1;
		m_direction      = OBJECT_DIRECTION::RIGHT;
	}

	PlayerInfo::~PlayerInfo()
	{

	}

	void PlayerInfo::InitializeInfo(bool bLifeInit)
	{
		setRenderColor(RENDERING_COLOR::INTENSITY_YELLOW);
		setShape("♀");

		m_score = 0;
		m_currentBulletCount = 0;

		if (bLifeInit == true)
		{
			m_life = 3;
		}

		m_bDescent        = false;
		m_bFallDown       = false;
		m_bGoal           = false;
		m_bGrowth         = false;
		m_bShoot          = false;
		m_bCollisionState = false;

		strncpy_s(m_strDownShape.strData, "ㅅ", sizeof(3));
		InitializeJumpInfo();

		m_renderPos.y = g_pStageMgr->getStage()->getStageInfo().heightBorderRenderBegin;
		et_math::setPos(g_pStageMgr->getStage()->getStageInfo().startPos, &m_nowPos);

		m_direction = OBJECT_DIRECTION::RIGHT;
	}

	void PlayerInfo::MinusRenderPosY()
	{
		--m_renderPos.y;
	}

	void PlayerInfo::InitializeRenderPosY()
	{
		m_renderPos.y = g_pStageMgr->getStage()->getStageInfo().heightBorderRenderBegin;
	}

	void PlayerInfo::InitializeJumpInfo()
	{
		m_jumpInfo.m_jumpState   = PLAYER_JUMP_STATE::NONE;
		m_jumpInfo.m_deltaJump   = 0;
		m_jumpInfo.m_bJump       = false;
	}

} // namespace object end