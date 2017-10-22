/*
 * <작성 날짜>
 * 2017-10-17
 *
 * <파일 설명>
 * 이펙트 정보를 관리합니다.
 * 이펙트는 EffectBase를 기반으로 하며 이펙트 매니저에 등록됩니다.
 * 이펙트가 많아진다면 팩토리 메서드 패턴으로 개선할 예정입니다.
 */

#include "effect_manager.h"

#include "../include/common/cmn_function.h"

#include "../object/effect/exlposion.h"

namespace manager
{

	struct EffectManager::ManagerDeleter
	{
		void operator() (EffectManager* pEffectManager)
		{
			if (pEffectManager != nullptr)
			{
				pEffectManager->_ClearEffectList();
				pEffectManager->~EffectManager();
				cmn::SafeFree(&pEffectManager);
			}
		}
	};

	EffectManager& EffectManager::AcitvateInstance()
	{
		static std::unique_ptr<EffectManager, ManagerDeleter> pEffectManager = nullptr;

		if (pEffectManager == nullptr)
		{
			std::once_flag flag;
			std::function<void()> allocator = []() { pEffectManager.reset(new EffectManager); };
			std::call_once(flag, allocator);
		}

		return *pEffectManager;
	}

	void EffectManager::CreateEffect(const Position2D & pos, const STRING& shape, EFFECT_TYPE effectType)
	{
		EffectBase* pEffect = nullptr;

		// 원래는 팩토리 메서드 패턴으로 구현하려고 했는데
		// 지금은 이펙트가 하나밖에 없어서 이렇게 구현했습니다.
		switch (effectType)
		{
		case EFFECT_TYPE::EXPLOSION:
			pEffect = new obj::eft::EffectExplosion;
			break;
		}

		assert(pEffect != nullptr);

		pEffect->Initialize();
		pEffect->setNowPos(pos);
		pEffect->setShape(shape);

		m_listEffect.push_back(pEffect);
	}

	void EffectManager::UpdateEffect()
	{
		for (LIST<EffectBase*>::iterator i = m_listEffect.begin(); i != m_listEffect.end();)
		{
			if (*i != nullptr)
			{
				if ((*i)->Update() == EFFECT_DESTROY)
				{
					cmn::SafeDelete(&(*i));

					// 반복자 무효화 현상을 예방합니다.
					m_listEffect.erase(i++);
				}
				else
				{
					++i;
				}
			}
		}
	}

	void EffectManager::RenderEffect()
	{
		// 이렇게 접근 용도로만 사용된다면
		// range based for문을 사용해도 됩니다.
		for (EffectBase* i : m_listEffect)
		{
			if (i != nullptr)
			{
				i->Render();
			}
		}
	}

	void EffectManager::_ClearEffectList()
	{
		// range based for문은 접근할 때만 사용해야 합니다!
		// 즉, 반복자는 값을 참고하는 용도일뿐...
		// 실제로 아래의 예제는 반복자에 nullptr을 넣어도
		// STL에는 적용되지 않습니다. i에 nullptr이 대입되지 않아요...
		/*for (EffectBase* i : m_listEffect)
		{
			assert(i != nullptr);
			delete i;
			i = nullptr;
		}*/

		for (std::list<EffectBase*>::iterator i = m_listEffect.begin(); i != m_listEffect.end(); )
		{
			assert(*i != nullptr);
			if (*i != nullptr)
			{
				cmn::SafeDelete(&(*i));
				m_listEffect.erase(i++);
			}
			else
			{
				++i;
			}
		}

		m_listEffect.clear();
	}

} // namespace manager end