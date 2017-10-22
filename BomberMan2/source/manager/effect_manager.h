/*
 * <�ۼ� ��¥>
 * 2017-10-17
 *
 * <���� ����>
 * ����Ʈ ������ �����մϴ�.
 * ����Ʈ�� EffectBase�� ������� �ϸ� ����Ʈ �Ŵ����� ��ϵ˴ϴ�.
 * ����Ʈ�� �������ٸ� ���丮 �޼��� �������� ������ �����Դϴ�.
 */

#ifndef EASIEST_EFFECT_MANAGER_H_
#define EASIEST_EFFECT_MANAGER_H_

#include "../include/common/cmn_header.h"

#include "../object/effect/effect_base.h"

typedef obj::eft::EffectBase EffectBase;

namespace manager
{

	class EffectManager
	{
	public:
		static EffectManager& AcitvateInstance();

		void CreateEffect(const Position2D& pos, const STRING& shape, EFFECT_TYPE effecType);
		void UpdateEffect();
		void RenderEffect();

		void _ClearEffectList();

		const std::list<EffectBase*>& getEffectList() const noexcept
		{
			return m_listEffect;
		}

	private:
		EffectManager()  = default;
		~EffectManager() = default;

		EffectManager(const EffectManager& rhs)  = delete;
		EffectManager(const EffectManager&& rhs) = delete;

		EffectManager& operator() (const EffectManager& rhs)  = delete;
		EffectManager& operator() (const EffectManager&& rhs) = delete;

		struct ManagerDeleter;

		std::list<EffectBase*> m_listEffect;
	};

} // namespace manager end
namespace mgr = manager;

#endif