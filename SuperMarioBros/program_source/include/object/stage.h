/*
 * <제작 날짜>
 * 2017-10-25
 *
 * <파일 설명>
 * 스테이지의 구현입니다.
 */

#ifndef SIDESCROLLING__STAGE_H_
#define SIDESCROLLING__STAGE_H_

#include "object/object_base.h"
#include "global_data.h"

struct StageInfo;

namespace object
{
	class TileInfo;
}

namespace object
{

	class Stage : public ObjectBase
	{
	public:
		Stage();
		virtual ~Stage() = default;

		virtual OBJECT_STATE Initialize() override;
		virtual OBJECT_STATE Update()     override;
		virtual OBJECT_STATE Render()     override;
		virtual OBJECT_STATE Release()    override;

		OBJECT_STATE  _LoadStage(INT32 stageIdx);
		void          _AllocateBoard(INT32 width, INT32 height);
		void          _BindData();

		void          ChangeTileInfo(INT32 x, INT32 y, const TILE_TYPE& tileType);
		void          ChangeTileInfo(const Position2D& tilePos, const TILE_TYPE& tileType);

		// getter
		const StageInfo& getStageInfo() const noexcept
		{
			return *m_pStageInfo;
		}

		const Position2D& getCameraPos() const noexcept
		{
			return m_cameraPos;
		}

		INT32 getCameraPosX() const noexcept
		{
			return m_cameraPos.x;
		}

		INT32 getCameraPosY() const noexcept
		{
			return m_cameraPos.y;
		}

		TileInfo* getTileInfo(INT32 x, INT32 y);
		TileInfo* getTileInfo(const Position2D& tilePos);

	private:
		TileInfo**    m_ppBoard;					      
		StageInfo*    m_pStageInfo;
		Position2D    m_cameraPos;
	};

} // namespace object end

#endif