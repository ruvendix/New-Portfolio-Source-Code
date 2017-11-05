/*
 * <제작 날짜>
 * 2017-10-25
 *
 * <파일 설명>
 * 스테이지의 공용 정보 및 목록을 관리합니다.
 */

#ifndef SIDESCROLLING__STAGE_MANAGER_H_
#define SIDESCROLLING__STAGE_MANAGER_H_

#include "common.h"
#include "global_data.h"

namespace object
{
	class Stage;
	class TileInfo;
}

namespace manager
{

	class StageMgr
	{
		DEFINE_SINGLETON_CLASS(StageMgr);
	public:
		void Initialize();
		void LoadStageList();
		void ResetStage();
		void CreateItem(obj::TileInfo* pTileInfo, bool bGrowth = false);
		void ReleaseStage();
		
		INT32 CalcLimitTime();

		bool  CheckLimitTimeOver();

		void  AddStageNum()
		{
			++m_nowStage;
		}

		// getter
		INT32 getStageCount() const noexcept
		{
			return m_stageCount;
		}

		INT32 getNowStage() const noexcept
		{
			return m_nowStage;
		}

		StageInfo* getStageInfo(INT32 stageIndex) const
		{
			return &m_pStageInfo[stageIndex - 1];
		}

		obj::Stage* getStage() const noexcept
		{
			return m_pStage;
		}

		TimePoint* getStartLimitTime() noexcept
		{
			return &m_startLimitTime;
		}

		TimePoint* getCurrentLimitTime() noexcept
		{
			return &m_currentLimitTime;
		}

		// setter
		void setNowStage(INT32 nowStage)
		{
			m_nowStage = nowStage;
		}

		void setStage(const obj::Stage* pStage)
		{
			m_pStage = const_cast<obj::Stage*>(pStage);
		}

	private:
		StageInfo*     m_pStageInfo;
		obj::Stage*    m_pStage;

		INT32          m_stageCount;
		INT32          m_nowStage;

		TimePoint      m_startLimitTime;
		TimePoint      m_currentLimitTime;
	};

} // namespace manager end

#endif