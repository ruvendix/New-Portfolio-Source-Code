/*
 * <���� ��¥>
 * 2017-11-11
 *
 * <���� ����>
 * ������ �ΰ��� ���Դϴ�.
 * �ΰ��ӿ����� �÷��̾ ������ �� �� �ֽ��ϴ�.
 */

#include "scene/ingame.h"
#include "manager/mgr_linker.h"
#include "object/player.h"

namespace scene
{

	Ingame::Ingame()
	{
		m_vecSubSceneFunc.reserve(5);
		m_pNowSubScene = nullptr;
	}

	Ingame::~Ingame()
	{
		cmn::SafeDelete(&m_pNowSubScene);
		m_vecSubSceneFunc.clear();
	}

	SCENE_STATE Ingame::Initialize()
	{
		m_vecSubSceneFunc.push_back(std::bind(&Ingame::_GotoStudy, this));
		m_vecSubSceneFunc.push_back(std::bind(&Ingame::_GotoHunger, this));
		m_vecSubSceneFunc.push_back(std::bind(&Ingame::_GotoSociety, this));

		g_pObjMgr->InitializeData();
		if (g_pObjMgr->InitializePlayer() == OBJECT_STATE::INIT_FAIL)
		{
			return SCENE_STATE::INIT_FAIL;
		}

		return SCENE_STATE::INIT_SUCCESS;
	}

	SCENE_STATE Ingame::Update()
	{
		if (m_selMenu == 0)
		{
			return SCENE_STATE::UPDATE_SUCCESS;
		}
		// ������ �����մϴ�.
		else if (m_selMenu == 4)
		{
			// ���� ����
		}
		// Ÿ��Ʋ�� ���ư��ϴ�.
		else if (m_selMenu == 5)
		{
			return SCENE_STATE::GOTO_TITLE;
		}

		g_pObjMgr->getPlayer()->Update();

		SCENE_STATE subSceneState = SCENE_STATE::UPDATE_SUCCESS;

		// ������� �Է¿� ���� ���� ���� ��ȯ�մϴ�.
		if (m_bHold)
		{
			m_bHold = g_pSceneMgr->AdjustSubScene(m_vecSubSceneFunc, m_selMenu, &m_pNowSubScene, &subSceneState);
		}

		// �ٽ� ���� ������ ���ƿ��� ���� ���� ���� �����ؾ� �մϴ�.
		subSceneState = m_pNowSubScene->Update();
		subSceneState = g_pSceneMgr->BackToPreviousScene(subSceneState, &m_pNowSubScene, &m_bHold);
		
		g_pUserInputMgr->FlushBuffer();

		return subSceneState;
	}

	SCENE_STATE Ingame::Render()
	{
		cmn::ShowHardBorderAutoNewLine();
		cmn::ShowMessageAutoNewLine("�ΰ��� ������");
		cmn::ShowHardBorderAutoNewLine();

		g_pObjMgr->getPlayer()->Render();

		if (m_bHold)
		{
			cmn::ShowMessageAutoNewLine("1. �ڵ� ����");
			cmn::ShowMessageAutoNewLine("2. �� ����");
			cmn::ShowMessageAutoNewLine("3. ��ȸ ����");
			cmn::ShowMessageAutoNewLine("4. �����ϱ�");
			cmn::ShowMessageAutoNewLine("5. Ÿ��Ʋ�� ���ư���");

			g_pSceneMgr->SelectMenu(&m_selMenu, 1, 5);
		}
		else
		{
			m_pNowSubScene->Render();
		}

		return SCENE_STATE::RENDER_SUCCESS;
	}

	SCENE_STATE Ingame::Release()
	{
		g_pSceneMgr->ResetSubScene(&m_pNowSubScene);
		g_pObjMgr->ReleasePlayer();
		return SCENE_STATE::RELEASE_SUCCESS;
	}

	SUB_SCENE_TYPE Ingame::_GotoStudy()
	{
		cmn::ShowMessageAutoNewLine("���θ� �մϴ�.");
		return SUB_SCENE_TYPE::STUDY_MAIN;
	}

	SUB_SCENE_TYPE Ingame::_GotoHunger()
	{
		cmn::ShowMessageAutoNewLine("������ �Խ��ϴ�.");
		return SUB_SCENE_TYPE::HUNGER_MAIN;
	}

	SUB_SCENE_TYPE Ingame::_GotoSociety()
	{
		cmn::ShowMessageAutoNewLine("��ȸ�� �����մϴ�.");
		return SUB_SCENE_TYPE::SOCIETY_MAIN;
	}

} // namespace scene end