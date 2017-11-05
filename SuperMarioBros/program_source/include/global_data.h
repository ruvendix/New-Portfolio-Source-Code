/*
 * <제작 날짜>
 * 2017-10-25
 *
 * <파일 설명>
 * 게임 안에서만 사용되는 전역 정보입니다.
 */

#ifndef SIDESCROLLING__GLOBAL_DATA_H_
#define SIDESCROLLING__GLOBAL_DATA_H_

#include "common_type.h"

enum class TILE_TYPE : INT32
{
	NONE = -1,
	EMPTY,
	BLOCK,
	COIN,
	START,
	GOAL,
	ITEM_GROWTH,
	ITEM_SHOOT,
	MONSTER,
	END,
};

struct StageInfo
{
	STRING        name;
	INT32         width;
	INT32         widthBorder;
	INT32         height;
	INT32         heightBorder;
	INT32         heightBorderRenderBegin;
	INT32         heightBorderRenderEnd;
	INT32         limitTime;

	Position2D    startPos;
	Position2D    endPos;
};

const STRING g_tileShapeTable[] = { "  ", "■", "♥", "◐", "◑", "◎", "♨", "♠" };

const INT32  MAX_BULLET = 5;

#endif