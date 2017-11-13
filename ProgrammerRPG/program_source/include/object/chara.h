/*
 * <���� ��¥>
 * 2017-11-12
 *
 * <���� ����>
 * ĳ������ �⺻ �����Դϴ�.
 * ��� ĳ���ʹ� Chara Ŭ������ ������� �����˴ϴ�.
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