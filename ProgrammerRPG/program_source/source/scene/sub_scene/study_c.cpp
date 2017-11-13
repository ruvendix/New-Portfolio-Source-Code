/*
 * <���� ��¥>
 * 2017-11-13
 *
 * <���� ����>
 * C++�� �����ϴ� ���� ���Դϴ�.
 */

#include "scene/sub_scene/study_c.h"
#include "manager/mgr_linker.h"
#include "file/fileStream.h"
#include "object/player.h"
#include "object/player_info.h"

namespace scene
{

	StudyC::StudyC()
	{
		m_studyState = STUDY_STATE::NONE;
	}

	StudyC::~StudyC()
	{

	}

	SCENE_STATE StudyC::Initialize()
	{
		m_bFirstPage = false;
		m_bLastPage  = false;

		file::FileStream CTable;
		CTable.OpenFileStream("C\\Table.txt", "rt");

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
			CTable.ReadFileLine(strBuffer.strData, &size); // ���� �̸� �б�

			file::FileStream CContent;
			STRING strFullPath = "C\\";
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

	SCENE_STATE StudyC::Update()
	{
		switch (m_selMenu)
		{
		case 1:
			m_studyState = g_pObjMgr->getPlayer()->StudyProgramming(STUDY_TYPE::C, m_vecContents.size());
			break;
		case 2:
			m_studyState = g_pObjMgr->getPlayer()->BackToPreviousPage(STUDY_TYPE::C);
			break;
		case 3:
			return SCENE_STATE::CHANGE;
		case 4:
			return SCENE_STATE::GOTO_TITLE;
		}

		return SCENE_STATE::UPDATE_SUCCESS;
	}

	SCENE_STATE StudyC::Render()
	{
		// C��� ���� ���
		for (INT i = 0; i < 12; ++i)
		{
			cmn::ShowMessageAutoNewLine(m_vecContents[g_pObjMgr->getPlayer()->getPlayerInfo()->getCPage()][i]);
		}

		if (m_studyState == STUDY_STATE::LESS_PAGE)
		{
			cmn::ShowMessageAutoNewLine("ù �������Դϴ�!");
		}
		else if (m_studyState == STUDY_STATE::OVER_PAGE)
		{
			cmn::ShowMessageAutoNewLine("������ �������Դϴ�!");
		}

		cmn::ShowSoftBorderAutoNewLine();
		cmn::ShowMessageAutoNewLine("1. ��� �����ϱ�");
		cmn::ShowMessageAutoNewLine("2. ���� �ܰ�� ����");
		cmn::ShowMessageAutoNewLine("3. �ڷ� ����");
		cmn::ShowMessageAutoNewLine("4. Ÿ��Ʋ�� ���ư���");

		g_pSceneMgr->SelectMenu(&m_selMenu, 1, 4);

		return SCENE_STATE::RENDER_SUCCESS;
	}

	SCENE_STATE StudyC::Release()
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