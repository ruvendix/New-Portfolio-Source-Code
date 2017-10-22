/*
 * <작성 날짜>
 * 2017-10-14
 *
 * <파일 설명>
 * 시간을 측정해주는 매니저입니다.
 * 측정된 시간을 이용하면 시간 간격을 구할 수 있습니다.
 * 게임에서는 시간 간격을 두 방식으로 이용하는데 하나는 일반적인 시간 간격을 이용하는 것이고
 * 다른 하나는 "델타 타임"이라 부르는 짧은 시간 간격을 구한 다음 이것을 누적시켜서 이용합니다.
 */

#include "time_manager.h"

#include "../include/common/cmn_function.h"

namespace manager
{

	struct TimeManager::ManagerDeleter
	{
		void operator() (TimeManager* pTimeManager)
		{
			if (pTimeManager != nullptr)
			{
				pTimeManager->~TimeManager();
				cmn::SafeFree(&pTimeManager);
			}
		}
	};

	TimeManager& TimeManager::ActivateManager()
	{
		static std::unique_ptr<TimeManager, ManagerDeleter> pTimeManager = nullptr;

		if (pTimeManager == nullptr)
		{
			std::once_flag flag;
			std::function<void()> allocator = []() { pTimeManager.reset(new TimeManager); };
			std::call_once(flag, allocator);
		}

		return *pTimeManager;
	}

	void TimeManager::InitializeFrameTime()
	{
		m_frameTime = 0.0f;
		m_startFrameTime = std::chrono::steady_clock::now();
		m_endFrameTime = m_startFrameTime;
	}

	void TimeManager::MeasureTimePoint(TimePoint* pTimePoint)
	{
		*pTimePoint = std::chrono::steady_clock::now();
	}

	// 프레임 시간은 델타 타임을 이용합니다.
	void TimeManager::CalculateFrameTimeInterval()
	{
		std::chrono::duration<FLOAT32> timeInterval = m_endFrameTime - m_startFrameTime;
		m_frameTime += timeInterval.count();
	}

	// 일반 시간은 시간 간격만 구해서 이용합니다.
	FLOAT32 TimeManager::CalculateTimeInterval(const TimePoint& startTime, const TimePoint& endTime) const
	{
		std::chrono::duration<FLOAT32> timeInterval = endTime - startTime;
		return timeInterval.count();
	}

} // namespace manager end