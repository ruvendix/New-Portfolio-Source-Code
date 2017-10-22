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

#ifndef EASIEST_TIME_MANAGER_H_
#define EASIEST_TIME_MANAGER_H_

#include "../include/common/cmn_header.h"
#include "../include/common/cmn_type.h"

namespace manager
{

	class TimeManager
	{
	public:
		static TimeManager& ActivateManager();

		void    InitializeFrameTime();
		void    MeasureTimePoint(TimePoint* pTimePoint);
		void    CalculateFrameTimeInterval(); // 인자가 복잡해서 따로 작성
		
		FLOAT32 CalculateTimeInterval(const TimePoint& startTime, const TimePoint& endTime) const;

		const FLOAT32 getFrameTime() const noexcept
		{
			return m_frameTime;
		}

		TimePoint* getStartFrameTime() noexcept
		{
			return &m_startFrameTime;
		}

		TimePoint* getEndFrameTime() noexcept
		{
			return &m_endFrameTime;
		}

	private:
		TimeManager()  = default;
		~TimeManager() = default;

		TimeManager(const TimeManager& rhs)  = delete;
		TimeManager(const TimeManager&& rhs) = delete;

		TimeManager& operator= (const TimeManager& rhs)  = delete;
		TimeManager& operator= (const TimeManager&& rhs) = delete;

		struct ManagerDeleter;

		// 시간 측정값과는 별개로 프레임 시간을 관리합니다.
		// 프레임 시간은 30프레임과 60프레임으로 구분됩니다.
		// 30프레임은 1초에 30번, 60프레임은 1초에 60번입니다.
		TimePoint m_startFrameTime;
		TimePoint m_endFrameTime;
		
		FLOAT32   m_frameTime;
	};

} // namespace manager end
namespace mgr = manager;

#endif