/*
 * <�ۼ� ��¥>
 * 2017-10-12
 *
 * <���� ����>
 * ������� �����ִ� �Ŵ����Դϴ�.
 * ����� ��忡���� ��ȿ�� �Լ��� ���ǵǾ��ֽ��ϴ�.
 */

#include "debug_manager.h"

#include "../include/common/cmn_function.h"

namespace manager
{

	struct DebugManager::ManagerDeleter
	{
		void operator() (DebugManager* pDebugManager)
		{
			if (pDebugManager != nullptr)
			{
				pDebugManager->~DebugManager();
				cmn::SafeFree(&pDebugManager);
			}
		}
	};

	DebugManager& DebugManager::ActivateManager()
	{
		static std::unique_ptr<DebugManager, ManagerDeleter> pDebugManager = nullptr;
		
		if (pDebugManager == nullptr)
		{
			std::once_flag flag;
			std::function<void()> allocator = []() { pDebugManager.reset(new DebugManager); };
			std::call_once(flag, allocator);
		}

		return *pDebugManager;
	}

} // namespace manager end