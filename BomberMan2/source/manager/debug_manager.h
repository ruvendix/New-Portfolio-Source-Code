/*
 * <작성 날짜>
 * 2017-10-12
 *
 * <파일 설명>
 * 디버깅을 도와주는 매니저입니다.
 * 디버그 모드에서만 유효한 함수가 정의되어있습니다.
 */

#ifndef EASIEST_DEBUG_MANAGER_H_
#define EASIEST_DEBUG_MANAGER_H_

#include "../include/common/cmn_type.h"

namespace manager
{

	class DebugManager
	{
	public:
		static DebugManager& ActivateManager();

		ASCII   m_ASCII;
		STRING  m_string;

		INT8    m_int8;
		INT16   m_int16;
		INT32   m_int32;
		INT64   m_int64;

		UINT8   m_uint8;
		UINT16  m_uint16;
		UINT32  m_uint32;
		UINT64  m_uint64;

		FLOAT32 m_float32;
		FLOAT64 m_float64;

#ifndef _NDEBUG
		// 디버깅 전용 함수

#endif

	private:
		DebugManager()  = default;
		~DebugManager() = default;

		DebugManager(const DebugManager& rhs)  = delete;
		DebugManager(const DebugManager&& rhs) = delete;

		DebugManager& operator= (const DebugManager& rhs)  = delete;
		DebugManager& operator= (const DebugManager&& rhs) = delete;

		struct ManagerDeleter;
	};

} // namespace manager end
namespace mgr = manager;

#endif