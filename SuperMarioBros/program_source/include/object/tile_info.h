/*
 * <���� ��¥>
 * 2017-10-25
 *
 * <���� ����>
 * ���������� �����Դϴ�.
 * ������ CMD�� �̿��ϰ� �����Ƿ� ���ڷ� ���������� ����մϴ�.
 * ���߿� �̹����� �����ϰ� �Ǹ� �̹����� ���������� ����� �� �ֽ��ϴ�.
 */

#ifndef SIDESCROLLING__TILE_INFO_H_
#define SIDESCROLLING__TILE_INFO_H_

#include "object/object_base_info.h"
#include "global_data.h"

namespace object
{

	// ���������� Ÿ�Ϸ� �����˴ϴ�.
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