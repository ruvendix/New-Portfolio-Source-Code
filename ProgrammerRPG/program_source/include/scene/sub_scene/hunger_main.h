/*
 * <제작 날짜>
 * 2017-11-12
 *
 * <파일 설명>
 * 배고픔을 달래는 메인 씬입니다.
 * 플레이어는 현재 코딩력에 따라 음식을 선택할 수 있습니다.
 * 코딩력이 낮다면 먹을 수 있는 음식도 별로 없습니다.
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