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

#ifndef EASIEST_COLLISION_MANAGER_H_
#define EASIEST_COLLISION_MANAGER_H_

#include "../include/common/cmn_type.h"
#include "../include/global_data.h"

namespace manager
{

	class CollisionManager
	{
	public:
		static CollisionManager& ActivateManager();

		// �������� �ܺο� �����ϴ��� Ȯ���մϴ�.
		BOOL CheckBasePosExistOutsidePos(INT32 baseX, INT32 baseY,
			 INT32 x1, INT32 y1, INT32 x2, INT32 y2);
		
		// �������� �ܺο� �������� �ʴ��� Ȯ���մϴ�.
		BOOL CheckBasePosNotExistOutsidePos(INT32 baseX, INT32 baseY,
			 INT32 x1, INT32 y1, INT32 x2, INT32 y2);
			
		// �������� ���ο� �����ϴ��� Ȯ���մϴ�.
		BOOL CheckBasePosExistInsidePos(INT32 baseX, INT32 baseY,
			 INT32 x1, INT32 y1, INT32 x2, INT32 y2);
		
		// �������� ���ο� �������� �ʴ��� Ȯ���մϴ�.
		BOOL CheckBasePosNotExistInsidePos(INT32 baseX, INT32 baseY,
			 INT32 x1, INT32 y1, INT32 x2, INT32 y2);
			
		// �ø��� �Ŵ����� ��ϵ� ���� ���ؼ� �浹�� �����մϴ�.
		BOOL CheckCollisionForCollisionValue(INT32 collisionValue, INT32 value);

		// �ø��� �Ŵ����� �ø������� ����մϴ�.
		void EnrollCollisionValue(INT32* pCollisionValue, INT32 value)
		{
			*pCollisionValue = value;
		}

#ifndef UNUSED_FUNC
		void setObjectPos(const Position2D& objectPos)
		{
			m_objectPos = objectPos;
		}
#endif

#ifndef UNUSED_FUNC
		Position2D& getObjectPos() noexcept
		{
			return m_objectPos;
		}
#endif

#ifndef UNUSED_FUNC
		const Position2D& getObjectPos() const noexcept
		{
			return m_objectPos;
		}
#endif

	private:
		CollisionManager();
		~CollisionManager() = default;

		CollisionManager(const CollisionManager& rhs)  = delete;
		CollisionManager(const CollisionManager&& rhs) = delete;

		CollisionManager& operator= (const CollisionManager& rhs)  = delete;
		CollisionManager& operator= (const CollisionManager&& rhs) = delete;

		struct ManagerDeleter;

		INT32 m_collisonValue;
		
		Position2D m_objectPos;
	};

} // namespace manager end
namespace mgr = manager;

#endif