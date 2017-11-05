/*
 * <���� ��¥>
 * 2017-11-04
 *
 * <���� ����>
 * �÷��̾�� �����Ǵ� HUD(Head Up Display)�Դϴ�.
 * HUD�� �÷��̾�� �ʿ��� ������ �����ݴϴ�.
 */

#include "UI/player_HUD.h"

#include "manager_linker.h"

#include "object/player.h"
#include "object/player_info.h"
#include "object/stage.h"

namespace UI
{

	PlayerHUD::PlayerHUD()
	{
		m_pPlayerInfo = nullptr;
	}

	PlayerHUD::~PlayerHUD()
	{
	}

	void PlayerHUD::Initialize()
	{
		m_pPlayerInfo = g_pObjectMgr->getPlayer()->getPlayerInfo();
		m_bClearMessage = false;
	}

	void PlayerHUD::ShowHUD()
	{
		_ShowUnderLine();
		_ShowPlayerLife();
		_ShowLimitTime();
		_ShowPlayerScore();
		_ShowCurrentStageNum();
		cmn::ShowMessageAutoNewLine("\n");
	}

	void PlayerHUD::ShowClearMessage()
	{
		m_bClearMessage = true;
		cmn::ShowMessageAutoNewLine("�������� �����߽��ϴ�!");
	}

	void PlayerHUD::ShowAllClearMessage()
	{
		cmn::ShowMessageAutoNewLine("��� ���������� Ŭ�����߽��ϴ�!");
	}

	void PlayerHUD::_ShowUnderLine()
	{
		g_pSystemMgr->AdjustRenderingPos(0, g_pStageMgr->getStage()->getStageInfo().heightBorderRenderBegin +
			g_pStageMgr->getStage()->getStageInfo().heightBorderRenderEnd);
		g_pSystemMgr->AdjustRenderColor(RENDERING_COLOR::LIGHT_WHITE);

		for (INT32 i = 0; i < g_pStageMgr->getStage()->getStageInfo().widthBorder; ++i)
		{
			printf("��");
		}
	}

	void PlayerHUD::_ShowPlayerLife()
	{
		g_pSystemMgr->AdjustRenderingPos(0, g_pStageMgr->getStage()->getStageInfo().heightBorderRenderBegin +
			g_pStageMgr->getStage()->getStageInfo().heightBorderRenderEnd + 1);
		g_pSystemMgr->AdjustRenderColor(RENDERING_COLOR::LIGHT_WHITE);

		INT32 playerLife = m_pPlayerInfo->getLife();

		if (playerLife < 0)
		{
			playerLife = 0;
		}

		printf("���� ���(%d)", playerLife);
	}

	void PlayerHUD::_ShowLimitTime()
	{
		INT32 limitTime = g_pStageMgr->CalcLimitTime();

		if (limitTime < 0)
		{
			limitTime = 0;
		}

		printf("    ���� �ð�(%d)", limitTime);
	}

	void PlayerHUD::_ShowPlayerScore()
	{
		printf("    ���� ����(%d)", g_pObjectMgr->getPlayer()->getPlayerInfo()->getScore());
	}

	void PlayerHUD::_ShowCurrentStageNum()
	{
		printf("    �������� 1-%d", g_pStageMgr->getNowStage());
	}

} // namespace UI end