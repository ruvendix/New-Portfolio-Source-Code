/*
 * <제작 날짜>
 * 2017-11-12
 *
 * <파일 설명>
 * 플레이어의 기본 정보입니다.
 */

#include "object/player_info.h"

namespace object
{

	PlayerInfo::PlayerInfo()
	{
		m_act = 10;
		m_coding_power = 0;
		m_coding_grade = 1;
		m_hp = m_hpMax = 100;
		m_cPage   = 0;
		m_cppPage = 0;
	}

	PlayerInfo::~PlayerInfo()
	{

	}

} // namespace object end