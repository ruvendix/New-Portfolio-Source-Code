/*
 * <���� ��¥>
 * 2017-11-04
 *
 * <���� ����>
 * �÷��̾�� �����Ǵ� HUD(Head Up Display)�Դϴ�.
 * HUD�� �÷��̾�� �ʿ��� ������ �����ݴϴ�.
 */

#ifndef SIDESCROLLING__PLAYER_HUD_H_
#define SIDESCROLLING__PLAYER_HUD_H_

#include "UI/UI_base.h"

namespace object
{
	class PlayerInfo;
}

namespace UI
{

	class PlayerHUD : public UIBase
	{
	public:
		PlayerHUD();
		virtual ~PlayerHUD();

		virtual void Initialize() override;

		void ShowHUD();
		void ShowClearMessage();
		void ShowAllClearMessage();

		void _ShowUnderLine();
		void _ShowPlayerLife();
		void _ShowLimitTime();
		void _ShowPlayerScore();
		void _ShowCurrentStageNum();

		// getter
		bool getClearMessage() const noexcept
		{
			return m_bClearMessage;
		}

		// setter
		void setClearMessage(bool bClearMessage)
		{
			m_bClearMessage = bClearMessage;
		}

	private:
		obj::PlayerInfo*    m_pPlayerInfo;

		bool                m_bClearMessage;
	};

} // namespace UI end

#endif