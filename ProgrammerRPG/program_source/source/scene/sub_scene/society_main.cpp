/*
 * <제작 날짜>
 * 2017-11-12
 *
 * <파일 설명>
 * 사회로 진출하는 메인 씬입니다.
 * 플레이어는 현재 코딩력에 따라 음식을 선택할 수 있습니다.
 * 코딩력이 낮다면 먹을 수 있는 음식도 별로 없습니다.
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
		cmn::ShowMessageAutoNewLine("1. 인턴 진출(코딩력 600)");
		cmn::ShowMessageAutoNewLine("2. 중소기업 진출(코딩력 1200)");
		cmn::ShowMessageAutoNewLine("3. 대기업 진출(코딩력 1500)");
		cmn::ShowMessageAutoNewLine("4. 글로벌 진출(코딩력 2500)");
		cmn::ShowMessageAutoNewLine("5. 뒤로 가기");
		cmn::ShowMessageAutoNewLine("6. 타이틀로 돌아가기");

		g_pSceneMgr->SelectMenu(&m_selMenu, 1, 6);

		return SCENE_STATE::RENDER_SUCCESS;
	}

	SCENE_STATE SocietyMain::Release()
	{
		return SCENE_STATE::RELEASE_SUCCESS;
	}

} // namespace scene end