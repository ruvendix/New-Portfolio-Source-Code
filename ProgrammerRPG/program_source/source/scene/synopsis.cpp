/*
 * <제작 날짜>
 * 2017-11-11
 *
 * <파일 설명>
 * 게임의 시놉시스 씬입니다.
 * 시놉시스는 게임의 개요를 보여줍니다.
 */

#include "scene/synopsis.h"
#include "manager/mgr_linker.h"
#include "file/fileStream.h"

namespace scene
{

	Synopsis::Synopsis()
	{
		m_ppSynopsis = nullptr;
		m_bGameStart = false;
	}

	Synopsis::~Synopsis()
	{
		for (INT32 i = 0; i < 9; ++i)
		{
			cmn::SafeArrayDelete(&m_ppSynopsis[i]);
		}
		cmn::SafeArrayDelete(m_ppSynopsis);
	}

	SCENE_STATE Synopsis::Initialize()
	{
		m_ppSynopsis = new ASCII*[10];
		for (INT32 i = 0; i < 10; ++i)
		{
			m_ppSynopsis[i] = new ASCII[STRING_BUFFER_SIZE];
			cmn::InitializeArrayMemory(m_ppSynopsis[i], STRING_BUFFER_SIZE);
		}

		file::FileStream synopsis;
		synopsis.OpenFileStream("synopsis.txt", "rt");

		for (INT32 i = 0; i < 10; ++i)
		{
			INT32 size = 0;
			synopsis.ReadFileLine(m_ppSynopsis[i], &size);
		}

		synopsis.CloseFileStream();

		return SCENE_STATE::INIT_SUCCESS;
	}

	SCENE_STATE Synopsis::Update()
	{
		if (m_bGameStart)
		{
			return SCENE_STATE::CHANGE;
		}

		return SCENE_STATE::UPDATE_SUCCESS;
	}

	SCENE_STATE Synopsis::Render()
	{
		for (INT i = 0; i < 9; ++i)
		{
			cmn::ShowMessageAutoNewLine(m_ppSynopsis[i]);
			getchar();
		}

		m_bGameStart = true;

		return SCENE_STATE::RENDER_SUCCESS;
	}

	SCENE_STATE Synopsis::Release()
	{
		return SCENE_STATE::RELEASE_SUCCESS;
	}

} // namespace scene end
