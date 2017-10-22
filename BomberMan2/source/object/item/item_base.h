/*
 * <작성 날짜>
 * 2017-10-15
 *
 * <파일 설명>
 * 아이템의 기반이 되는 오브젝트입니다.
 */

#ifndef EASIEST_ITEM_BASE_H_
#define EASIEST_ITEM_BASE_H_

#include "../object_base.h"

namespace object
{

	namespace item
	{
		
		class ItemBase : public ObjectBase
		{
		public:
			virtual ~ItemBase() = default;

			virtual INT32 Initialize() override;
			virtual INT32 Update()     override;
			virtual INT32 Render()     override;
			virtual INT32 Release()    override;

		private:

		};

	} // namespace item end

} // namespace object end
namespace obj = object;

#endif