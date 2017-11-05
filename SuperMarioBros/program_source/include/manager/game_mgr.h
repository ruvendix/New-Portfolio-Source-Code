/*
 * <제작 날짜>
 * 2017-10-24
 *
 * <파일 설명>
 * 게임 프로그램의 흐름을 관리합니다.
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

		// 플레이어의 목숨이 존재하는지 판단합니다.
		bool                              m_bPlayerDie;
	};

} // namespace manager end

#endif