/*
 * <제작 날짜>
 * 2017-10-24
 *
 * <파일 설명>
 * 게임 프로그램의 흐름을 관리합니다.
 */

#include "game_mgr.h"

#include "manager_linker.h"

#include "object/stage.h"
#include "object/player.h"
#include "object/player_info.h"

#include "UI/player_HUD.h"

namespace manager
{

	SCENE_STATE GameMgr::Initialize()
	{
		g_pObjectMgr->Initialize();

		g_pStageMgr->Initialize();
		g_pStageMgr->LoadStageList();

		m_pStage = std::make_shared<obj::Stage>();
		assert(m_pStage != nullptr);
		g_pStageMgr->setStage(m_pStage.get());
		m_pStage->Initialize();

		g_pObjectMgr->InitializePlayer();

		m_pPlayerHUD = std::make_shared<UI::PlayerHUD>();
		assert(m_pPlayerHUD != nullptr);
		m_pPlayerHUD->Initialize();

		return SCENE_STATE::INIT_SCENE_SUCCESS;
	}

	SCENE_STATE GameMgr::Update()
	{
		m_pStage->Update();
		g_pObjectMgr->UpdateObject();
		g_pSoundMgr->UpdateBGM("stage.mp3");

		if ( (g_pObjectMgr->CheckPlayerArriveGoal()) &&
			 (m_pPlayerHUD->getClearMessage()) )
		{
			// 다음 스테이지로 이동하면 스테이지와 몬스터만 초기화됩니다.
			ClearStage();
			m_pPlayerHUD->setClearMessage(false);
			return SCENE_STATE::UPDATE_SCENE_SUCCESS;
		}

		return SCENE_STATE::UPDATE_SCENE_SUCCESS;
	}

	SCENE_STATE GameMgr::Render()
	{
		m_pStage->Render();
		g_pObjectMgr->RenderObject();
		m_pPlayerHUD->ShowHUD();

		if (_JudgeGameState())
		{
			cmn::PauseProgram();

			g_pObjectMgr->ResetObject();  // 플레이어만 동적할당을 해제하지 않습니다.
			g_pStageMgr->ResetStage();    // 동적할당을 해제합니다.

			g_pSoundMgr->PlayOnSound("stage.mp3", true);
			return SCENE_STATE::RENDER_SCENE_SUCCESS;
		}

		if (g_pObjectMgr->CheckPlayerArriveGoal())
		{
			m_pPlayerHUD->ShowClearMessage();
			g_pSoundMgr->StopOnSound("stage.mp3", true);
			g_pSoundMgr->PlayOnSound("stage_clear.wav");
			g_pSoundMgr->WaitPlayingSound("stage_clear.wav");
			g_pSoundMgr->PlayOnSound("stage.mp3", true);
			return SCENE_STATE::RENDER_SCENE_SUCCESS;
		}

		if (g_pStageMgr->getNowStage() > g_pStageMgr->getStageCount())
		{
			g_pSoundMgr->StopOnSound("stage.mp3", true);
			g_pSoundMgr->PlayOnSound("world_clear.wav");
			g_pSoundMgr->WaitPlayingSound("world_clear.wav");
			return SCENE_STATE::RENDER_SCENE_SUCCESS;
		}

		return SCENE_STATE::RENDER_SCENE_SUCCESS;
	}

	SCENE_STATE GameMgr::Release()
	{
		g_pObjectMgr->ReleaseObject();
		m_pStage->Release();
		g_pStageMgr->ReleaseStage();

		return SCENE_STATE::RELEASE_SCENE_SUCCESS;
	}

	SCENE_STATE GameMgr::ClearStage()
	{
		if (g_pStageMgr->getNowStage() > g_pStageMgr->getStageCount())
		{
			m_pPlayerHUD->ShowAllClearMessage();
			return SCENE_STATE::MOVE_TITLE;
		}

		g_pObjectMgr->ResetBullet();
		g_pObjectMgr->ResetMonster();

		g_pStageMgr->AddStageNum();
		g_pStageMgr->ResetStage();

		obj::PlayerInfo* pPlayerInfo = g_pObjectMgr->getPlayer()->getPlayerInfo();
		pPlayerInfo->setGoal(false);
		et_math::setPos(g_pStageMgr->getStage()->getStageInfo().startPos, pPlayerInfo->getNowPos());

		return SCENE_STATE::NONE;
	}

	bool GameMgr::_JudgeGameState()
	{
		bool bPlayerFallDown     = g_pObjectMgr->CheckPlayerFallDown();
		bool bPlayerCollision    = g_pObjectMgr->CheckPlayerCollision();
		bool bStageLimitTimeOver = g_pStageMgr->CheckLimitTimeOver();

		obj::PlayerInfo* pPlayerInfo = g_pObjectMgr->getPlayer()->getPlayerInfo();

		if ( (bPlayerFallDown) ||
			 (bPlayerCollision) ||
			 (bStageLimitTimeOver) )
		{
			pPlayerInfo->MinusLife();
		}

		if (g_pObjectMgr->CheckPlayerGameOver())
		{
			cmn::ShowMessageAutoNewLine("남은 목숨이 없습니다!");
			g_pSoundMgr->StopOnSound("stage.mp3", true);
			g_pSoundMgr->PlayOnSound("game_over.wav");
			g_pSoundMgr->WaitPlayingSound("game_over.wav");
			return true;
		}

		if (bPlayerFallDown)
		{
			cmn::ShowMessageAutoNewLine("플레이어가 추락사했습니다!");
			g_pSoundMgr->StopOnSound("stage.mp3", true);
			g_pSoundMgr->PlayOnSound("you_died.wav");
			g_pSoundMgr->WaitPlayingSound("you_died.wav");
			return true;
		}
		else if (bPlayerCollision)
		{
			cmn::ShowMessageAutoNewLine("플레이어가 사망했습니다!");
			g_pSoundMgr->StopOnSound("stage.mp3", true);
			g_pSoundMgr->PlayOnSound("you_died.wav");
			g_pSoundMgr->WaitPlayingSound("you_died.wav");
			return true;
		}
		else if (bStageLimitTimeOver)
		{
			cmn::ShowMessageAutoNewLine("남은 시간이 없습니다!");
			g_pSoundMgr->StopOnSound("stage.mp3", true);
			g_pSoundMgr->PlayOnSound("you_died.wav");
			g_pSoundMgr->WaitPlayingSound("you_died.wav");
			return true;
		}

		return false;
	}

} // namespace manager end