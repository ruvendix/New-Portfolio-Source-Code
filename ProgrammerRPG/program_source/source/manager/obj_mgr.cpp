/*
 * <���� ��¥>
 * 2017-11-11
 *
 * <���� ����>
 * ������Ʈ�� �����մϴ�.
 */

#include "manager/obj_mgr.h"
#include "object/player.h"

namespace manager
{
	OBJECT_STATE ObjMgr::InitializeData()
	{
		m_pPlayer = nullptr;
		return OBJECT_STATE::INIT_SUCCESS;
	}
	OBJECT_STATE ObjMgr::InitializePlayer()
	{
		if (m_pPlayer != nullptr)
		{
			return OBJECT_STATE::INIT_FAIL;
		}

		m_pPlayer = new obj::Player;

		if (m_pPlayer->Initialize() == OBJECT_STATE::INIT_FAIL)
		{
			return OBJECT_STATE::INIT_FAIL;
		}

		return OBJECT_STATE::INIT_SUCCESS;
	}

	void ObjMgr::ReleasePlayer()
	{
		m_pPlayer->Release();
		cmn::SafeDelete(&m_pPlayer);
	}

} // namespace manager end