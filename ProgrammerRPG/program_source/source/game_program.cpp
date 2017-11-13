/*
 * <제작 날짜>
 * 2017-11-11
 *
 * <파일 설명>
 * 게임 매니저를 실행해줍니다.
 */

#include "game_program.h"
#include "manager/game_mgr.h"
#include "manager/mgr_linker.h"

void GamePgm::DriveGame()
{
	GameMgr* pGameMgr = &GameMgr::ObtainInstance();

	if (pGameMgr->Initialize() == SCENE_STATE::INIT_FAIL)
	{
		return;
	}

	while (true)
	{
		SCENE_STATE sceneState = pGameMgr->Update();

		if ( (sceneState == SCENE_STATE::UPDATE_FAIL) ||
			 (sceneState == SCENE_STATE::GAME_EXIT) )
		{
			break;
		}

		pGameMgr->Render();
	}

	pGameMgr->Release();
	g_pSystemMgr->PauseProgram();
}