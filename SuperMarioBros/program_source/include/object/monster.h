/*
 * <제작 날짜>
 * 2017-11-03
 *
 * <파일 설명>
 * 몬스터의 구현입니다.
 * 현재는 몬스터가 이동만 합니다.
 */

#ifndef SIDESCROLLING__MONSTER_H_
#define SIDESCROLLING__MONSTER_H_

#include "object/object_base.h"

namespace object
{
	class ObjectBaseInfo;
}

namespace object
{
	
	class Monster : public ObjectBase
	{
	public:
		Monster();
		virtual ~Monster();

		virtual OBJECT_STATE Initialize();
		virtual OBJECT_STATE Update();
		virtual OBJECT_STATE Render();
		virtual OBJECT_STATE Release();

		void    _MovePos();
		void    _DescendPos();

		bool    _CheckExceptionTile(const Position2D& pos);
		bool    _CheckPlayerCollsion();

		// getter
		ObjectBaseInfo* getMonsterInfo() const
		{
			return m_pMonsterInfo.get();
		}

		bool getFallDown() const noexcept
		{
			return m_bFallDown;
		}

	private:
		std::shared_ptr<ObjectBaseInfo>    m_pMonsterInfo;
		bool                               m_bFallDown;
	};

} // namespace object end

#endif