/*
 * <���� ��¥>
 * 2017-11-12
 *
 * <���� ����>
 * �÷��̾��� �⺻ �����Դϴ�.
 */

#ifndef PROGRAMMER_RPG__PLAYER_H_
#define PROGRAMMER_RPG__PLAYER_H_

#include "object/chara.h"
#include "global_data.h"

namespace object
{
	class PlayerInfo;
}

namespace object
{

	class Player : public obj::Chara
	{
	public:
		Player();
		virtual ~Player();

		virtual OBJECT_STATE Initialize();
		virtual OBJECT_STATE Update();
		virtual OBJECT_STATE Render();
		virtual OBJECT_STATE Release();

		STUDY_STATE StudyProgramming(STUDY_TYPE type, INT32 maxPage);
		STUDY_STATE BackToPreviousPage(STUDY_TYPE type);

		void RecoverHP(INT32 hp);
		void DecreaseAct();

		bool FullHP();

		// getter
		obj::PlayerInfo* getPlayerInfo() const noexcept
		{
			return m_pPlayerInfo;
		}

	private:
		obj::PlayerInfo*    m_pPlayerInfo;
	};

} // namespace object end

#endif