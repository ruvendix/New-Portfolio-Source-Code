/*
 * 작성 날짜 : 2017-10-11
 * 파일 설명 : 오브젝트의 기본 정보입니다.
 */

#include "object_base.h"

namespace object
{

	ObjectBase::ObjectBase()
	{
		setNowPos(0, 0);
		CopyPos(&m_oldPos, m_nowPos);
		m_collisionValue = 0;
	}

} // namespace object end