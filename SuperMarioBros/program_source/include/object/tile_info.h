/*
 * <제작 날짜>
 * 2017-10-25
 *
 * <파일 설명>
 * 스테이지의 정보입니다.
 * 지금은 CMD를 이용하고 있으므로 문자로 스테이지를 출력합니다.
 * 나중에 이미지를 적용하게 되면 이미지로 스테이지를 출력할 수 있습니다.
 */

#ifndef SIDESCROLLING__TILE_INFO_H_
#define SIDESCROLLING__TILE_INFO_H_

#include "object/object_base_info.h"
#include "global_data.h"

namespace object
{

	// 스테이지는 타일로 구성됩니다.
	class TileInfo : public ObjectBaseInfo
	{
	public:
		TileInfo();
		virtual ~TileInfo();

		// getter
		TILE_TYPE getTileType() const noexcept
		{
			return m_type;
		}

		// setter
		void setTileType(const TILE_TYPE& tileType)
		{
			m_type = tileType;
		}

	private:
		TILE_TYPE    m_type;
	};

} // namespace object end

#endif