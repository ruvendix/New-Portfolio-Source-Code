/*
 * <�ۼ� ��¥>
 * 2017-10-11
 *
 * <���� ����>
 * ���� �����մϴ�.
 * ���� ���Ͽ��� ���� ������ ���� �������� �����˴ϴ�.
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
		// ������ Win32 API�� �̿����� �����Ƿ� �ʿ��� ��� ������Ʈ�� ����ؾ� �մϴ�.
		Position2D playerPos = mgr::GameManager::ActivateManager().getPlayerPos();
		std::list<EffectBase*> listEffect = mgr::EffectManager::AcitvateInstance().getEffectList();

		for (INT32 i = 0; i < MAP_HEIGHT; ++i)
		{
			// ���Ͽ��� ���� ���� �� ���� ���ڱ��� �����Ƿ�
			// ������ �������� ����� �����ؾ� �մϴ�.
			for (INT32 j = 0; j < MAP_WIDTH - 1; ++j)
			{
				BOOL bEffectRendering = false;
				STRING strEffectShape = "";

				// ������ ��, ����Ʈ, ��ź, �÷��̾� ������ ���̾ �����ؾ� ������
				// ������ ��� ��ǥ�� �ǵ帮�� �����Ƿ� ���̾�� �ϳ����� ��� �����մϴ�.
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
					printf("��");
				}
				else
				{
					printf("%s", m_mapObjectShapeTable[m_map[i][j]].c_str());
				}
			}

			printf("\n");
		}

#ifndef _NDEBUG
		printf("���� ��ǥ : (%d, %d)\n", m_startPos.x, m_startPos.y);
		printf("���� ��ǥ : (%d, %d)\n", m_endPos.x, m_endPos.y);
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

				// ASCII�� ������ ��ȯ�մϴ�.
				m_map[i][j] = readData - '0';

				// ���� ��ǥ�� ���� ��ǥ�� �����մϴ�.
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
		m_mapObjectShapeTable[static_cast<INT32>(MAP_OBJECT_SHAPE::HARD_WALL)]         = "��";
		m_mapObjectShapeTable[static_cast<INT32>(MAP_OBJECT_SHAPE::SOFT_WALL)]         = "��";
		m_mapObjectShapeTable[static_cast<INT32>(MAP_OBJECT_SHAPE::START)]             = "��";
		m_mapObjectShapeTable[static_cast<INT32>(MAP_OBJECT_SHAPE::GOAL)]              = "��";
		m_mapObjectShapeTable[static_cast<INT32>(MAP_OBJECT_SHAPE::BOMB)]              = "��";
		m_mapObjectShapeTable[static_cast<INT32>(MAP_OBJECT_SHAPE::ITEM_POWER)]        = "��";
		m_mapObjectShapeTable[static_cast<INT32>(MAP_OBJECT_SHAPE::ITEM_TRANSPARENCY)] = "��";
		m_mapObjectShapeTable[static_cast<INT32>(MAP_OBJECT_SHAPE::ITEM_WALL_PUSH)]    = "��";
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