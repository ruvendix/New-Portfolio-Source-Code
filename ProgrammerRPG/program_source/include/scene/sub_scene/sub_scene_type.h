/*
 * <���� ��¥>
 * 2017-11-12
 *
 * <���� ����>
 * ������ ���� ���Դϴ�.
 * ���� ���� ���� �� �ȿ��� �����ϴ� ���Դϴ�.
 * ���� ���� �ٸ� ���� ���� ������ ���� �ֽ��ϴ�.
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