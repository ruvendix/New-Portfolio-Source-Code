/*
 * <제작 날짜>
 * 2017-10-24
 *
 * <파일 설명>
 * 게임 프로그램을 작동시키는 함수를 제공합니다.
 */

#ifndef SIDESCROLLING__GAME_PROGRAM_H_
#define SIDESCROLLING__GAME_PROGRAM_H_

#include "common.h"

class GameProgram
{
	DEFINE_SINGLETON_CLASS(GameProgram);

public:
	void DriveGame();
};

#endif