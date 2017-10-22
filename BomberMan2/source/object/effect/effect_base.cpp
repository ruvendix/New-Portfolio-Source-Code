/*
 * <작성 날짜>
 * 2017-10-17
 *
 * <파일 설명>
 * 이펙트의 기반이 되는 오브젝트입니다.
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