/*
 * <���� ��¥>
 * 2017-11-12
 *
 * <���� ����>
 * �÷��̾��� �⺻ �����Դϴ�.
 */

#include "object/player.h"
#include "object/player_info.h"

#include "manager/mgr_linker.h"

namespace object
{

	Player::Player()
	{
		m_pPlayerInfo = nullptr;
	}

	Player::~Player()
	{
		cmn::SafeDelete(&m_pPlayerInfo);
	}

	OBJECT_STATE Player::Initialize()
	{
		if (Chara::Initialize() == OBJECT_STATE::INIT_FAIL)
		{
			return OBJECT_STATE::INIT_FAIL;
		}

		m_pPlayerInfo = new obj::PlayerInfo;

		while (true)
		{
			printf("�̸��� �Է��ϼ���(6���� ����) : ");
			StringBuffer strBuffer;
			m_pPlayerInfo->m_strName = g_pUserInputMgr->InputString(&strBuffer);
			g_pUserInputMgr->FlushBuffer();

			if (m_pPlayerInfo->m_strName.size() > 6 * 2)
			{
				cmn::ShowMessageAutoNewLine("�̸��� ���� �Ǵ� 6���� �̻� �Է��� �� �����ϴ�!\n");
			}
			else
			{
				break;
			}
		}

		return OBJECT_STATE::INIT_SUCCESS;
	}

	OBJECT_STATE Player::Update()
	{

		return OBJECT_STATE::UPDATE_SUCCESS;
	}

	OBJECT_STATE Player::Render()
	{
		printf("�̸� : %12s\t", m_pPlayerInfo->m_strName.c_str());
		printf("�ൿ�� : ");
		for (INT32 i = 0; i < m_pPlayerInfo->m_act; ++i)
		{
			printf("��");
		}
		printf("\n");
		
		printf("ü�� :    (%03d/%03d)\t", m_pPlayerInfo->m_hp, m_pPlayerInfo->m_hpMax);
		printf("�ڵ��� : %04d\t", m_pPlayerInfo->m_coding_power);
		printf("�ڵ� ��� : %d\n", m_pPlayerInfo->m_coding_grade);
		cmn::ShowSoftBorderAutoNewLine();

		return OBJECT_STATE::RENDER_SUCCESS;
	}

	OBJECT_STATE Player::Release()
	{

		return OBJECT_STATE::RELEASE_SUCCESS;
	}

	STUDY_STATE Player::StudyProgramming(STUDY_TYPE type, INT32 maxPage)
	{
		if (m_pPlayerInfo->m_hp <= 0)
		{
			cmn::ShowMessageAutoNewLine("ü���� �����մϴ�!");
			return STUDY_STATE::LACK_HP;
		}

		if (m_pPlayerInfo->m_act <= 0)
		{
			cmn::ShowMessageAutoNewLine("�ൿ���� �����մϴ�!");
			return STUDY_STATE::LACK_ACT;
		}
		
		switch (type)
		{
		case STUDY_TYPE::C:
			if (m_pPlayerInfo->m_hp < 20)
			{
				cmn::ShowMessageAutoNewLine("ü���� �����մϴ�!");
				return STUDY_STATE::LACK_HP;
			}

			m_pPlayerInfo->m_hp -= 20;
			m_pPlayerInfo->m_coding_power += 50;

			++m_pPlayerInfo->m_cPage;
			if (m_pPlayerInfo->m_cPage >= maxPage)
			{
				--m_pPlayerInfo->m_cPage;
				return STUDY_STATE::OVER_PAGE;
			}

			--m_pPlayerInfo->m_act;
			break;
		case STUDY_TYPE::CPP:
			if (m_pPlayerInfo->m_hp < 60)
			{
				cmn::ShowMessageAutoNewLine("ü���� �����մϴ�!");
				return STUDY_STATE::LACK_HP;
			}

			m_pPlayerInfo->m_coding_power += 150;
			m_pPlayerInfo->m_hp -= 60;

			++m_pPlayerInfo->m_cppPage;
			if (m_pPlayerInfo->m_cppPage >= maxPage)
			{
				--m_pPlayerInfo->m_cppPage;
				return STUDY_STATE::OVER_PAGE;
			}

			--m_pPlayerInfo->m_act;
			break;
		}
		return STUDY_STATE::NONE;
	}

	// ���� �������� ���ư��� �� �ൿ�°� ü�¿� ������ ��ġ�� �ʽ��ϴ�.
	// ������ �ٽ� ���� �������� �Ѿ�� �ൿ�°� ü���� ���ҵ˴ϴ�.
	STUDY_STATE Player::BackToPreviousPage(STUDY_TYPE type)
	{	
		switch (type)
		{
		case STUDY_TYPE::C:
			--m_pPlayerInfo->m_cPage;

			if (m_pPlayerInfo->m_cPage < 0)
			{
				m_pPlayerInfo->m_cPage = 0;
				return STUDY_STATE::LESS_PAGE;
			}

			break;
		case STUDY_TYPE::CPP:
			--m_pPlayerInfo->m_cppPage;

			if (m_pPlayerInfo->m_cppPage < 0)
			{
				m_pPlayerInfo->m_cppPage = 0;
				return STUDY_STATE::LESS_PAGE;
			}

			break;
		}

		return STUDY_STATE::NONE;
	}

	void Player::RecoverHP(INT32 hp)
	{
		m_pPlayerInfo->m_hp += hp;

		if (m_pPlayerInfo->m_hp >= m_pPlayerInfo->m_hpMax)
		{
			m_pPlayerInfo->m_hp = m_pPlayerInfo->m_hpMax;
		}
	}

	void Player::DecreaseAct()
	{
		--m_pPlayerInfo->m_act;

		if (m_pPlayerInfo->m_act < 0)
		{
			m_pPlayerInfo->m_act = 0;
		}
	}

	bool Player::FullHP()
	{
		return (m_pPlayerInfo->m_hp == m_pPlayerInfo->m_hpMax);
	}

} // namespace object end