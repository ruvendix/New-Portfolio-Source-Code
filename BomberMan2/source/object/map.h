/*
 * <작성 날짜>
 * 2017-10-11
 *
 * <파일 설명>
 * 맵을 구현합니다.
 * 맵은 파일에서 읽은 값으로 레벨 디자인이 설정됩니다.
 */

#ifndef EASIEST_OBJECT_MAP_H_
#define EASIEST_OBJECT_MAP_H_

#include "object_base.h"

namespace object
{

	class Map : public ObjectBase
	{
	public:
		Map();
		virtual ~Map() = default;

		virtual INT32 Initialize() override;
		virtual INT32 Update()     override;
		virtual INT32 Render()     override;
		virtual INT32 Release()    override;

		void SwapMapObject(const Position2D& oldPos, const Position2D& nowPos);
		void EnrollMapObjectCollisionValue(INT32* pCollisionValue, const Position2D& objectPos);
		void EnrollMapObjectForObjectPos(const Position2D& objectPos, const MAP_OBJECT_SHAPE& mapObject);

		void _ReadMapData();
		void _InitializeMapObject();

		BOOL _CheckValidMapObject(const MAP_OBJECT_SHAPE& mapObject);

		const Position2D& getStartPos() const noexcept
		{
			return m_startPos;
		}

		const Position2D& getEndPos() const noexcept
		{
			return m_endPos;
		}

	private:
		INT32      m_map[MAP_HEIGHT][MAP_WIDTH];
		STRING     m_mapObjectShapeTable[static_cast<INT32>(MAP_OBJECT_SHAPE::END)];
		Position2D m_startPos;
		Position2D m_endPos;
	};

} // namespace object end
namespace obj = object;

#endif;