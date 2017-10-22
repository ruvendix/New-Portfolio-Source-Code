/*
 * <작성 날짜>
 * 2017-10-15
 *
 * <파일 설명>
 * 폭탄의 파워를 증가시켜주는 아이템입니다.
 */

#ifndef EASIEST_ITEM_POWER_H_
#define EASIEST_ITEM_POWER_H_

#include "item_base.h"

namespace object
{

	namespace item
	{

		class ItemPower : public ItemBase
		{
		public:
			virtual ~ItemPower() = default;

			virtual INT32 Initialize() override;
			virtual INT32 Update()     override;
			virtual INT32 Render()     override;
			virtual INT32 Release()    override;
		};

	} // namespace item end

} // namespace object end
namespace obj = object;

#endif