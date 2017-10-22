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
		void    CalculateFrameTimeInterval(); // ���ڰ� �����ؼ� ���� �ۼ�
		
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

		// �ð� ���������� ������ ������ �ð��� �����մϴ�.
		// ������ �ð��� 30�����Ӱ� 60���������� ���е˴ϴ�.
		// 30�������� 1�ʿ� 30��, 60�������� 1�ʿ� 60���Դϴ�.
		TimePoint m_startFrameTime;
		TimePoint m_endFrameTime;
		
		FLOAT32   m_frameTime;
	};

} // namespace manager end
namespace mgr = manager;

#endif