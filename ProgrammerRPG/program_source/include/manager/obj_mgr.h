/*
 * <���� ��¥>
 * 2017-11-11
 *
 * <���� ����>
 * ������Ʈ�� �����մϴ�.
 */

#ifndef PROGRAMMER_RPG__MANAGER_OBJECT_H_
#define PROGRAMMER_RPG__MANAGER_OBJECT_H_

#include "common.h"

namespace object
{
	class Player;
}

namespace manager
{

	class ObjMgr
	{
		DEFINE_SINGLETON_CLASS(ObjMgr);

	public:
		OBJECT_STATE InitializeData();
		OBJECT_STATE InitializePlayer();

		void ReleasePlayer();

		// getter
		obj::Player* getPlayer() const noexcept
		{
			return m_pPlayer;
		}

	private:
		obj::Player*    m_pPlayer;
	};

} // namespace manager end

#endif