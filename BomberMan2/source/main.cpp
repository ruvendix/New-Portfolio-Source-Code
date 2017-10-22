/*
 * <작성 날짜>
 * 2017-10-11
 *
 * <파일 설명>
 * 프로그램의 메인 함수입니다.
 * 메인 함수에는 로직이 없으며 중계하는 역할만 합니다.
 * 프로그램을 종료하려면 메인에서 처리하는 게 좋습니다.
 * 대부분의 게임은 타이틀 화면에서 종료하는 기능과
 * 인게임에서 즉시 종료하는 기능이 구현되어있습니다.
 */

#include "include/global_data.h"
#include "include/common/cmn_function.h"

#include "manager/game_manager.h"
#include "manager/time_manager.h"
#include "manager/user_input_manager.h"

int main()
{
	mgr::GameManager::ActivateManager().InitializeGame();
	mgr::TimeManager::ActivateManager().InitializeFrameTime();

	while (true)
	{
		mgr::TimeManager::ActivateManager().MeasureTimePoint(
			mgr::TimeManager::ActivateManager().getStartFrameTime());

		// 시간 측정값이 1프레임 이상일 때만 처리
		if (mgr::TimeManager::ActivateManager().getFrameTime() > THIRTY_FRAME_TIME * 1.6f)
		{
			if (mgr::UserInputManager::ActivateManager().IsInputKey(KEY_Q))
			{
				break;
			}

			mgr::TimeManager::ActivateManager().InitializeFrameTime();

			cmn::ClearScreen();

			GameState gameState = mgr::GameManager::ActivateManager().DriveGame();

			if (gameState.updateState == GAME_UPDATE_STATE::PLAYER_ARRIVE_GOAL)
			{
				cmn::ShowMessageAutoNewLine("목적지에 도착~!\n");
				break;
			}
			else if (gameState.updateState == GAME_UPDATE_STATE::PLAYER_DIE_BOMB)
			{
				//cmn::ShowMessageAutoNewLine("폭탄에 맞아서 시작 지점으로 이동 ㅠㅠ");
				//cmn::PauseProgram();
			}
		}

		mgr::TimeManager::ActivateManager().MeasureTimePoint(
			mgr::TimeManager::ActivateManager().getEndFrameTime());

		// 프레임 시간 연산
		mgr::TimeManager::ActivateManager().CalculateFrameTimeInterval();
	}

	cmn::ShowMessageAutoNewLine("게임이 종료되었습니다.");
	cmn::PauseProgram();
	mgr::GameManager::ActivateManager().ReleaseGame();

	return 0;
}