/*
 * <�ۼ� ��¥>
 * 2017-10-17
 *
 * <���� ����>
 * ���� ����Ʈ ������Ʈ�� �����մϴ�.
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
			// ���� �Լ� ���迡���� ������ ���� ���ε���
			// ��ü�� �Լ��� ȣ���ϹǷ� �̷��� �θ���
			// �Լ��� ȣ���ϴ� ����� ����ϱ⵵ �մϴ�.
			// �񰡻� �Լ��� ���� �̷� ����� ����մϴ�.
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