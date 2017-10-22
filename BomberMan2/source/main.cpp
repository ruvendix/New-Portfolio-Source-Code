/*
 * <�ۼ� ��¥>
 * 2017-10-11
 *
 * <���� ����>
 * ���α׷��� ���� �Լ��Դϴ�.
 * ���� �Լ����� ������ ������ �߰��ϴ� ���Ҹ� �մϴ�.
 * ���α׷��� �����Ϸ��� ���ο��� ó���ϴ� �� �����ϴ�.
 * ��κ��� ������ Ÿ��Ʋ ȭ�鿡�� �����ϴ� ��ɰ�
 * �ΰ��ӿ��� ��� �����ϴ� ����� �����Ǿ��ֽ��ϴ�.
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

		// �ð� �������� 1������ �̻��� ���� ó��
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
				cmn::ShowMessageAutoNewLine("�������� ����~!\n");
				break;
			}
			else if (gameState.updateState == GAME_UPDATE_STATE::PLAYER_DIE_BOMB)
			{
				//cmn::ShowMessageAutoNewLine("��ź�� �¾Ƽ� ���� �������� �̵� �Ф�");
				//cmn::PauseProgram();
			}
		}

		mgr::TimeManager::ActivateManager().MeasureTimePoint(
			mgr::TimeManager::ActivateManager().getEndFrameTime());

		// ������ �ð� ����
		mgr::TimeManager::ActivateManager().CalculateFrameTimeInterval();
	}

	cmn::ShowMessageAutoNewLine("������ ����Ǿ����ϴ�.");
	cmn::PauseProgram();
	mgr::GameManager::ActivateManager().ReleaseGame();

	return 0;
}