/*
 * <작성 날짜>
 * 2017-10-11
 *
 * <파일 설명>
 * 게임의 전반적인 부분을 관리합니다.
 * 특정 객체의 정보를 저장하거나 조작하기도 합니다.
 */

#ifndef EASIEST_GAME_MANAGER_H_
#define EASIEST_GAME_MANAGER_H_

#include "../include/common/cmn_header.h"
#include "../include/common/cmn_type.h"

#include "../object/map.h"
#include "../object/player.h"
#include "../object/bomb.h"

#include "effect_manager.h"

namespace manager
{

	class GameManager
	{
	public:
		static GameManager& ActivateManager();

		INT32             InitializeGame();
		GAME_UPDATE_STATE UpdateGame();
		GAME_RENDER_STATE RenderGame();
		INT32             ReleaseGame();

		const GameState&  DriveGame();

		void  SwapMapObject(const Position2D& oldPos, const Position2D& nowPos);
		void  EnrollMapObjectCollisionValue(INT32* pCollisionValue, const Position2D& objectPos);
		void  EnrollMapObjectForObjectPos(const Position2D& objectPos, const MAP_OBJECT_SHAPE& mapObject);

		// 연산이 끝난 플레이어의 위치로 처리하므로 플레이어의 위치를 넘겨주지 않아도 됨
		BOOL  _CheckPlayerPosInGoal();

		const Position2D& getPlayerPos() const noexcept
		{
			return m_pPlayer->getNowPos();
		}

		INT32 getPlayerBombPower() const noexcept
		{
			return m_pPlayer->getBombPower();
		}

		const LIST<obj::Bomb*>& getListBomb() const noexcept
		{
			return m_pPlayer->getListBomb();
		}

	private:
		GameManager()  = default;
		~GameManager() = default;

		GameManager(const GameManager& rhs)  = delete;
		GameManager(const GameManager&& rhs) = delete;

		GameManager& operator= (const GameManager& rhs)  = delete;
		GameManager& operator= (const GameManager&& rhs) = delete;

		struct ManagerDeleter;

		// 여기에 게임 매니저에서 직접 관리할 오브젝트를 추가하면 됩니다.
		std::unique_ptr<obj::Map>    m_pMap;
		std::unique_ptr<obj::Player> m_pPlayer;

		GameState m_gameState;
	};

} // namespace manager end
namespace mgr = manager;

#endif