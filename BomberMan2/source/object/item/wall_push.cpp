/*
 * <작성 날짜>
 * 2017-10-15
 *
 * <파일 설명>
 * 얇은 벽을 미는 능력이 있는 아이템입니다.
 */

#include "wall_push.h"

namespace object
{

	namespace item
	{

		INT32 ItemWallPush::Initialize()
		{
			m_wallPushDirection = OBJECT_DIRECTION::END;
			return 0;
		}

		INT32 ItemWallPush::Update()
		{
			return 0;
		}

		INT32 ItemWallPush::Render()
		{
			return 0;
		}

		INT32 ItemWallPush::Release()
		{
			return 0;
		}

	} // namespace item end

} // namespace object end
