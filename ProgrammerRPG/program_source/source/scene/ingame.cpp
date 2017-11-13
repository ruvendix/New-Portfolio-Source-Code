/*
 * <제작 날짜>
 * 2017-11-11
 *
 * <파일 설명>
 * 게임의 인게임 씬입니다.
 * 인게임에서는 플레이어가 게임을 할 수 있습니다.
 */

#include "scene/ingame.h"
#include "manager/mgr_linker.h"
#include "object/player.h"

namespace scene
{

	Ingame::Ingame()
	{
		m_vecSubSceneFunc.reserve(5);
		m_pNowSubScene = nullptr;
	}

	Ingame::~Ingame()
	{
		cmn::SafeDelete(&m_pNowSubScene);
		m_vecSubSceneFunc.clear();
	}

	SCENE_STATE Ingame::Initialize()
	{
		m_vecSubSceneFunc.push_back(std::bind(&Ingame::_GotoStudy, this));
		m_vecSubSceneFunc.push_back(std::bind(&Ingame::_GotoHunger, this));
		m_vecSubSceneFunc.push_back(std::bind(&Ingame::_GotoSociety, this));

		g_pObjMgr->InitializeData();
		if (g_pObjMgr->InitializePlayer() == OBJECT_STATE::INIT_FAIL)
		{
			return SCENE_STATE::INIT_FAIL;
		}

		return SCENE_STATE::INIT_SUCCESS;
	}

	SCENE_STATE Ingame::Update()
	{
		if (m_selMenu == 0)
		{
			return SCENE_STATE::UPDATE_SUCCESS;
		}
		// 게임을 저장합니다.
		else if (m_selMenu == 4)
		{
			// 게임 저장
		}
		// 타이틀로 돌아갑니다.
		else if (m_selMenu == 5)
		{
			return SCENE_STATE::GOTO_TITLE;
		}

		g_pObjMgr->getPlayer()->Update();

		SCENE_STATE subSceneState = SCENE_STATE::UPDATE_SUCCESS;

		// 사용자의 입력에 따라 서브 씬을 반환합니다.
		if (m_bHold)
		{
			m_bHold = g_pSceneMgr->AdjustSubScene(m_vecSubSceneFunc, m_selMenu, &m_pNowSubScene, &subSceneState);
		}

		// 다시 메인 씬으로 돌아오면 현재 서브 씬을 해제해야 합니다.
		subSceneState = m_pNowSubScene->Update();
		subSceneState = g_pSceneMgr->BackToPreviousScene(subSceneState, &m_pNowSubScene, &m_bHold);
		
		g_pUserInputMgr->FlushBuffer();

		return subSceneState;
	}

	SCENE_STATE Ingame::Render()
	{
		cmn::ShowHardBorderAutoNewLine();
		cmn::ShowMessageAutoNewLine("인게임 렌더링");
		cmn::ShowHardBorderAutoNewLine();

		g_pObjMgr->getPlayer()->Render();

		if (m_bHold)
		{
			cmn::ShowMessageAutoNewLine("1. 코딩 공부");
			cmn::ShowMessageAutoNewLine("2. 밥 먹자");
			cmn::ShowMessageAutoNewLine("3. 사회 진출");
			cmn::ShowMessageAutoNewLine("4. 저장하기");
			cmn::ShowMessageAutoNewLine("5. 타이틀로 돌아가기");

			g_pSceneMgr->SelectMenu(&m_selMenu, 1, 5);
		}
		else
		{
			m_pNowSubScene->Render();
		}

		return SCENE_STATE::RENDER_SUCCESS;
	}

	SCENE_STATE Ingame::Release()
	{
		g_pSceneMgr->ResetSubScene(&m_pNowSubScene);
		g_pObjMgr->ReleasePlayer();
		return SCENE_STATE::RELEASE_SUCCESS;
	}

	SUB_SCENE_TYPE Ingame::_GotoStudy()
	{
		cmn::ShowMessageAutoNewLine("공부를 합니다.");
		return SUB_SCENE_TYPE::STUDY_MAIN;
	}

	SUB_SCENE_TYPE Ingame::_GotoHunger()
	{
		cmn::ShowMessageAutoNewLine("뭔가를 먹습니다.");
		return SUB_SCENE_TYPE::HUNGER_MAIN;
	}

	SUB_SCENE_TYPE Ingame::_GotoSociety()
	{
		cmn::ShowMessageAutoNewLine("사회로 진출합니다.");
		return SUB_SCENE_TYPE::SOCIETY_MAIN;
	}

} // namespace scene end