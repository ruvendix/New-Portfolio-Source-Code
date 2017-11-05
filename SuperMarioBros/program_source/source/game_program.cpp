/*
 * <제작 날짜>
 * 2017-10-24
 *
 * <파일 설명>
 * 게임 프로그램을 작동시키는 함수를 제공합니다.
 */

#include "game_program.h"

#include "manager_linker.h"

void GameProgram::DriveGame()
{
	g_pSystemMgr->HideCursor();
	g_pSystemMgr->AdjustRenderColor(RENDERING_COLOR::LIGHT_WHITE);
	cmn::PauseProgram();
	
	g_pSoundMgr->Initialize();
	g_pSoundMgr->LoadSoundTable("BGMTable.txt", true);
	g_pSoundMgr->LoadSoundTable("SFXTable.txt");
	g_pSoundMgr->PlayOnSound("stage.mp3", true);

	g_pTimeMgr->InitializeFrameTime(true);
	g_pGameMgr->Initialize();

	while (true)
	{
		g_pTimeMgr->AccumulateFrameTime();

		if (g_pTimeMgr->getFrameTimeInterval() > 0.1f)//THIRTY_FRAME * 2)
		{
			cmn::ClearScreen();
			g_pTimeMgr->InitializeFrameTime();

			g_pGameMgr->Update();
			g_pGameMgr->Render();

			if (g_pUserInputMgr->IsInputValue(KEY_Q))
			{
				cmn::ShowMessageAutoNewLine("게임을 종료합니다.");
				break;
			}
		}
	}		

	g_pGameMgr->Release();
	g_pSoundMgr->Release();

	return;
}