/*
 * <���� ��¥>
 * 2017-11-11
 *
 * <���� ����>
 * ���� �Ŵ����� �������ݴϴ�.
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