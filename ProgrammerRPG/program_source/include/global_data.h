/*
 * <제작 날짜>
 * 2017-11-13
 *
 * <파일 설명>
 * 게임에서 사용되는 공용 정보입니다.
 */

#ifndef PROGRAMMER_RPG__GLOBAL_DATA_H_
#define PROGRAMMER_RPG__GLOBAL_DATA_H_

#include "common.h"

enum class STUDY_TYPE
{
	NONE,
	C,
	CPP,
	END,
};

enum class STUDY_STATE
{
	NONE,
	LACK_ACT,
	LACK_HP,
	OVER_PAGE,
	LESS_PAGE,
	END,
};

#endif