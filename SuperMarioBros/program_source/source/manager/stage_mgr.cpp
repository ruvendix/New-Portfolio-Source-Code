/*
 * <제작 날짜>
 * 2017-10-25
 *
 * <파일 설명>
 * 스테이지의 공용 정보 및 목록을 관리합니다.
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

		// 스테이지 개수만큼 동적할당합니다.
		m_pStageInfo = new StageInfo[m_stageCount];
		cmn::InitializeArrayMemory(m_pStageInfo, m_stageCount);
		
		// 텍스트 파일에 있는 정보는 문자열이므로 문자열 버퍼를 할당해서
		// 읽어와야 합니다. 변환이 필요한 경우는 변환 과정도 거칩니다.
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

		if (itemAppear <= 70) // 아이템 등장 확률
		{
			itemAppear = g_pRandomMgr->GenerateInt(0, 100);

			if (itemAppear <= 70) // 거대화 아이템 등장 확률
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