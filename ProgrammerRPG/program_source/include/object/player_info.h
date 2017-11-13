/*
 * <���� ��¥>
 * 2017-11-12
 *
 * <���� ����>
 * �÷��̾��� �⺻ �����Դϴ�.
 */

#ifndef PROGRAMMER_RPG__PLAYER_INFORMATION_H_
#define PROGRAMMER_RPG__PLAYER_INFORMATION_H_

#include "object/chara_info.h"

namespace object
{

	class PlayerInfo : public obj::CharaInfo
	{
		friend class Player; // private ���ٵ� ����մϴ�.

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
		INT32    m_act;          // �ൿ��
		INT32    m_coding_power; // �ڵ���
		INT32    m_coding_grade; // �ڵ� ���
		INT32    m_hp;           // ü��
		INT32    m_hpMax;        // �ִ� ü��
		INT32    m_cPage;        // ���� �����ؾ� �� C��� ������
		INT32    m_cppPage;      // ���� �����ؾ� �� C++��� ������
	};

} // namespace object end

#endif