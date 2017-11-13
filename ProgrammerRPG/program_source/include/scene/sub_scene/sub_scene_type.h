/*
 * <제작 날짜>
 * 2017-11-12
 *
 * <파일 설명>
 * 게임의 서브 씬입니다.
 * 서브 씬은 메인 씬 안에서 동작하는 씬입니다.
 * 서브 씬은 다른 서브 씬을 포함할 수도 있습니다.
 */

#ifndef PROGRAMMER_RPG__SUB_SCENE_TYPE_H_
#define PROGRAMMER_RPG__SUB_SCENE_TYPE_H_

#include "common.h"

enum class SUB_SCENE_TYPE : INT32
{
	NONE,
	STUDY_MAIN,
	STUDY_C,
	STUDY_CPP,
	HUNGER_MAIN,
	HUNGER_CONVENIENCE_STORE,
	HUNGER_FAMOUS,
	HUNGER_RESTARUANT,
	SOCIETY_MAIN,
	SOCIETY_INTERN,
	SOCIETY_REGULAR,
	SOCIETY_PRESIDENT,
	END,
};

using VecSubSceneType = std::vector<std::function<SUB_SCENE_TYPE()> >;

#endif