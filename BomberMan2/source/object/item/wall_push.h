/*
 * <작성 날짜>
 * 2017-10-15
 *
 * <파일 설명>
 * 얇은 벽을 미는 능력이 있는 아이템입니다.
 */

#ifndef EASIEST_ITEM_WALLPUSH_H_
#define EASIEST_ITEM_WALLPUSH_H_

#include "item_base.h"

namespace object
{

	namespace item
	{

		class ItemWallPush : public ItemBase
		{
		public:
			virtual ~ItemWallPush() = default;

			virtual INT32 Initialize() override;
			virtual INT32 Update()     override;
			virtual INT32 Render()     override;
			virtual INT32 Release()    override;

			void setWallPushDirection(const OBJECT_DIRECTION& wallPushDirection)
			{
				m_wallPushDirection = wallPushDirection;
			}

		private:
			OBJECT_DIRECTION m_wallPushDirection;
		};

	} // namespace item end

} // namespace object end

#endif