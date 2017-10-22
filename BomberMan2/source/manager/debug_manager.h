/*
 * <�ۼ� ��¥>
 * 2017-10-12
 *
 * <���� ����>
 * ������� �����ִ� �Ŵ����Դϴ�.
 * ����� ��忡���� ��ȿ�� �Լ��� ���ǵǾ��ֽ��ϴ�.
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
		// ����� ���� �Լ�

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