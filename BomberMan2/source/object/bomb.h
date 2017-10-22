/*
 * <�ۼ� ��¥>
 * 2017-10-14
 *
 * <���� ����>
 * ��ź ������Ʈ�� �����մϴ�.
 * �÷��̾ ��ź�� ����ϸ� �� �ڸ����� ��ġ�˴ϴ�.
 * ��ź�� ���� �ð��� ���� �Ŀ� �����մϴ�.
 * �̶� ���� ������ �ٸ� ��ź�� ������ ��ġ�� �� ��ź�� ���� �����մϴ�.
 * ��ź�� �����ϸ� ���� ����Ʈ�� �����ǰ� ���������� ���� �ð��� ���� �ڿ� ������ϴ�.
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
		TimePoint m_bombDropTime;  // ��ź�� ��ġ�� �ð�
		TimePoint m_explosionTime; // ��ź�� �����ϴ� �ð�

		BOOL m_bChainExplosion;    // ���� ���� ����
		BOOL m_bChainExplosionDirection[BOMB_DIRECTION_MAX];

		ARRAY<Position2D, BOMB_DIRECTION_MAX> m_bombDirectionTable;
	};

} // namespace object end
namespace obj = object;

#endif