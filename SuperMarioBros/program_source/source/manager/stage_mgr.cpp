/*
 * <���� ��¥>
 * 2017-10-25
 *
 * <���� ����>
 * ���������� ���� ���� �� ����� �����մϴ�.
 */

#include "stage_mgr.h"

#include "manager_linker.h"
#include "object/stage.h"
#include "object/tile_info.h"

namespace manager
{
	void StageMgr::Initialize()
	{
		m_pStageInfo = nullptr;
		m_pStage     = nullptr;

		m_stageCount = 0;
		m_nowStage   = 1;
	}

	void StageMgr::LoadStageList()
	{
		STRING strFileName = "StageList.txt";
		g_pFileMgr->OpenFileStream(strFileName, "rt");

		INT32 lineSize = 0;
		g_pFileMgr->ReadFileLine(&m_stageCount, &lineSize);
		m_stageCount -= '0';
		assert(m_stageCount > 0);

		// �������� ������ŭ �����Ҵ��մϴ�.
		m_pStageInfo = new StageInfo[m_stageCount];
		cmn::InitializeArrayMemory(m_pStageInfo, m_stageCount);
		
		// �ؽ�Ʈ ���Ͽ� �ִ� ������ ���ڿ��̹Ƿ� ���ڿ� ���۸� �Ҵ��ؼ�
		// �о�;� �մϴ�. ��ȯ�� �ʿ��� ���� ��ȯ ������ ��Ĩ�ϴ�.
		for (INT32 i = 0; i < m_stageCount; ++i)
		{
			ASCII strBuffer[STRING_BUFFER_SIZE] = "";
			g_pFileMgr->ReadFileLine(strBuffer, &lineSize);
			m_pStageInfo[i].name = strBuffer;
			cmn::InitializeArrayMemory(strBuffer, STRING_BUFFER_SIZE);

			ASCII* pStop = nullptr;
			g_pFileMgr->ReadFileLine(strBuffer, &lineSize);
			m_pStageInfo[i].limitTime = cmn::ConvertStringToInteger(strBuffer, lineSize, &pStop);
			cmn::InitializeArrayMemory(strBuffer, STRING_BUFFER_SIZE);

			g_pFileMgr->ReadFileLine(strBuffer, &lineSize);
			m_pStageInfo[i].height = cmn::ConvertStringToInteger(strBuffer, lineSize, &pStop);
			cmn::InitializeArrayMemory(strBuffer, STRING_BUFFER_SIZE);

			g_pFileMgr->ReadFileLine(strBuffer, &lineSize);
			m_pStageInfo[i].width = cmn::ConvertStringToInteger(strBuffer, lineSize, &pStop);
			cmn::InitializeArrayMemory(strBuffer, STRING_BUFFER_SIZE);

			g_pFileMgr->ReadFileLine(strBuffer, &lineSize);
			m_pStageInfo[i].heightBorder = cmn::ConvertStringToInteger(strBuffer, lineSize, &pStop);
			cmn::InitializeArrayMemory(strBuffer, STRING_BUFFER_SIZE);

			g_pFileMgr->ReadFileLine(strBuffer, &lineSize);
			m_pStageInfo[i].widthBorder = cmn::ConvertStringToInteger(strBuffer, lineSize, &pStop);
			cmn::InitializeArrayMemory(strBuffer, STRING_BUFFER_SIZE);

			g_pFileMgr->ReadFileLine(strBuffer, &lineSize);
			m_pStageInfo[i].heightBorderRenderBegin = cmn::ConvertStringToInteger(strBuffer, lineSize, &pStop);
			cmn::InitializeArrayMemory(strBuffer, STRING_BUFFER_SIZE);
		}

		g_pFileMgr->CloseFileStream();
	}

	void StageMgr::ResetStage()
	{
		m_pStage->Release();
		m_pStage->Initialize();
	}

	void StageMgr::CreateItem(obj::TileInfo* pTileInfo, bool bGrowth)
	{
		g_pRandomMgr->CreateGenerator();
		INT32 itemAppear = g_pRandomMgr->GenerateInt(0, 100);

		Position2D itemPos = *pTileInfo->getNowPos();

		if (bGrowth)
		{
			et_math::SubtractPosY(1, &itemPos);
			pTileInfo = getStage()->getTileInfo(itemPos);
		}

		if (itemAppear <= 70) // ������ ���� Ȯ��
		{
			itemAppear = g_pRandomMgr->GenerateInt(0, 100);

			if (itemAppear <= 70) // �Ŵ�ȭ ������ ���� Ȯ��
			{
				m_pStage->ChangeTileInfo(itemPos, TILE_TYPE::ITEM_GROWTH);
				pTileInfo->setRenderColor(RENDERING_COLOR::INTENSITY_GREEN);
			}
			else
			{
				m_pStage->ChangeTileInfo(itemPos, TILE_TYPE::ITEM_SHOOT);
				pTileInfo->setRenderColor(RENDERING_COLOR::INTENSITY_TEAL);
			}

			g_pSoundMgr->PlayOnSound("appear_item.wav");
		}
		else
		{
			m_pStage->ChangeTileInfo(itemPos, TILE_TYPE::EMPTY);
		}
	}

	void StageMgr::ReleaseStage()
	{
		cmn::SafeArrayDelete(&m_pStageInfo);
	}

	INT32 StageMgr::CalcLimitTime()
	{
		INT32 elapseLimitTime =
			static_cast<INT32>(g_pTimeMgr->CalcTimeInterval(&m_startLimitTime, &m_currentLimitTime));
		return (m_pStage->getStageInfo().limitTime - elapseLimitTime);
	}

	bool StageMgr::CheckLimitTimeOver()
	{
		if (CalcLimitTime() < 0)
		{
			return true;
		}

		return false;
	}

} // namespace manager end