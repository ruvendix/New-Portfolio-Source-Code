/*
 * <작성 날짜>
 * 2017-10-14
 *
 * <파일 설명>
 * 폭탄 오브젝트를 구현합니다.
 * 플레이어가 폭탄을 사용하면 그 자리에서 설치됩니다.
 * 폭탄은 일정 시간이 지난 후에 폭발합니다.
 * 이때 폭발 범위가 다른 폭탄에 영향을 끼치면 그 폭탄도 같이 폭발합니다.
 * 폭탄이 폭발하면 폭발 이펙트가 생성되고 마찬가지로 일정 시간이 지난 뒤에 사라집니다.
 */

#ifndef EASIEST_OBJECT_BOMB_H_
#define EASIEST_OBJECT_BOMB_H_

#include "object_base.h"

static const INT32 BOMB_DIRECTION_MAX = 4;

namespace object
{

	class Bomb : public ObjectBase
	{
	public:
		Bomb() = default;
		virtual ~Bomb() = default;

		virtual INT32 Initialize() override;
		virtual INT32 Update()     override;
		virtual INT32 Render()     override;
		virtual INT32 Release()    override;

		BOMB_STATE _Explode();

		void _AppearItem(const Position2D& explosionPos) const;

		BOOL _CheckExplosionItem() const;
		BOOL _CheckExplosionChain(const Position2D& explosionPos, OBJECT_DIRECTION explosionDirection) const;

		void setExplosionChain(BOOL explosionChain)
		{
			m_bChainExplosion = explosionChain;
		}

		void setExplosionChainDirection(const OBJECT_DIRECTION& explosionDirection, BOOL bValue)
		{
			m_bChainExplosionDirection[static_cast<INT32>(explosionDirection)] = bValue;
		}

	private:
		TimePoint m_bombDropTime;  // 폭탄을 설치한 시간
		TimePoint m_explosionTime; // 폭탄이 폭발하는 시간

		BOOL m_bChainExplosion;    // 연쇄 폭발 상태
		BOOL m_bChainExplosionDirection[BOMB_DIRECTION_MAX];

		ARRAY<Position2D, BOMB_DIRECTION_MAX> m_bombDirectionTable;
	};

} // namespace object end
namespace obj = object;

#endif