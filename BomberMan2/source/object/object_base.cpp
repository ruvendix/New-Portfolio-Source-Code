/*
 * �ۼ� ��¥ : 2017-10-11
 * ���� ���� : ������Ʈ�� �⺻ �����Դϴ�.
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