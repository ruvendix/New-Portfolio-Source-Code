/*
 * <���� ��¥>
 * 2017-11-11
 *
 * <���� ����>
 * ���� �Ŵ����� �������ݴϴ�.
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