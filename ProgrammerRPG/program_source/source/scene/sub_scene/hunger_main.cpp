/*
 * <제작 날짜>
 * 2017-11-12
 *
 * <파일 설명>
 * 배고픔을 달래는 메인 씬입니다.
 * 플레이어는 현재 코딩력에 따라 음식을 선택할 수 있습니다.
 * 코딩력이 낮다면 먹을 수 있는 음식도 별로 없습니다.
 */

#include "scene/sub_scene/hunger_main.h"
#include "manager/mgr_linker.h"
#include "object/player.h"
#include "object/player_info.h"

namespace scene
{

	HungerMain::HungerMain()
	{
		m_vecSubSceneFunc.reserve(5);
	}

	HungerMain::~HungerMain()
	{

	}

	SCENE_STATE HungerMain::Initialize()
	{
		m_vecSubSceneFunc.push_back(std::bind(&HungerMain::_EatConvenience, this));
		m_vecSubSceneFunc.push_back(std::bind(&HungerMain::_EatFamous, this));
		m_vecSubSceneFunc.push_back(std::bind(&HungerMain::_EastRestaurant, this));

		return SCENE_STATE::INIT_SUCCESS;
	}

	SCENE_STATE HungerMain::Update()
	{
		if (m_selMenu == 0)
		{
			return SCENE_STATE::UPDATE_SUCCESS;
		}
		else if (m_selMenu == 4)
		{
			return SCENE_STATE::CHANGE;
		}
		else if (m_selMenu == 5)
		{
			return SCENE_STATE::GOTO_TITLE;
		}

		m_vecSubSceneFunc[m_selMenu - 1]();

		return SCENE_STATE::UPDATE_SUCCESS;
	}

	SCENE_STATE HungerMain::Render()
	{
		cmn::ShowMessageAutoNewLine("1. 편의점(코딩력 200)");
		cmn::ShowMessageAutoNewLine("2. 맛집(코딩력 800)");
		cmn::ShowMessageAutoNewLine("3. 레스토랑(코딩력 1600)");
		cmn::ShowMessageAutoNewLine("4. 뒤로 가기");
		cmn::ShowMessageAutoNewLine("5. 타이틀로 돌아가기");

		g_pSceneMgr->SelectMenu(&m_selMenu, 1, 5);

		return SCENE_STATE::RENDER_SUCCESS;
	}

	SCENE_STATE HungerMain::Release()
	{
		return SCENE_STATE::RELEASE_SUCCESS;
	}

	SUB_SCENE_TYPE HungerMain::_EatConvenience()
	{
		obj::Player*     pPlayer     = g_pObjMgr->getPlayer();
		obj::PlayerInfo* pPlayerInfo = pPlayer->getPlayerInfo();

		if (pPlayerInfo->getCodingPower() < 200)
		{
			cmn::ShowMessageAutoNewLine("코딩력이 부족합니다!");
			return SUB_SCENE_TYPE::NONE;
		}
		else if (pPlayerInfo->getAct() <= 0)
		{
			cmn::ShowMessageAutoNewLine("행동력이 부족합니다!");
			return SUB_SCENE_TYPE::NONE;
		}
		else if (pPlayer->FullHP())
		{
			cmn::ShowMessageAutoNewLine("체력이 가득 찼습니다!");
			return SUB_SCENE_TYPE::NONE;
		}

		pPlayer->RecoverHP(30);
		pPlayer->DecreaseAct();
		cmn::ShowMessageAutoNewLine("체력이 30회복되었습니다!");
		return SUB_SCENE_TYPE::HUNGER_CONVENIENCE_STORE;
	}

	SUB_SCENE_TYPE HungerMain::_EatFamous()
	{
		obj::Player*     pPlayer     = g_pObjMgr->getPlayer();
		obj::PlayerInfo* pPlayerInfo = pPlayer->getPlayerInfo();

		if (pPlayerInfo->getCodingPower() < 800)
		{
			cmn::ShowMessageAutoNewLine("코딩력이 부족합니다!");
			return SUB_SCENE_TYPE::NONE;
		}
		else if (pPlayerInfo->getAct() <= 0)
		{
			cmn::ShowMessageAutoNewLine("행동력이 부족합니다!");
			return SUB_SCENE_TYPE::NONE;
		}
		else if (pPlayer->FullHP())
		{
			cmn::ShowMessageAutoNewLine("체력이 가득 찼습니다!");
			return SUB_SCENE_TYPE::NONE;
		}

		pPlayer->RecoverHP(120);
		pPlayer->DecreaseAct();
		cmn::ShowMessageAutoNewLine("체력이 120회복되었습니다!");
		return SUB_SCENE_TYPE::HUNGER_FAMOUS;
	}

	SUB_SCENE_TYPE HungerMain::_EastRestaurant()
	{
		obj::Player*     pPlayer     = g_pObjMgr->getPlayer();
		obj::PlayerInfo* pPlayerInfo = pPlayer->getPlayerInfo();

		if (pPlayerInfo->getCodingPower() < 1600)
		{
			cmn::ShowMessageAutoNewLine("코딩력이 부족합니다!");
			return SUB_SCENE_TYPE::NONE;
		}
		else if (pPlayerInfo->getAct() <= 0)
		{
			cmn::ShowMessageAutoNewLine("행동력이 부족합니다!");
			return SUB_SCENE_TYPE::NONE;
		}
		else if (pPlayer->FullHP())
		{
			cmn::ShowMessageAutoNewLine("체력이 가득 찼습니다!");
			return SUB_SCENE_TYPE::NONE;
		}

		pPlayer->RecoverHP(300);
		pPlayer->DecreaseAct();
		cmn::ShowMessageAutoNewLine("체력이 300회복되었습니다!");
		return SUB_SCENE_TYPE::HUNGER_RESTARUANT;
	}

} // namespace scene end