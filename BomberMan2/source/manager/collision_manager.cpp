/*
 * <�ۼ� ��¥>
 * 2017-10-13
 *
 * <���� ����>
 * ������Ʈ�� �浹�� �����մϴ�.
 * �浹 �˻�� �ø��� �Ŵ����� �̿��ؾ� �մϴ�.
 * �������� �κе� ���Ե����� ���а��� �и��س����ϴ�.
 * ���а� ���õ� �κ��� cmath ����� �̿��մϴ�.
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