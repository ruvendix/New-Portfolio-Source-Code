/*
 * <���� ��¥>
 * 2017-11-12
 *
 * <���� ����>
 * ��ȸ�� �����ϴ� ���� ���Դϴ�.
 * �÷��̾�� ���� �ڵ��¿� ���� ������ ������ �� �ֽ��ϴ�.
 * �ڵ����� ���ٸ� ���� �� �ִ� ���ĵ� ���� �����ϴ�.
 */

#include "scene/sub_scene/society_main.h"
#include "manager/mgr_linker.h"

namespace scene
{

	SocietyMain::SocietyMain()
	{

	}

	SocietyMain::~SocietyMain()
	{

	}

	SCENE_STATE SocietyMain::Initialize()
	{
		return SCENE_STATE::INIT_SUCCESS;
	}

	SCENE_STATE SocietyMain::Update()
	{
		if (m_selMenu == 5)
		{
			return SCENE_STATE::CHANGE;
		}
		else if (m_selMenu == 6)
		{
			return SCENE_STATE::GOTO_TITLE;
		}

		return SCENE_STATE::UPDATE_SUCCESS;
	}

	SCENE_STATE SocietyMain::Render()
	{
		cmn::ShowMessageAutoNewLine("1. ���� ����(�ڵ��� 600)");
		cmn::ShowMessageAutoNewLine("2. �߼ұ�� ����(�ڵ��� 1200)");
		cmn::ShowMessageAutoNewLine("3. ���� ����(�ڵ��� 1500)");
		cmn::ShowMessageAutoNewLine("4. �۷ι� ����(�ڵ��� 2500)");
		cmn::ShowMessageAutoNewLine("5. �ڷ� ����");
		cmn::ShowMessageAutoNewLine("6. Ÿ��Ʋ�� ���ư���");

		g_pSceneMgr->SelectMenu(&m_selMenu, 1, 6);

		return SCENE_STATE::RENDER_SUCCESS;
	}

	SCENE_STATE SocietyMain::Release()
	{
		return SCENE_STATE::RELEASE_SUCCESS;
	}

} // namespace scene end