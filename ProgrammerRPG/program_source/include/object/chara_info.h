/*
 * <���� ��¥>
 * 2017-11-12
 *
 * <���� ����>
 * ĳ������ �⺻ �����Դϴ�.
 * ��� ĳ���� ������ CharaInfo Ŭ������ ������� �����˴ϴ�.
 */

#ifndef PROGRAMMER_RPG__CHARACTER_INFORMATION_H_
#define PROGRAMMER_RPG__CHARACTER_INFORMATION_H_

#include "common.h"
#include "object/object_base_info.h"

namespace object
{

	class CharaInfo : public obj::ObjectBaseInfo
	{
	public:
		CharaInfo();
		virtual ~CharaInfo();

	protected:
		STRING    m_strName;
		INT32     m_id;
	};

} // namespace object end

#endif