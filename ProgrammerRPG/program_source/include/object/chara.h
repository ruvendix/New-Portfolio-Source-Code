/*
 * <제작 날짜>
 * 2017-11-12
 *
 * <파일 설명>
 * 캐릭터의 기본 구현입니다.
 * 모든 캐릭터는 Chara 클래스를 기반으로 구현됩니다.
 */

#ifndef PROGRAMMER_RPG__CHARACTER_H_
#define PROGRAMMER_RPG__CHARACTER_H_

#include "common.h"
#include "object/object_base.h"

namespace object
{

	class Chara : public obj::ObjectBase
	{
	public:
		Chara();
		virtual ~Chara();

		virtual OBJECT_STATE Initialize();
		virtual OBJECT_STATE Update();
		virtual OBJECT_STATE Render();
		virtual OBJECT_STATE Release();
	};

} // namespace object end

#endif