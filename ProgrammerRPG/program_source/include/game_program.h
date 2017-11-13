/*
 * <제작 날짜>
 * 2017-11-11
 *
 * <파일 설명>
 * 게임 매니저를 실행해줍니다.
 */

#ifndef PROGRAMMER_RPG__GAME_PROGRAM_H_
#define PROGRAMMER_RPG__GAME_PROGRAM_H_

#include "common.h"

class GamePgm
{
	DEFINE_SINGLETON_CLASS(GamePgm);

public:
	void DriveGame();
};

#endif