/*
 * <�ۼ� ��¥>
 * 2017-10-11
 *
 * <���� ����>
 * ������ �������� �κ��� �����մϴ�.
 * Ư�� ��ü�� ������ �����ϰų� �����ϱ⵵ �մϴ�.
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

		// ������ ���� �÷��̾��� ��ġ�� ó���ϹǷ� �÷��̾��� ��ġ�� �Ѱ����� �ʾƵ� ��
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

		// ���⿡ ���� �Ŵ������� ���� ������ ������Ʈ�� �߰��ϸ� �˴ϴ�.
		std::unique_ptr<obj::Map>    m_pMap;
		std::unique_ptr<obj::Player> m_pPlayer;

		GameState m_gameState;
	};

} // namespace manager end
namespace mgr = manager;

#endif