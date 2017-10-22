/*
 * <�ۼ� ��¥>
 * 2017-10-17
 *
 * <���� ����>
 * ����Ʈ�� ����� �Ǵ� ������Ʈ�Դϴ�.
 */

#include "effect_base.h"

#include "../../manager/time_manager.h"

namespace object
{

	namespace effect
	{

		INT32 EffectBase::Initialize()
		{
			m_shape = ' ';

			mgr::TimeManager::ActivateManager().MeasureTimePoint(&m_createTime);
			m_destroyTime = m_createTime;
			return 0;
		}

		INT32 EffectBase::Update()
		{
			return 0;
		}

		INT32 EffectBase::Render()
		{
			return 0;
		}

		INT32 EffectBase::Release()
		{
			return 0;
		}

	} // namespace effect end
	namespace eft = effect;

} // namespace object end
namespace obj = object;