/*
 * <제작 날짜>
 * 2017-10-25
 *
 * <파일 설명>
 * 스테이지의 정보입니다.
 * 지금은 CMD를 이용하고 있으므로 문자로 스테이지를 출력합니다.
 * 나중에 이미지를 적용하게 되면 이미지로 스테이지를 출력할 수 있습니다.
 */

#include "object/tile_info.h"

namespace object
{

	TileInfo::TileInfo()
	{
		m_type = TILE_TYPE::NONE;
	}

	TileInfo::~TileInfo()
	{
		
	}

} // namespace object end