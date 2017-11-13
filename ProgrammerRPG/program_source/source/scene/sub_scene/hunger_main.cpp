/*
 * <���� ��¥>
 * 2017-11-12
 *
 * <���� ����>
 * ������� �޷��� ���� ���Դϴ�.
 * �÷��̾�� ���� �ڵ��¿� ���� ������ ������ �� �ֽ��ϴ�.
 * �ڵ����� ���ٸ� ���� �� �ִ� ���ĵ� ���� �����ϴ�.
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
		cmn::ShowMessageAutoNewLine("1. ������(�ڵ��� 200)");
		cmn::ShowMessageAutoNewLine("2. ����(�ڵ��� 800)");
		cmn::ShowMessageAutoNewLine("3. �������(�ڵ��� 1600)");
		cmn::ShowMessageAutoNewLine("4. �ڷ� ����");
		cmn::ShowMessageAutoNewLine("5. Ÿ��Ʋ�� ���ư���");

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
			cmn::ShowMessageAutoNewLine("�ڵ����� �����մϴ�!");
			return SUB_SCENE_TYPE::NONE;
		}
		else if (pPlayerInfo->getAct() <= 0)
		{
			cmn::ShowMessageAutoNewLine("�ൿ���� �����մϴ�!");
			return SUB_SCENE_TYPE::NONE;
		}
		else if (pPlayer->FullHP())
		{
			cmn::ShowMessageAutoNewLine("ü���� ���� á���ϴ�!");
			return SUB_SCENE_TYPE::NONE;
		}

		pPlayer->RecoverHP(30);
		pPlayer->DecreaseAct();
		cmn::ShowMessageAutoNewLine("ü���� 30ȸ���Ǿ����ϴ�!");
		return SUB_SCENE_TYPE::HUNGER_CONVENIENCE_STORE;
	}

	SUB_SCENE_TYPE HungerMain::_EatFamous()
	{
		obj::Player*     pPlayer     = g_pObjMgr->getPlayer();
		obj::PlayerInfo* pPlayerInfo = pPlayer->getPlayerInfo();

		if (pPlayerInfo->getCodingPower() < 800)
		{
			cmn::ShowMessageAutoNewLine("�ڵ����� �����մϴ�!");
			return SUB_SCENE_TYPE::NONE;
		}
		else if (pPlayerInfo->getAct() <= 0)
		{
			cmn::ShowMessageAutoNewLine("�ൿ���� �����մϴ�!");
			return SUB_SCENE_TYPE::NONE;
		}
		else if (pPlayer->FullHP())
		{
			cmn::ShowMessageAutoNewLine("ü���� ���� á���ϴ�!");
			return SUB_SCENE_TYPE::NONE;
		}

		pPlayer->RecoverHP(120);
		pPlayer->DecreaseAct();
		cmn::ShowMessageAutoNewLine("ü���� 120ȸ���Ǿ����ϴ�!");
		return SUB_SCENE_TYPE::HUNGER_FAMOUS;
	}

	SUB_SCENE_TYPE HungerMain::_EastRestaurant()
	{
		obj::Player*     pPlayer     = g_pObjMgr->getPlayer();
		obj::PlayerInfo* pPlayerInfo = pPlayer->getPlayerInfo();

		if (pPlayerInfo->getCodingPower() < 1600)
		{
			cmn::ShowMessageAutoNewLine("�ڵ����� �����մϴ�!");
			return SUB_SCENE_TYPE::NONE;
		}
		else if (pPlayerInfo->getAct() <= 0)
		{
			cmn::ShowMessageAutoNewLine("�ൿ���� �����մϴ�!");
			return SUB_SCENE_TYPE::NONE;
		}
		else if (pPlayer->FullHP())
		{
			cmn::ShowMessageAutoNewLine("ü���� ���� á���ϴ�!");
			return SUB_SCENE_TYPE::NONE;
		}

		pPlayer->RecoverHP(300);
		pPlayer->DecreaseAct();
		cmn::ShowMessageAutoNewLine("ü���� 300ȸ���Ǿ����ϴ�!");
		return SUB_SCENE_TYPE::HUNGER_RESTARUANT;
	}

} // namespace scene end