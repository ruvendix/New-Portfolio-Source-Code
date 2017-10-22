/*
 * <�ۼ� ��¥>
 * 2017-10-12
 *
 * <���� ����>
 * �÷��̾ �����մϴ�.
 * �÷��̾�� ����ڰ� ���� ������ �� �ִ� ������Ʈ�Դϴ�.
 */

#ifndef EASIEST_OBJECT_PLAYER_H_
#define EASIEST_OBJECT_PLAYER_H_

#include "../object/object_base.h"

#include "item/item_base.h"

#include "bomb.h"

static const INT32 PLAYER_MOVE_KEY_MAX   = 4;
static const INT32 PLAYER_BOMB_MAX_COUNT = 5;
static const INT32 PLAYER_ITEM_MAX_COUNT = 3;

namespace object
{

	class Player : public ObjectBase
	{
	public:
		virtual ~Player() = default;

		virtual INT32 Initialize() override;
		virtual INT32 Update()     override;
		virtual INT32 Render()     override;
		virtual INT32 Release()    override;

		void  EnrollChainBomb(INT32 bombNum, const OBJECT_DIRECTION& explosionDirection);

		void  _CalculateMovePos(Position2D* pMovePos);
		void  _AddItemDummy(); // �ƹ��͵� ó������ �ʴ� ���� �Լ��Դϴ�.
		void  _AddItemPower();
		void  _AddItemTransparency();
		void  _AddItemWallPush();
		void  _ApplyItemAbility();

		INT32 _MovePlayer(Position2D* pMovePos);
		INT32 _DropBomb();
		INT32 _AddItem();
		INT32 _ExplosionBomb();

		BOOL  _CheckCollisionMapObject();
		BOOL  _PushWall();

		BOOL  getIsDropBomb() const noexcept
		{
			return m_bIsDropBomb;
		}

		BOOL  getIsTransparency() const noexcept
		{
			return m_bIsTransparency;
		}

		BOOL  getTransparencyMode() const noexcept
		{
			return m_bTransparencyMode;
		}

		BOOL  getIsWallPush() const noexcept
		{
			return m_bIsWallPush;
		}

		BOOL  getIsWallPushMode() const noexcept
		{
			return m_bIsWallPushMode;
		}

		INT32 getBombPower() const noexcept
		{
			return m_bombPower;
		}

		INT32 getBombDropCount() const noexcept
		{
			return m_bombDropCount;
		}

		const LIST<Bomb*>& getListBomb() const noexcept
		{
			return m_listBomb;
		}

	private:
		INT32 m_bombPower;
		INT32 m_bombDropCount; // ���� ��ġ�� ��ź�� ����

		BOOL  m_bIsDropBomb;
		BOOL  m_bIsTransparency;
		BOOL  m_bTransparencyMode;
		BOOL  m_bIsWallPush;
		BOOL  m_bIsWallPushMode;
		BOOL  m_bIsWallCollision;

		LIST<Bomb*> m_listBomb;

		ARRAY<item::ItemBase*, PLAYER_ITEM_MAX_COUNT> m_arrItem;
	};

} // namespace object end
namespace obj = object;

#endif