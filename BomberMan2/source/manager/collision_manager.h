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

		// 기준점이 외부에 존재하는지 확인합니다.
		BOOL CheckBasePosExistOutsidePos(INT32 baseX, INT32 baseY,
			 INT32 x1, INT32 y1, INT32 x2, INT32 y2);
		
		// 기준점이 외부에 존재하지 않는지 확인합니다.
		BOOL CheckBasePosNotExistOutsidePos(INT32 baseX, INT32 baseY,
			 INT32 x1, INT32 y1, INT32 x2, INT32 y2);
			
		// 기준점이 내부에 존재하는지 확인합니다.
		BOOL CheckBasePosExistInsidePos(INT32 baseX, INT32 baseY,
			 INT32 x1, INT32 y1, INT32 x2, INT32 y2);
		
		// 기준점이 내부에 존재하지 않는지 확인합니다.
		BOOL CheckBasePosNotExistInsidePos(INT32 baseX, INT32 baseY,
			 INT32 x1, INT32 y1, INT32 x2, INT32 y2);
			
		// 컬리전 매니저에 등록된 값과 비교해서 충돌을 판정합니다.
		BOOL CheckCollisionForCollisionValue(INT32 collisionValue, INT32 value);

		// 컬리전 매니저에 컬리전값을 등록합니다.
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