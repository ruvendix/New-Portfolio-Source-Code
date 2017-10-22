/*
 * <�ۼ� ��¥>
 * 2017-10-17
 *
 * <���� ����>
 * ����Ʈ ������ �����մϴ�.
 * ����Ʈ�� EffectBase�� ������� �ϸ� ����Ʈ �Ŵ����� ��ϵ˴ϴ�.
 * ����Ʈ�� �������ٸ� ���丮 �޼��� �������� ������ �����Դϴ�.
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

		// ������ ���丮 �޼��� �������� �����Ϸ��� �ߴµ�
		// ������ ����Ʈ�� �ϳ��ۿ� ��� �̷��� �����߽��ϴ�.
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

					// �ݺ��� ��ȿȭ ������ �����մϴ�.
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
		// �̷��� ���� �뵵�θ� ���ȴٸ�
		// range based for���� ����ص� �˴ϴ�.
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
		// range based for���� ������ ���� ����ؾ� �մϴ�!
		// ��, �ݺ��ڴ� ���� �����ϴ� �뵵�ϻ�...
		// ������ �Ʒ��� ������ �ݺ��ڿ� nullptr�� �־
		// STL���� ������� �ʽ��ϴ�. i�� nullptr�� ���Ե��� �ʾƿ�...
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