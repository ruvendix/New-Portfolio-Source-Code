/*
 * <제작 날짜>
 * 2017-11-12
 *
 * <파일 설명>
 * C언어를 공부하는 서브 씬입니다.
 */

#include "scene/sub_scene/study_cpp.h"
#include "manager/mgr_linker.h"
#include "file/fileStream.h"
#include "object/player.h"
#include "object/player_info.h"

namespace scene
{

	StudyCPP::StudyCPP()
	{
		m_studyState = STUDY_STATE::NONE;
	}

	StudyCPP::~StudyCPP()
	{

	}

	SCENE_STATE StudyCPP::Initialize()
	{
		m_bFirstPage = false;
		m_bLastPage  = false;

		file::FileStream CTable;
		CTable.OpenFileStream("CPP\\Table.txt", "rt");

		INT32        size;
		StringBuffer strBuffer;
		ASCII*       pStop = nullptr;
		cmn::InitializeArrayMemory(strBuffer.strData, _countof(strBuffer.strData));
		CTable.ReadFileLine(strBuffer.strData, &size);
		INT32 count = cmn::ConvertStringToInteger(strBuffer.strData, size, &pStop);
		m_vecContents.reserve(count);
		
		for (INT i = 0; i < count; ++i)
		{
			cmn::InitializeArrayMemory(strBuffer.strData, _countof(strBuffer.strData));
			CTable.ReadFileLine(strBuffer.strData, &size); // 파일 이름 읽기

			file::FileStream CContent;
			STRING strFullPath = "CPP\\";
			strFullPath += strBuffer.strData;
			CContent.OpenFileStream(strFullPath, "rt");

			ASCII** ppBuffer = new ASCII*[16];
			for (INT j = 0; j < 16; ++j)
			{
				ppBuffer[j] = new ASCII[STRING_BUFFER_SIZE];
				cmn::InitializeArrayMemory(ppBuffer[j], STRING_BUFFER_SIZE);
			}

			for (INT j = 0; j < 16; ++j)
			{
				CContent.ReadFileLine(ppBuffer[j], &size);
			}

			m_vecContents.push_back(ppBuffer);
			CContent.CloseFileStream();
		}

		CTable.CloseFileStream();
		return SCENE_STATE::INIT_SUCCESS;
	}

	SCENE_STATE StudyCPP::Update()
	{
		switch (m_selMenu)
		{
		case 1:
			m_studyState = g_pObjMgr->getPlayer()->StudyProgramming(STUDY_TYPE::CPP, m_vecContents.size());
			break;
		case 2:
			m_studyState = g_pObjMgr->getPlayer()->BackToPreviousPage(STUDY_TYPE::CPP);
			break;
		case 3:
			return SCENE_STATE::CHANGE;
		case 4:
			return SCENE_STATE::GOTO_TITLE;
		}

		return SCENE_STATE::UPDATE_SUCCESS;
	}

	SCENE_STATE StudyCPP::Render()
	{
		// C언어 내용 출력
		for (INT i = 0; i < 12; ++i)
		{
			cmn::ShowMessageAutoNewLine(m_vecContents[g_pObjMgr->getPlayer()->getPlayerInfo()->getCPPPage()][i]);
		}

		if (m_studyState == STUDY_STATE::LESS_PAGE)
		{
			cmn::ShowMessageAutoNewLine("첫 페이지입니다!");
		}
		else if (m_studyState == STUDY_STATE::OVER_PAGE)
		{
			cmn::ShowMessageAutoNewLine("마지막 페이지입니다!");
		}

		cmn::ShowSoftBorderAutoNewLine();
		cmn::ShowMessageAutoNewLine("1. 계속 공부하기");
		cmn::ShowMessageAutoNewLine("2. 이전 단계로 가기");
		cmn::ShowMessageAutoNewLine("3. 뒤로 가기");
		cmn::ShowMessageAutoNewLine("4. 타이틀로 돌아가기");

		g_pSceneMgr->SelectMenu(&m_selMenu, 1, 4);

		return SCENE_STATE::RENDER_SUCCESS;
	}

	SCENE_STATE StudyCPP::Release()
	{
		if (m_vecContents.empty() == false)
		{
			for (INT i = 0; i < static_cast<INT32>(m_vecContents.size()); ++i)
			{
				for (INT j = 0; j < 16; ++j)
				{
					cmn::SafeArrayDelete(&m_vecContents[i][j]);
				}
				cmn::SafeArrayDelete(m_vecContents[i]);
			}
		}
		m_vecContents.clear();
		return SCENE_STATE::RELEASE_SUCCESS;
	}

} // namespace scene end