/*
 * <�ۼ� ��¥>
 * 2017-10-11
 *
 * <���� ����>
 * ������ �������� �κ��� �����մϴ�.
 * Ư�� ��ü�� ������ �����ϰų� �����ϱ⵵ �մϴ�.
 */

#include "game_manager.h"

#include "../include/common/cmn_function.h"

#include "../manager/collision_manager.h"
#include "../manager/user_input_manager.h"

namespace manager
{

	struct GameManager::ManagerDeleter
	{
		void operator() (GameManager* pGameManager)
		{
			if (pGameManager != nullptr)
			{
				pGameManager->~GameManager();
				cmn::SafeFree(&pGameManager);
			}
		}
	};

	GameManager& GameManager::ActivateManager()
	{
		static std::unique_ptr<GameManager, ManagerDeleter> pGameManager = nullptr;

		if (pGameManager == nullptr)
		{
			std::once_flag flag;
			std::function<void()> allocator = []() { pGameManager.reset(new GameManager); };
			std::call_once(flag, allocator);
		}

		return *pGameManager;
	}

	INT32 GameManager::InitializeGame()
	{
		m_gameState.updateState = GAME_UPDATE_STATE::NONE;
		m_gameState.renderState = GAME_RENDER_STATE::NONE;

		m_pMap = std::make_unique<obj::Map>();
		assert(m_pMap != nullptr);
		m_pMap->Initialize();

		m_pPlayer = std::make_unique<obj::Player>();
		assert(m_pPlayer != nullptr);
		m_pPlayer->Initialize();

		return 0;
	}

	GAME_UPDATE_STATE GameManager::UpdateGame()
	{
		mgr::UserInputManager::ActivateManager().InitializeInput();

		m_pMap->Update();
		INT32 playerUpdateReuslt = m_pPlayer->Update();

		if (static_cast<PLAYER_STATE>(playerUpdateReuslt) == PLAYER_STATE::DIE_BOMB)
		{
			m_pPlayer->setNowPos(m_pMap->getStartPos());
			return GAME_UPDATE_STATE::PLAYER_DIE_BOMB;
		}

		if (_CheckPlayerPosInGoal())
		{
			return GAME_UPDATE_STATE::PLAYER_ARRIVE_GOAL;
		}

		mgr::EffectManager::AcitvateInstance().UpdateEffect();

		return GAME_UPDATE_STATE::NONE;
	}

	GAME_RENDER_STATE GameManager::RenderGame()
	{
		m_pMap->Render();
		m_pPlayer->Render();

		cmn::ShowMessageAutoNewLine("��(A) ��(D) ��(W) �Ʒ�(S) ��ź ����(T) �� �б�(Y) ����(Q)\n");
		printf("�Ŀ�(%d) ", m_pPlayer->getBombPower());
		printf("��ġ ������ ��ź ����(%d)\n", PLAYER_BOMB_MAX_COUNT - m_pPlayer->getBombDropCount());
		printf("����ȭ(%s, %s) ", m_pPlayer->getIsTransparency() ? "����" : "����",
			m_pPlayer->getTransparencyMode() ? "�ߵ�" : "�̹ߵ�");
		printf("�� �б�(%s, %s)\n", m_pPlayer->getIsWallPush() ? "����" : "����",
			m_pPlayer->getIsWallPushMode() ? "�ߵ�" : "�̹ߵ�");
		printf("\n");

		if (m_pPlayer->getIsDropBomb() == false)
		{
			cmn::ShowMessageAutoNewLine("�� �̻� ��ź ���� �Ұ�!");
		}

		mgr::EffectManager::AcitvateInstance().RenderEffect();

		return GAME_RENDER_STATE::NONE;
	}

	INT32 GameManager::ReleaseGame()
	{
		m_pMap->Release();
		m_pPlayer->Release();

		return 0;
	}

	const GameState& GameManager::DriveGame()
	{
		m_gameState.updateState = UpdateGame();
		m_gameState.renderState = RenderGame();

		return m_gameState;
	}

	void GameManager::SwapMapObject(const Position2D& oldPos, const Position2D& nowPos)
	{
		m_pMap->SwapMapObject(oldPos, nowPos);
	}

	void GameManager::EnrollMapObjectCollisionValue(INT32* pCollisionValue, const Position2D& objectPos)
	{
		m_pMap->EnrollMapObjectCollisionValue(pCollisionValue, objectPos);
	}

	void GameManager::EnrollMapObjectForObjectPos(const Position2D& objectPos, const MAP_OBJECT_SHAPE& mapObject)
	{
		m_pMap->EnrollMapObjectForObjectPos(objectPos, mapObject);
	}

	BOOL GameManager::_CheckPlayerPosInGoal()
	{
		if (m_pPlayer->CheckSamePos(getPlayerPos(), m_pMap->getEndPos()))
		{
			return true;
		}

		return false;
	}

} // namespace manager end;