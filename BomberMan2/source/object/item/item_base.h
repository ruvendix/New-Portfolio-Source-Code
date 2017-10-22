/*
 * <�ۼ� ��¥>
 * 2017-10-15
 *
 * <���� ����>
 * �������� ����� �Ǵ� ������Ʈ�Դϴ�.
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