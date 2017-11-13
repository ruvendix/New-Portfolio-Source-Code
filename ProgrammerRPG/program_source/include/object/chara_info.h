/*
 * <제작 날짜>
 * 2017-11-12
 *
 * <파일 설명>
 * 캐릭터의 기본 정보입니다.
 * 모든 캐릭터 정보는 CharaInfo 클래스를 기반으로 구현됩니다.
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