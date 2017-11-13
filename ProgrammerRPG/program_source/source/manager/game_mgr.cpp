/*
 * <제작 날짜>
 * 2017-11-11
 *
 * <파일 설명>
 * 게임의 흐름을 관리합니다.
 */

#include "manager/game_mgr.h"
#include "manager/mgr_linker.h"

#include "scene/title.h"

SCENE_STATE GameMgr::Initialize()
{
	g_pSystemMgr->FixCMDArea(120, 30);

	m_nowSceneType = SCENE_TYPE::NONE;
	g_pSceneMgr->InitializeScene();
	m_pNowScene = g_pSceneMgr->getScene();
	m_pNowScene->Initialize();
	m_nowSceneType = SCENE_TYPE::TITLE;
	return SCENE_STATE::INIT_SUCCESS;
}

SCENE_STATE GameMgr::Update()
{
	cmn::ShowMessageAutoNewLine("씬 전환을 테스트합니다.");

	SCENE_STATE sceneState = m_pNowScene->Update();

	if (sceneState != SCENE_STATE::UPDATE_SUCCESS)
	{
		// 현재 메인 씬을 전환합니다.
		// 예를 들어 현재 씬이 타이틀인데 씬 이동이 발생한다면 시놉시스 씬으로 전환됩니다.
		switch (m_nowSceneType)
		{
		case SCENE_TYPE::TITLE:
			if (sceneState == SCENE_STATE::GAME_EXIT)
			{
				return SCENE_STATE::GAME_EXIT;
			}
			m_nowSceneType = SCENE_TYPE::SYNOPSIS;
			break;
		case SCENE_TYPE::SYNOPSIS:
			m_nowSceneType = SCENE_TYPE::INGAME;
			break;
		case SCENE_TYPE::INGAME:
			if (sceneState == SCENE_STATE::GOTO_TITLE)
			{
				m_nowSceneType = SCENE_TYPE::TITLE;
			}
			break;
		}

		if (g_pSceneMgr->ChangeScene(m_nowSceneType) == false)
		{
			return SCENE_STATE::UPDATE_FAIL;
		}
		m_pNowScene = g_pSceneMgr->getScene();
	}

	return SCENE_STATE::UPDATE_SUCCESS;
}

SCENE_STATE GameMgr::Render()
{
	m_pNowScene->Render();
	g_pSystemMgr->ClearScreen();
	return SCENE_STATE::RENDER_SUCCESS;
}

SCENE_STATE GameMgr::Release()
{
	m_pNowScene->Release();
	g_pSceneMgr->ResetScene();
	return SCENE_STATE::RELEASE_SUCCESS;
}