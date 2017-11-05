/*
 * <���� ��¥>
 * 2017-10-24
 *
 * <���� ����>
 * ���� ���α׷��� �帧�� �����մϴ�.
 */

#ifndef SIDESCROLLING__GAME_MANAGER_H_
#define SIDESCROLLING__GAME_MANAGER_H_

#include "common.h"

namespace object
{
	class Stage;
	class Player;
} 

namespace UI
{
	class PlayerHUD;
}

namespace manager
{

	class GameMgr
	{
		DEFINE_SINGLETON_CLASS(GameMgr);
	public:
		SCENE_STATE Initialize();
		SCENE_STATE Update();
		SCENE_STATE Render();
		SCENE_STATE Release();
		SCENE_STATE ClearStage();

		bool _JudgeGameState();

	private:
		std::shared_ptr<obj::Stage>       m_pStage;
		std::shared_ptr<UI::PlayerHUD>    m_pPlayerHUD;

		// �÷��̾��� ����� �����ϴ��� �Ǵ��մϴ�.
		bool                              m_bPlayerDie;
	};

} // namespace manager end

#endif