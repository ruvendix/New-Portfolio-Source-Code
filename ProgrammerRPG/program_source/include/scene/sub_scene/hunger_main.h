/*
 * <���� ��¥>
 * 2017-11-12
 *
 * <���� ����>
 * ������� �޷��� ���� ���Դϴ�.
 * �÷��̾�� ���� �ڵ��¿� ���� ������ ������ �� �ֽ��ϴ�.
 * �ڵ����� ���ٸ� ���� �� �ִ� ���ĵ� ���� �����ϴ�.
 */

#ifndef PROGRAMMER_RPG__HUNGER_MAIN_H_
#define PROGRAMMER_RPG__HUNGER_MAIN_H_

#include "common.h"
#include "scene/ingame.h"

namespace scene
{

	class HungerMain : public Ingame
	{
	public:
		HungerMain();
		~HungerMain();

		virtual SCENE_STATE Initialize();
		virtual SCENE_STATE Update();
		virtual SCENE_STATE Render();
		virtual SCENE_STATE Release();

		SUB_SCENE_TYPE _EatConvenience();
		SUB_SCENE_TYPE _EatFamous();
		SUB_SCENE_TYPE _EastRestaurant();
	};

} // namespace scene end

#endif