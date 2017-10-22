/*
 * <�ۼ� ��¥>
 * 2017-10-12
 *
 * <���� ����>
 * ����Ǵ� ���� ���ǵǾ��ֽ��ϴ�.
 * ��ũ�� ��� ��� const�� ����մϴ�.
 * �������� ����ü�� ���⿡ ���ǵ˴ϴ�.
 */

#ifndef DEVELOPMENT_GLOBAL_DATA_H_
#define DEVELOPMENT_GLOBAL_DATA_H_

#include "common/cmn_type.h"

// ����� �� ũ�Ⱑ �����Ǿ��ֽ��ϴ�.
// ���������� �����Ϸ��� �� ũ�⸦ ���Ͽ���
// �о�� �� �� ũ�� ������ ���� �о������ �����ؾ� �մϴ�.
// ���� ũ�Ⱑ ���̺��� �ϳ� �� ���� ������ ���Ͽ��� ���� �о�� ��
// ���� ���ڱ��� �о���� �����Դϴ�. ���� �� ������ �ϳ� �ʿ��մϴ�.
const INT32 MAP_WIDTH  = 21;
const INT32 MAP_HEIGHT = 20;

const INT32 MAP_START_BORDER_WIDTH  = 1;
const INT32 MAP_START_BORDER_HEIGHT = 1;
const INT32 MAP_END_BORDER_WIDTH    = MAP_WIDTH  - 3; // ����, ��, ���� ����
const INT32 MAP_END_BORDER_HEIGHT   = MAP_HEIGHT - 2; // ����, ��

const INT32 MAX_PLAYER_BOMB_POWER = 5;

// 30 �������� �ʴ� 0.3333�� ���� �ǰ�
// 60 �������� �ʴ� 0.1666�� ���� �˴ϴ�.
const FLOAT32 THIRTY_FRAME_TIME = 1.0f / 30.0f;
const FLOAT32 SIXTY_FRAME_TIME  = 1.0f / 60.0f;

const FLOAT32 BOMB_EXPLOSION_TIME = 2.0f;

// �������� ���������� ��ȯ�� ���� ����
// enum class�� �ۼ��մϴ�.
// NONE�� ������ �ε����� ������� �ʴ� �������Դϴ�.
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

// ����� ���� ���ڿ����� ���������� ������ ������Ʈ �����͸� �����ؼ�
// �浹 �˻縦 �� �Ŀ� �浹�� ������Ʈ�� ������ �˾Ƴ��� �մϴ�.
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