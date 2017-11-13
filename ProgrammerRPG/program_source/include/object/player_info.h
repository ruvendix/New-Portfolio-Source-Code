/*
 * <제작 날짜>
 * 2017-11-12
 *
 * <파일 설명>
 * 플레이어의 기본 정보입니다.
 */

#ifndef PROGRAMMER_RPG__PLAYER_INFORMATION_H_
#define PROGRAMMER_RPG__PLAYER_INFORMATION_H_

#include "object/chara_info.h"

namespace object
{

	class PlayerInfo : public obj::CharaInfo
	{
		friend class Player; // private 접근도 허용합니다.

	public:
		PlayerInfo();
		virtual ~PlayerInfo();

		// getter
		INT32 getCPage() const noexcept
		{
			return m_cPage;
		}

		INT32 getCPPPage() const noexcept
		{
			return m_cppPage;
		}

		INT32 getCodingPower() const noexcept
		{
			return m_coding_power;
		}

		INT32 getAct() const noexcept
		{
			return m_act;
		}

		INT32 getHP() const noexcept
		{
			return m_hp;
		}

	private:
		INT32    m_act;          // 행동력
		INT32    m_coding_power; // 코딩력
		INT32    m_coding_grade; // 코딩 등급
		INT32    m_hp;           // 체력
		INT32    m_hpMax;        // 최대 체력
		INT32    m_cPage;        // 현재 공부해야 할 C언어 페이지
		INT32    m_cppPage;      // 현재 공부해야 할 C++언어 페이지
	};

} // namespace object end

#endif