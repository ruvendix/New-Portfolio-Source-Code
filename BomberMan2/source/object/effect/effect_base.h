/*
 * <작성 날짜>
 * 2017-10-17
 *
 * <파일 설명>
 * 이펙트의 기반이 되는 오브젝트입니다.
 */

#ifndef EASIEST_EFFECT_BASE_H_
#define EASIEST_EFFECT_BASE_H_

#include "../object_base.h"

const INT32 EFFECT_DESTROY = -1;

namespace object
{

	namespace effect
	{

		class EffectBase : public ObjectBase
		{
		public:
			virtual ~EffectBase() = default;

			virtual INT32 Initialize() override;
			virtual INT32 Update()     override;
			virtual INT32 Render()     override;
			virtual INT32 Release()    override;

			const STRING& getShape() const noexcept
			{
				return m_shape;
			}

			void setShape(const STRING& shape)
			{
				m_shape = shape;
			}

		protected:
			TimePoint m_createTime;
			TimePoint m_destroyTime;

		private:
			STRING m_shape;
		};

	} // namespace effect end
	namespace eft = effect;

} // namespace object end
namespace obj = object;

#endif