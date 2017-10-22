/*
 * <작성 날짜>
 * 2017-10-17
 *
 * <파일 설명>
 * 이펙트 정보를 관리합니다.
 * 이펙트는 EffectBase를 기반으로 하며 이펙트 매니저에 등록됩니다.
 * 이펙트가 많아진다면 팩토리 메서드 패턴으로 개선할 예정입니다.
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