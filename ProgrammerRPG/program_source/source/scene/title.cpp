/*
 * <제작 날짜>
 * 2017-11-11
 *
 * <파일 설명>
 * 게임의 타이틀 씬입니다.
 * 타이틀에서는 게임 시작, 불러오기, 종료가 가능합니다.
 */

#include "scene/title.h"

#include "manager/mgr_linker.h"
#include "file/fileStream.h"

namespace scene
{

	Title::Title()
	{
		m_ppTitle = nullptr;
		m_selMenu = 0;
		m_vecTitleFunc.reserve(5);
	}

	Title::~Title()
	{
		for (INT32 i = 0; i < 18; ++i)
		{
			cmn::SafeArrayDelete(&m_ppTitle[i]);
		}
		cmn::SafeArrayDelete(m_ppTitle);

		m_vecTitleFunc.clear();
	}

	SCENE_STATE Title::Initialize()
	{
		m_vecTitleFunc.push_back(std::bind(&Title::NewGame, this));
		m_vecTitleFunc.push_back(std::bind(&Title::LoadUser, this));
		m_vecTitleFunc.push_back(std::bind(&Title::ExitGame, this));

		m_ppTitle = new ASCII*[18];
		for (INT32 i = 0; i < 18; ++i)
		{
			m_ppTitle[i] = new ASCII[STRING_BUFFER_SIZE];
			cmn::InitializeArrayMemory(m_ppTitle[i], STRING_BUFFER_SIZE);
		}

		file::FileStream title;
		title.OpenFileStream("title.txt", "rt");

		for (INT32 i = 0; i < 18; ++i)
		{
			INT32 size = 0;
			title.ReadFileLine(m_ppTitle[i], &size);
		}

		title.CloseFileStream();

		return SCENE_STATE::INIT_SUCCESS;
	}

	SCENE_STATE Title::Update()
	{
		if (m_selMenu == 0)
		{
			return SCENE_STATE::UPDATE_SUCCESS;
		}

		g_pUserInputMgr->FlushBuffer();
		return m_vecTitleFunc[m_selMenu - 1]();
	}

	SCENE_STATE Title::Render()
	{
		cmn::ShowHardBorderAutoNewLine();
		for (INT32 i = 0; i < 16; ++i)
		{
			cmn::ShowMessageAutoNewLine(m_ppTitle[i]);
		}
		cmn::ShowHardBorderAutoNewLine();

		cmn::ShowMessageAutoNewLine("1. 새 게임");
		cmn::ShowMessageAutoNewLine("2. 불러오기");
		cmn::ShowMessageAutoNewLine("3. 종료");
		
		// 프레임으로 진행되는 게 아니므로 입력도 렌더링에서 처리합니다.
		g_pSceneMgr->SelectMenu(&m_selMenu, 1, 3);

		return SCENE_STATE::RENDER_SUCCESS;
	}

	SCENE_STATE Title::Release()
	{
		return SCENE_STATE::RELEASE_SUCCESS;
	}

	SCENE_STATE Title::NewGame()
	{
		cmn::ShowHardBorderAutoNewLine();
		cmn::ShowMessageAutoNewLine("새 게임 선택!");
		cmn::ShowHardBorderAutoNewLine();
		return SCENE_STATE::CHANGE;
	}

	SCENE_STATE Title::LoadUser()
	{
		cmn::ShowHardBorderAutoNewLine();
		cmn::ShowMessageAutoNewLine("불러오기 선택!");
		return SCENE_STATE::UPDATE_SUCCESS;
	}

	SCENE_STATE Title::ExitGame()
	{
		cmn::ShowHardBorderAutoNewLine();
		cmn::ShowMessageAutoNewLine("종료 선택!");
		return SCENE_STATE::GAME_EXIT;
	}

} // namespace scene end