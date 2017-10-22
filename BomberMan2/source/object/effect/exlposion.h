/*
 * <작성 날짜>
 * 2017-10-17
 *
 * <파일 설명>
 * 폭발 이펙트 오브젝트를 구현합니다.
 */

#ifndef EASIEST_EFFECT_EXPLOSION_H_
#define EASIEST_EFFECT_EXPLOSION_H_

#include "effect_base.h"

namespace object
{

	namespace effect
	{

		class EffectExplosion : public EffectBase
		{
		public:
			virtual ~EffectExplosion() = default;

			virtual INT32 Initialize() override;
			virtual INT32 Update()     override;
			virtual INT32 Render()     override;
			virtual INT32 Release()    override;
		};

	} // namespace effect end
	namespace eft = effect;

} // namespace object end
namespace obj = object;

#endif