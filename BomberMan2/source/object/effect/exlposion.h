/*
 * <�ۼ� ��¥>
 * 2017-10-17
 *
 * <���� ����>
 * ���� ����Ʈ ������Ʈ�� �����մϴ�.
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