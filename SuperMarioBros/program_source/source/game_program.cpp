/*
 * <���� ��¥>
 * 2017-10-24
 *
 * <���� ����>
 * ���� ���α׷��� �۵���Ű�� �Լ��� �����մϴ�.
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
				cmn::ShowMessageAutoNewLine("������ �����մϴ�.");
				break;
			}
		}
	}		

	g_pGameMgr->Release();
	g_pSoundMgr->Release();

	return;
}