/*
 * <���� ��¥>
 * 2017-11-01
 *
 * <���� ����>
 * �Ѿ��� �����Դϴ�.
 * �Ѿ��� �÷��̾�� ������ ó���մϴ�.
 */

#include "object/bullet.h"

#include "manager_linker.h"
#include "object/object_base_info.h"
#include "object/player.h"
#include "object/player_info.h"
#include "object/stage.h"
#include "object/tile_info.h"

const INT32 MAX_BULLET_DISTANCE = 6;

namespace object
{

	Bullet::Bullet()
	{
		m_pBulletInfo = nullptr;
		m_distance    = 0;
	}

	Bullet::~Bullet()
	{

	}

	OBJECT_STATE Bullet::Initialize()
	{
		m_pBulletInfo = std::make_shared<obj::ObjectBaseInfo>();
		assert(m_pBulletInfo != nullptr);

		m_pBulletInfo->setDeltaDirection(1);
		m_pBulletInfo->setDirection(OBJECT_DIRECTION::RIGHT);
		m_pBulletInfo->setShape("��");
		m_pBulletInfo->setRenderColor(RENDERING_COLOR::INTENSITY_WHITE);

		m_distance = MAX_BULLET_DISTANCE;
		return OBJECT_STATE::INIT_OBJECT_SUCCESS;
	}

	OBJECT_STATE Bullet::Update()
	{
		if (m_distance != 0)
		{
			--m_distance;

			obj::Stage* pStage  = g_pStageMgr->getStage();
			Position2D  nextPos = *m_pBulletInfo->getNowPos();

			m_pBulletInfo->DecideDirection();

			// ���� x��ǥ�� ��ȿ�� ��ǥ���� Ȯ���մϴ�.
			et_math::AddPosX(*m_pBulletInfo->getNowPos(), m_pBulletInfo->getDeltaDirection(), &nextPos);
			const StageInfo& stageInfo = g_pStageMgr->getStage()->getStageInfo();
			TileInfo* pTileInfo = pStage->getTileInfo(nextPos);

			if ( (cmn::CheckUnderIndex(nextPos.x, 0)) ||
				 (cmn::CheckOverIndex(nextPos.x, stageInfo.width - 1)) )
			{
				return OBJECT_STATE::UPDATE_OBJECT_DELETE;
			}
			// x��ǥ�� ��ȿ�ϴٸ� �ش� ��ǥ�� Ÿ�� ������ Ȯ���մϴ�.
			else if (pTileInfo->getTileType() == TILE_TYPE::BLOCK)
			{
				return OBJECT_STATE::UPDATE_OBJECT_DELETE;
			}
			else if (g_pObjectMgr->CheckMonsterCollisionPos(
				m_pBulletInfo->getNowPosX(), m_pBulletInfo->getNowPosY()))
			{
				g_pObjectMgr->getPlayer()->getPlayerInfo()->AddScore(200);
				return OBJECT_STATE::UPDATE_OBJECT_DELETE;
			}

			et_math::AddPosX(m_pBulletInfo->getDeltaDirection(), m_pBulletInfo->getNowPos());
		}
		else
		{
			return OBJECT_STATE::UPDATE_OBJECT_DELETE;
		}

		return OBJECT_STATE::UPDATE_OBJECT_SUCCESS;
	}

	OBJECT_STATE Bullet::Render()
	{
		g_pSystemMgr->AdjustRenderColor(m_pBulletInfo->getRenderColor());
		printf("%s", m_pBulletInfo->getShape());
		return OBJECT_STATE::RENDER_OBJECT_SUCCESS;
	}

	OBJECT_STATE Bullet::Release()
	{
		return OBJECT_STATE::RELEASE_OBJECT_SUCCESS;
	}

} // namespace object end