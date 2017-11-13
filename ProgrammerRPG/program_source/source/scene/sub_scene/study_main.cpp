/*
 * <���� ��¥>
 * 2017-11-12
 *
 * <���� ����>
 * �����ϴ� ���� ���Դϴ�.
 * �÷��̾�� C���� C++��� �� �ϳ��� ������ �� �ֽ��ϴ�.
 * �� �����ϸ� �ٸ� ���� ���� �۵��ϰ� �˴ϴ�.
 */

#include "scene/sub_scene/study_main.h"
#include "manager/mgr_linker.h"

namespace scene
{

	StudyMain::StudyMain()
	{

	}

	StudyMain::~StudyMain()
	{

	}

	SCENE_STATE StudyMain::Initialize()
	{
		m_vecSubSceneFunc.push_back(std::bind(&StudyMain::_StudyC, this));
		m_vecSubSceneFunc.push_back(std::bind(&StudyMain::_StudyCPP, this));
		return SCENE_STATE::INIT_SUCCESS;
	}

	SCENE_STATE StudyMain::Update()
	{
		if (m_selMenu == 0)
		{
			return SCENE_STATE::UPDATE_SUCCESS;
		}
		else if (m_selMenu == 3)
		{
			return SCENE_STATE::CHANGE;
		}
		else if (m_selMenu == 4)
		{
			return SCENE_STATE::GOTO_TITLE;
		}

		SCENE_STATE subSceneState = SCENE_STATE::UPDATE_SUCCESS;

		// ������� �Է¿� ���� ���� ���� ��ȯ�մϴ�.
		if (m_bHold)
		{
			m_bHold = g_pSceneMgr->AdjustSubScene(m_vecSubSceneFunc, m_selMenu, &m_pNowSubScene, &subSceneState);
		}

		// �ٽ� ���� ������ ���ƿ��� ���� ���� ���� �����ؾ� �մϴ�.
		subSceneState = m_pNowSubScene->Update();
		subSceneState = g_pSceneMgr->BackToPreviousScene(subSceneState, &m_pNowSubScene, &m_bHold);

		return subSceneState;
	}

	SCENE_STATE StudyMain::Render()
	{
		if (m_bHold)
		{
			cmn::ShowMessageAutoNewLine("1. C��� �����ϱ�(ü�� 20�Ҹ�)");
			cmn::ShowMessageAutoNewLine("2. C++��� �����ϱ�(ü�� 60�Ҹ�)");
			cmn::ShowMessageAutoNewLine("3. �ڷ� ����");
			cmn::ShowMessageAutoNewLine("4. Ÿ��Ʋ�� ���ư���");

			g_pSceneMgr->SelectMenu(&m_selMenu, 1, 4);
		}
		else
		{
			m_pNowSubScene->Render();
		}

		return SCENE_STATE::RENDER_SUCCESS;
	}

	SCENE_STATE StudyMain::Release()
	{
		return SCENE_STATE::RELEASE_SUCCESS;
	}

	SUB_SCENE_TYPE StudyMain::_StudyC()
	{
		cmn::ShowMessageAutoNewLine("C�� �����մϴ�.");
		return SUB_SCENE_TYPE::STUDY_C;
	}

	SUB_SCENE_TYPE StudyMain::_StudyCPP()
	{
		cmn::ShowMessageAutoNewLine("C�� �����մϴ�.");
		return SUB_SCENE_TYPE::STUDY_CPP;
	}

} // namespace scene end