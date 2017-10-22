/*
 * <작성 날짜>
 * 2017-10-13
 *
 * <파일 설명>
 * 오브젝트의 충돌을 관리합니다.
 * 충돌 검사는 컬리전 매니저를 이용해야 합니다.
 * 수학적인 부분도 포함되지만 수학과는 분리해놨습니다.
 * 수학과 관련된 부분은 cmath 헤더를 이용합니다.
 */

#include "collision_manager.h"

#include "../include/common/cmn_function.h"

namespace manager
{
	CollisionManager::CollisionManager()
	{
		m_collisonValue = 0;
		m_objectPos     = { 0, 0 };
	}

	struct CollisionManager::ManagerDeleter
	{
		void operator() (CollisionManager* pCollisionManager)
		{
			if (pCollisionManager != nullptr)
			{
				pCollisionManager->~CollisionManager();
				cmn::SafeFree(&pCollisionManager);
			}
		}
	};

	CollisionManager& CollisionManager::ActivateManager()
	{
		static std::unique_ptr<CollisionManager, ManagerDeleter> pCollisionManager = nullptr;

		if (pCollisionManager == nullptr)
		{
			std::once_flag flag;
			std::function<void()> allocator = []() { pCollisionManager.reset(new CollisionManager); };
			std::call_once(flag, allocator);
		}

		return *pCollisionManager;
	}

	BOOL CollisionManager::CheckBasePosExistOutsidePos(INT32 baseX, INT32 baseY,
		 INT32 x1, INT32 y1, INT32 x2, INT32 y2)
	{
		if ( (baseX < x1) ||
			 (baseY < y1) ||
			 (baseX > x2) ||
			 (baseY > y2) )
		{
			return true;
		}

		return false;
	}

	BOOL CollisionManager::CheckBasePosNotExistOutsidePos(INT32 baseX, INT32 baseY,
		 INT32 x1, INT32 y1, INT32 x2, INT32 y2)
	{
		if ( (baseX < x1) ||
			 (baseY < y1) ||
			 (baseX > x2) ||
			 (baseY > y2) )
		{
			return false;
		}

		return true;
	}

	BOOL CollisionManager::CheckBasePosExistInsidePos(INT32 baseX, INT32 baseY,
		 INT32 x1, INT32 y1, INT32 x2, INT32 y2)
	{
		if ( (baseX >= x1) &&
			 (baseY >= y1) &&
			 (baseX <= x2) &&
			 (baseY <= y2) )
		{
			return true;
		}

		return false;
	}

	BOOL CollisionManager::CheckBasePosNotExistInsidePos(INT32 baseX, INT32 baseY,
		 INT32 x1, INT32 y1, INT32 x2, INT32 y2)
	{
		if ( (baseX >= x1) &&
			 (baseY >= y1) &&
			 (baseX <= x2) &&
			 (baseY <= y2) )
		{
			return false;
		}

		return true;
	}

	BOOL CollisionManager::CheckCollisionForCollisionValue(INT32 collisionValue, INT32 value)
	{
		if (collisionValue == value)
		{
			return true;
		}

		return false;
	}

} // namespace manager end