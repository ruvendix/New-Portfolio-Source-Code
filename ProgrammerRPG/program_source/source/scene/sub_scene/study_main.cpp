/*
 * <제작 날짜>
 * 2017-11-12
 *
 * <파일 설명>
 * 공부하는 메인 씬입니다.
 * 플레이어는 C언어와 C++언어 중 하나를 선택할 수 있습니다.
 * 언어를 선택하면 다른 서브 씬이 작동하게 됩니다.
 */

#include "scene/sub_scene/study_main.h"
#include "manager/mgr_linker.h"

namespace scene
{

	StudyMain::StudyMain()
	{

	}

	StudyMain::~StudyMain()
	{

	}

	SCENE_STATE StudyMain::Initialize()
	{
		m_vecSubSceneFunc.push_back(std::bind(&StudyMain::_StudyC, this));
		m_vecSubSceneFunc.push_back(std::bind(&StudyMain::_StudyCPP, this));
		return SCENE_STATE::INIT_SUCCESS;
	}

	SCENE_STATE StudyMain::Update()
	{
		if (m_selMenu == 0)
		{
			return SCENE_STATE::UPDATE_SUCCESS;
		}
		else if (m_selMenu == 3)
		{
			return SCENE_STATE::CHANGE;
		}
		else if (m_selMenu == 4)
		{
			return SCENE_STATE::GOTO_TITLE;
		}

		SCENE_STATE subSceneState = SCENE_STATE::UPDATE_SUCCESS;

		// 사용자의 입력에 따라 서브 씬을 반환합니다.
		if (m_bHold)
		{
			m_bHold = g_pSceneMgr->AdjustSubScene(m_vecSubSceneFunc, m_selMenu, &m_pNowSubScene, &subSceneState);
		}

		// 다시 메인 씬으로 돌아오면 현재 서브 씬을 해제해야 합니다.
		subSceneState = m_pNowSubScene->Update();
		subSceneState = g_pSceneMgr->BackToPreviousScene(subSceneState, &m_pNowSubScene, &m_bHold);

		return subSceneState;
	}

	SCENE_STATE StudyMain::Render()
	{
		if (m_bHold)
		{
			cmn::ShowMessageAutoNewLine("1. C언어 공부하기(체력 20소모)");
			cmn::ShowMessageAutoNewLine("2. C++언어 공부하기(체력 60소모)");
			cmn::ShowMessageAutoNewLine("3. 뒤로 가기");
			cmn::ShowMessageAutoNewLine("4. 타이틀로 돌아가기");

			g_pSceneMgr->SelectMenu(&m_selMenu, 1, 4);
		}
		else
		{
			m_pNowSubScene->Render();
		}

		return SCENE_STATE::RENDER_SUCCESS;
	}

	SCENE_STATE StudyMain::Release()
	{
		return SCENE_STATE::RELEASE_SUCCESS;
	}

	SUB_SCENE_TYPE StudyMain::_StudyC()
	{
		cmn::ShowMessageAutoNewLine("C언어를 공부합니다.");
		return SUB_SCENE_TYPE::STUDY_C;
	}

	SUB_SCENE_TYPE StudyMain::_StudyCPP()
	{
		cmn::ShowMessageAutoNewLine("C언어를 공부합니다.");
		return SUB_SCENE_TYPE::STUDY_CPP;
	}

} // namespace scene end