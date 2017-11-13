/*
 * <제작 날짜>
 * 2017-11-11
 *
 * <파일 설명>
 * 씬을 관리하는 매니저입니다.
 * 모든 씬은 기본 씬을 기반으로 구현됩니다.
 */

#include "manager/scene_mgr.h"
#include "manager/mgr_linker.h"

#include "scene/title.h"
#include "scene/synopsis.h"
#include "scene/ingame.h"

#include "scene/sub_scene/study_main.h"
#include "scene/sub_scene/study_c.h"
#include "scene/sub_scene/study_cpp.h"
#include "scene/sub_scene/hunger_main.h"
#include "scene/sub_scene/society_main.h"

namespace manager
{
	void SceneMgr::ResetScene()
	{
		if (m_pScene)
		{
			m_pScene->Release();
		}
		cmn::SafeDelete(&m_pScene);
	}

	void SceneMgr::ResetSubScene(scene::SceneBase** ppSubScene)
	{
		if (ppSubScene == nullptr)
		{
			return;
		}

		if (*ppSubScene)
		{
			(*ppSubScene)->Release();
		}

		cmn::SafeDelete(ppSubScene);
	}

	void SceneMgr::SelectMenu(INT32* pSelMenu, INT32 min, INT32 max)
	{
		printf("메뉴를 선택하세요 >> ");

		*pSelMenu = g_pUserInputMgr->InputValue();
		if (cmn::CheckValidIndex(*pSelMenu, min, max) == false)
		{
			*pSelMenu = 0;
			cmn::ShowMessageAutoNewLine("메뉴를 다시 선택해주세요");
			g_pSystemMgr->PauseProgram();
		}
	}

	bool SceneMgr::InitializeScene()
	{
		m_pScene = new scene::Title;
		return false;
	}

	bool SceneMgr::ChangeScene(SCENE_TYPE type)
	{
		if ( (type <= SCENE_TYPE::NONE) ||
			 (type >= SCENE_TYPE::END) )
		{
			cmn::ShowMessageAutoNewLine("씬 범위에 없는 씬입니다!");
			return false;
		}

		ResetScene();

		switch (type)
		{
		case SCENE_TYPE::TITLE:
			m_pScene = new scene::Title;
			break;
		case SCENE_TYPE::SYNOPSIS:
			m_pScene = new scene::Synopsis;
			break;
		case SCENE_TYPE::INGAME:
			m_pScene = new scene::Ingame;
			break;
		}

		if (m_pScene->Initialize() == SCENE_STATE::INIT_FAIL)
		{
			ResetScene();
			cmn::ShowMessageAutoNewLine("씬 전환에 실패했습니다!");
			return false;
		}

		return true;
	}

	bool SceneMgr::ChangeSubScene(SUB_SCENE_TYPE type, scene::SceneBase** ppSubScene)
	{
		if ( (type <= SUB_SCENE_TYPE::NONE) ||
			 (type >= SUB_SCENE_TYPE::END) )
		{
			cmn::ShowMessageAutoNewLine("씬 범위에 없는 서브 씬입니다!");
			return false;
		}

		ResetSubScene(ppSubScene);

		switch (type)
		{
		case SUB_SCENE_TYPE::STUDY_MAIN:
			*ppSubScene = new scene::StudyMain;
			break;
		case SUB_SCENE_TYPE::STUDY_C:
			*ppSubScene = new scene::StudyC;
			break;
		case SUB_SCENE_TYPE::STUDY_CPP:
			*ppSubScene = new scene::StudyCPP;
			break;
		case SUB_SCENE_TYPE::HUNGER_MAIN:
			*ppSubScene = new scene::HungerMain;
			break;
		case SUB_SCENE_TYPE::SOCIETY_MAIN:
			*ppSubScene = new scene::SocietyMain;
			break;
		}

		if ((*ppSubScene)->Initialize() == SCENE_STATE::INIT_FAIL)
		{
			ResetSubScene(ppSubScene);
			cmn::ShowMessageAutoNewLine("서브 씬 전환에 실패했습니다!");
			return false;
		}

		return true;
	}

	bool SceneMgr::AdjustSubScene(const VecSubSceneType& vecSubSceneType, INT32 selMenu,
		scene::SceneBase** ppSubScene, SCENE_STATE* pSceneState)
	{
		if (selMenu == 0)
		{
			return true;
		}

		SUB_SCENE_TYPE subSceneType = vecSubSceneType[selMenu - 1]();

		if (subSceneType != SUB_SCENE_TYPE::NONE)
		{
			if (ChangeSubScene(subSceneType, ppSubScene) == false)
			{
				*pSceneState = SCENE_STATE::UPDATE_FAIL;
			}
			return false;
		}

		return true;
	}

	SCENE_STATE SceneMgr::BackToPreviousScene(SCENE_STATE subSceneState, scene::SceneBase** ppSubScene, bool* pHold)
	{
		if ( (subSceneState == SCENE_STATE::CHANGE) ||
			 (subSceneState == SCENE_STATE::GOTO_TITLE) )
		{
			ResetSubScene(ppSubScene);
			*pHold = true;

			if (subSceneState == SCENE_STATE::GOTO_TITLE)
			{
				return SCENE_STATE::GOTO_TITLE;
			}
		}

		return SCENE_STATE::UPDATE_SUCCESS;
	}

} // namespace manager end