/*
 * <작성 날짜>
 * 2017-10-11
 *
 * <파일 설명>
 * 맵을 구현합니다.
 * 맵은 파일에서 읽은 값으로 레벨 디자인이 설정됩니다.
 */

#include "map.h"

#include "../manager/collision_manager.h"
#include "../manager/effect_manager.h"
#include "../manager/file_manager.h"
#include "../manager/game_manager.h"

#include "effect/effect_base.h"

namespace object
{

	Map::Map()
	{
		memset(m_map, 0, sizeof(m_map));
		CopyPos(&m_startPos, 0, 0);
		CopyPos(&m_endPos, 0, 0);
	}

	INT32 Map::Initialize()
	{
		_ReadMapData();
		_InitializeMapObject();

		return 0;
	}

	INT32 Map::Update()
	{
		return 0;
	}

	INT32 Map::Render()
	{
		// 지금은 Win32 API를 이용하지 않으므로 맵에서 모든 오브젝트를 출력해야 합니다.
		Position2D playerPos = mgr::GameManager::ActivateManager().getPlayerPos();
		std::list<EffectBase*> listEffect = mgr::EffectManager::AcitvateInstance().getEffectList();

		for (INT32 i = 0; i < MAP_HEIGHT; ++i)
		{
			// 파일에서 값을 읽을 때 개행 문자까지 읽으므로
			// 가로의 최종값은 출력을 생략해야 합니다.
			for (INT32 j = 0; j < MAP_WIDTH - 1; ++j)
			{
				BOOL bEffectRendering = false;
				STRING strEffectShape = "";

				// 원래는 맵, 이펙트, 폭탄, 플레이어 순으로 레이어를 형성해야 하지만
				// 지금은 출력 좌표를 건드리지 않으므로 레이어당 하나씩만 출력 가능합니다.
				for (EffectBase* k : listEffect)
				{
					assert(k != nullptr);
					if (k != nullptr)
					{
						if (CheckSamePos(k->getNowPos(), j, i))
						{
							bEffectRendering = true;
							strEffectShape = k->getShape();
						}
					}
				}

				if (bEffectRendering)
				{
					printf("%s", strEffectShape.c_str());
				}
				else if ( (playerPos.x == j) &&
					      (playerPos.y == i) )
				{
					printf("＠");
				}
				else
				{
					printf("%s", m_mapObjectShapeTable[m_map[i][j]].c_str());
				}
			}

			printf("\n");
		}

#ifndef _NDEBUG
		printf("시작 좌표 : (%d, %d)\n", m_startPos.x, m_startPos.y);
		printf("목적 좌표 : (%d, %d)\n", m_endPos.x, m_endPos.y);
#endif

		return 0;
	}

	INT32 Map::Release()
	{
		return 0;
	}

	void Map::SwapMapObject(const Position2D& oldPos, const Position2D& nowPos)
	{
		cmn::SwapData(&m_map[oldPos.y][oldPos.x], &m_map[nowPos.y][nowPos.x]);
	}

	void Map::EnrollMapObjectCollisionValue(INT32* pCollisionValue, const Position2D& objectPos)
	{
		mgr::CollisionManager::ActivateManager().EnrollCollisionValue(pCollisionValue,
			m_map[objectPos.y][objectPos.x]);
	}

	void Map::EnrollMapObjectForObjectPos(const Position2D& objectPos, const MAP_OBJECT_SHAPE& mapObject)
	{
		BOOL bResult = _CheckValidMapObject(mapObject);
		assert(bResult != false);

		m_map[objectPos.y][objectPos.x] = static_cast<INT32>(mapObject);
	}

	void Map::_ReadMapData()
	{
		FILE* pMapDataFile = mgr::FileManager::ActivateManager().OpenFileStream("map.txt", "rt");
		assert(pMapDataFile != nullptr);

		for (INT32 i = 0; i < MAP_HEIGHT; ++i)
		{
			for (INT32 j = 0; j < MAP_WIDTH; ++j)
			{
				INT32 readData = fgetc(pMapDataFile);

				// ASCII를 정수로 변환합니다.
				m_map[i][j] = readData - '0';

				// 시작 좌표와 목적 좌표를 설정합니다.
				if (m_map[i][j] == static_cast<INT32>(MAP_OBJECT_SHAPE::START))
				{
					CopyPos(&m_startPos, j, i);
				}
				else if (m_map[i][j] == static_cast<INT32>(MAP_OBJECT_SHAPE::GOAL))
				{
					CopyPos(&m_endPos, j, i);
				}
			}
		}

		mgr::FileManager::ActivateManager().CloseFileStream(pMapDataFile);
	}

	void Map::_InitializeMapObject()
	{
		m_mapObjectShapeTable[static_cast<INT32>(MAP_OBJECT_SHAPE::ROAD)]              = "  ";
		m_mapObjectShapeTable[static_cast<INT32>(MAP_OBJECT_SHAPE::HARD_WALL)]         = "■";
		m_mapObjectShapeTable[static_cast<INT32>(MAP_OBJECT_SHAPE::SOFT_WALL)]         = "▩";
		m_mapObjectShapeTable[static_cast<INT32>(MAP_OBJECT_SHAPE::START)]             = "★";
		m_mapObjectShapeTable[static_cast<INT32>(MAP_OBJECT_SHAPE::GOAL)]              = "☆";
		m_mapObjectShapeTable[static_cast<INT32>(MAP_OBJECT_SHAPE::BOMB)]              = "♨";
		m_mapObjectShapeTable[static_cast<INT32>(MAP_OBJECT_SHAPE::ITEM_POWER)]        = "◈";
		m_mapObjectShapeTable[static_cast<INT32>(MAP_OBJECT_SHAPE::ITEM_TRANSPARENCY)] = "⊙";
		m_mapObjectShapeTable[static_cast<INT32>(MAP_OBJECT_SHAPE::ITEM_WALL_PUSH)]    = "☞";
	}

	BOOL Map::_CheckValidMapObject(const MAP_OBJECT_SHAPE& mapObject)
	{
		if (mapObject >= MAP_OBJECT_SHAPE::END)
		{
			return false;
		}

		return true;
	}

} // namespace object end