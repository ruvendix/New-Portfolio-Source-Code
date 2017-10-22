/*
 * <작성 날짜>
 * 2017-10-12
 *
 * <파일 설명>
 * 디버깅을 도와주는 매니저입니다.
 * 디버그 모드에서만 유효한 함수가 정의되어있습니다.
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