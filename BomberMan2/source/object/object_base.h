/*
 * <�ۼ� ��¥>
 * 2017-10-11
 *
 * <���� ����>
 * ������Ʈ�� ������� �⺻ �����Դϴ�.
 */

#ifndef EASIEST_OBJECT_BASE_H_
#define EASIEST_OBJECT_BASE_H_

#include "../include/common/cmn_function.h"
#include "../include/common/cmn_header.h"
#include "../include/common/cmn_type.h"
#include "../include/global_data.h"

namespace object
{
	// ���� �Լ��� �ϳ��� ������ �߻� Ŭ������� �մϴ�.
	class ObjectBase abstract
	{
	public:
		ObjectBase();
		virtual ~ObjectBase() = default;

		virtual INT32 Initialize() = 0;
		virtual INT32 Update()     = 0;
		virtual INT32 Render()     = 0;
		virtual INT32 Release()    = 0;

		// ������Ʈ�� �浹���� �� ������ �����ϱ� ���� �Լ�
		// ���� ������ �Ļ� Ŭ�������� �����մϴ�.
		virtual void RenewCollisionObjectInfo()
		{

		}

		// ��� ���Ͽ� ���� ���Ǹ� �ϸ� �ζ������� ó���˴ϴ�.
		// ������ �ζ��� ���ǿ� ������ ���� �ζ������� ó���˴ϴ�.
		//
		// getter
		Position2D& getNowPos() noexcept
		{
			return m_nowPos;
		}

		const Position2D& getNowPos() const noexcept
		{
			return m_nowPos;
		}

		INT32 getNowPosX() noexcept
		{
			return m_nowPos.x;
		}

		const INT32& getNowPosX() const noexcept
		{
			return m_nowPos.x;
		}

		INT32 getNowPosY() noexcept
		{
			return m_nowPos.y;
		}

		const INT32& getNowPosY() const noexcept
		{
			return m_nowPos.y;
		}

		const INT32& getCollisionValue() const noexcept
		{
			return m_collisionValue;
		}

		// setter
		void setNowPos(const Position2D& pos)
		{
			m_nowPos = pos;
		}

		void setNowPos(INT32 x, INT32 y)
		{
			m_nowPos.x = x;
			m_nowPos.y = y;
		}

		void CopyPos(Position2D* pPos, INT32 x, INT32 y)
		{
			pPos->x = x;
			pPos->y = y;
		}

		void CopyPos(Position2D* pPos, const Position2D& newPos)
		{
			pPos->x = newPos.x;
			pPos->y = newPos.y;
		}

		void AddPos(Position2D* pPos, const Position2D& firstPos, const Position2D& secondPos)
		{
			pPos->x = firstPos.x + secondPos.x;
			pPos->y = firstPos.y + secondPos.y;
		}

		void SubtractPos(Position2D* pPos, const Position2D& firstPos, const Position2D& secondPos)
		{
			pPos->x = firstPos.x - secondPos.x;
			pPos->y = firstPos.y - secondPos.y;
		}

		void MultiplePos(Position2D* pPos, const Position2D& firstPos, const Position2D& secondPos)
		{
			pPos->x = firstPos.x * secondPos.x;
			pPos->y = firstPos.y * secondPos.y;
		}

		void MultiplePos(Position2D* pPos, const Position2D& newPos, INT32 multipleNum)
		{
			pPos->x = newPos.x * multipleNum;
			pPos->y = newPos.y * multipleNum;
		}

		void MultiplePos(Position2D* pPos, INT32 multipleNum)
		{
			pPos->x *= multipleNum;
			pPos->y *= multipleNum;
		}

		BOOL CheckSamePos(const Position2D& firstPos, const Position2D& secondPos)
		{
			if ( (firstPos.x == secondPos.x) &&
				 (firstPos.y == secondPos.y) )
			{
				return true;
			}
		
			return false;
		}

		BOOL CheckSamePos(const Position2D& firstPos, const Position2D& secondPos) const
		{
			if ((firstPos.x == secondPos.x) &&
				(firstPos.y == secondPos.y))
			{
				return true;
			}

			return false;
		}

		BOOL CheckSamePos(const Position2D& firstPos, INT32 x, INT32 y)
		{
			if ( (firstPos.x == x) &&
				 (firstPos.y == y) )
			{
				return true;
			}

			return false;
		}

	protected:
		Position2D m_nowPos;
		Position2D m_oldPos;

		INT32 m_collisionValue;
	};

} // namespace object end

namespace obj = object;

#endif