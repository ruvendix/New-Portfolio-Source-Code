/*
 * <제작 날짜>
 * 2017-11-01
 *
 * <파일 설명>
 * 총알의 구현입니다.
 * 총알은 플레이어와 별개로 처리합니다.
 */

#ifndef SIDESCROLLING__BULLET_H_
#define SIDESCROLLING__BULLET_H_

#include "object/object_base.h"

namespace object
{
	class ObjectBaseInfo;
}

namespace object
{

	class Bullet : public ObjectBase
	{
	public:
		Bullet();
		virtual ~Bullet();

		virtual OBJECT_STATE Initialize();
		virtual OBJECT_STATE Update();
		virtual OBJECT_STATE Render();
		virtual OBJECT_STATE Release();

		// getter
		ObjectBaseInfo* getBulletInfo() const
		{
			return m_pBulletInfo.get();
		}

	private:
		std::shared_ptr<obj::ObjectBaseInfo>    m_pBulletInfo;
		INT32                                   m_distance;
	};

} // namespace object end

#endif