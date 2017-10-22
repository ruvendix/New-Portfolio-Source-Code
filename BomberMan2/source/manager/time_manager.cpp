/*
 * <�ۼ� ��¥>
 * 2017-10-14
 *
 * <���� ����>
 * �ð��� �������ִ� �Ŵ����Դϴ�.
 * ������ �ð��� �̿��ϸ� �ð� ������ ���� �� �ֽ��ϴ�.
 * ���ӿ����� �ð� ������ �� ������� �̿��ϴµ� �ϳ��� �Ϲ����� �ð� ������ �̿��ϴ� ���̰�
 * �ٸ� �ϳ��� "��Ÿ Ÿ��"�̶� �θ��� ª�� �ð� ������ ���� ���� �̰��� �������Ѽ� �̿��մϴ�.
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

	// ������ �ð��� ��Ÿ Ÿ���� �̿��մϴ�.
	void TimeManager::CalculateFrameTimeInterval()
	{
		std::chrono::duration<FLOAT32> timeInterval = m_endFrameTime - m_startFrameTime;
		m_frameTime += timeInterval.count();
	}

	// �Ϲ� �ð��� �ð� ���ݸ� ���ؼ� �̿��մϴ�.
	FLOAT32 TimeManager::CalculateTimeInterval(const TimePoint& startTime, const TimePoint& endTime) const
	{
		std::chrono::duration<FLOAT32> timeInterval = endTime - startTime;
		return timeInterval.count();
	}

} // namespace manager end