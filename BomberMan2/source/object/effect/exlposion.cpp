/*
 * <작성 날짜>
 * 2017-10-17
 *
 * <파일 설명>
 * 폭발 이펙트 오브젝트를 구현합니다.
 */

#include "exlposion.h"

#include "../../manager/time_manager.h"

const FLOAT32 EXPLOSION_VANISH_TIME = 0.5f;

namespace object
{

	namespace effect
	{

		INT32 EffectExplosion::Initialize()
		{
			// 가상 함수 관계에서는 실제로 동적 바인딩된
			// 객체의 함수만 호출하므로 이렇게 부모의
			// 함수를 호출하는 기법을 사용하기도 합니다.
			// 비가상 함수일 때도 이런 기법을 사용합니다.
			EffectBase::Initialize();

			return 0;
		}

		INT32 EffectExplosion::Update()
		{
			mgr::TimeManager::ActivateManager().MeasureTimePoint(&m_destroyTime);

			if (mgr::TimeManager::ActivateManager().CalculateTimeInterval(m_createTime, m_destroyTime) > EXPLOSION_VANISH_TIME)
			{
				return EFFECT_DESTROY;
			}

			return 0;
		}

		INT32 EffectExplosion::Render()
		{
			return 0;
		}

		INT32 EffectExplosion::Release()
		{
			return 0;
		}

	} // namespace effect end
	namespace eft = effect;

} // namespace object end
namespace obj = object;