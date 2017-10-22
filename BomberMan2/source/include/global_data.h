/*
 * <작성 날짜>
 * 2017-10-12
 *
 * <파일 설명>
 * 공용되는 값이 정의되어있습니다.
 * 매크로 상수 대신 const를 사용합니다.
 * 열거형과 구조체도 여기에 정의됩니다.
 */

#ifndef DEVELOPMENT_GLOBAL_DATA_H_
#define DEVELOPMENT_GLOBAL_DATA_H_

#include "common/cmn_type.h"

// 현재는 맵 크기가 고정되어있습니다.
// 유동적으로 변경하려면 맵 크기를 파일에서
// 읽어올 때 맵 크기 정보도 같이 읽어오도록 구현해야 합니다.
// 가로 크기가 높이보다 하나 더 많은 이유는 파일에서 맵을 읽어올 때
// 개행 문자까지 읽어오기 때문입니다. 따라서 빈 공간이 하나 필요합니다.
const INT32 MAP_WIDTH  = 21;
const INT32 MAP_HEIGHT = 20;

const INT32 MAP_START_BORDER_WIDTH  = 1;
const INT32 MAP_START_BORDER_HEIGHT = 1;
const INT32 MAP_END_BORDER_WIDTH    = MAP_WIDTH  - 3; // 시작, 끝, 개행 문자
const INT32 MAP_END_BORDER_HEIGHT   = MAP_HEIGHT - 2; // 시작, 끝

const INT32 MAX_PLAYER_BOMB_POWER = 5;

// 30 프레임은 초당 0.3333초 정도 되고
// 60 프레임은 초당 0.1666초 정도 됩니다.
const FLOAT32 THIRTY_FRAME_TIME = 1.0f / 30.0f;
const FLOAT32 SIXTY_FRAME_TIME  = 1.0f / 60.0f;

const FLOAT32 BOMB_EXPLOSION_TIME = 2.0f;

// 열거형은 정수형과의 변환을 막기 위해
// enum class로 작성합니다.
// NONE이 있으면 인덱스로 사용하지 않는 열거형입니다.
enum class GAME_UPDATE_STATE : INT32
{
	NONE = 0,
	PLAYER_ARRIVE_GOAL,
	PLAYER_DIE_BOMB,
	END,
};

enum class GAME_RENDER_STATE : INT32
{
	NONE = 0,
	END,
};

enum class OBJECT_DIRECTION : INT32
{
	LEFT = 0,
	UP,
	RIGHT,
	DOWN,
	END,
};

// 현재는 맵이 문자열값만 저장하지만 원래는 오브젝트 포인터를 저장해서
// 충돌 검사를 한 후에 충돌된 오브젝트의 정보를 알아내야 합니다.
enum class MAP_OBJECT_SHAPE : INT32
{
	ROAD = 0,
	HARD_WALL,
	SOFT_WALL,
	START,
	GOAL,
	BOMB,
	ITEM_POWER,
    ITEM_TRANSPARENCY,
	ITEM_WALL_PUSH,
	END,
};

enum class PLAYER_STATE : INT32
{
	NONE = 0,
	CANNOT_MOVE,
	CANNOT_DROP_BOMB_MAX,
	CANNOT_DROP_BOMB_OVERLAP,
	CANNOT_DROP_BOMB_TRANSPARENCY,
	DROP_BOMB,
	DIE_BOMB,
	MOVE_TRANSPARENCY,
	MOVE_WALL_PUSH,
	END,
};

enum class PLAYER_HAVE_ITEM : INT32
{
	POWER,
	TRANSPARENCY,
	WALL_PUSH,
	END,
};

enum class BOMB_STATE : INT32
{
	NONE = 0,
	EXPLOSION,
	EXPLOSION_HIT_PLAYER,
	END,
};

enum class EFFECT_TYPE : INT32
{
	NONE = 0,
	EXPLOSION,
	END,
};

struct Position2D
{
	INT32 x;
	INT32 y;
};

struct GameState
{
	GAME_UPDATE_STATE updateState;
	GAME_RENDER_STATE renderState;
};

#endif