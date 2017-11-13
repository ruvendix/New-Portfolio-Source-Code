/*
 * <���� ��¥>
 * 2017-11-11
 *
 * <���� ����>
 * ������ �ΰ��� ���Դϴ�.
 * �ΰ��ӿ����� �÷��̾ ������ �� �� �ֽ��ϴ�.
 */

#ifndef PROGRAMMER_RPG__INGAME_H_
#define PROGRAMMER_RPG__INGAME_H_

#include "scene/scene_base.h"
#include "scene/sub_scene/sub_scene_type.h"

namespace scene
{

	class Ingame : public SceneBase
	{
	public:
		Ingame();
		virtual ~Ingame();

		virtual SCENE_STATE Initialize() override;
		virtual SCENE_STATE Update()     override;
		virtual SCENE_STATE Render()     override;
		virtual SCENE_STATE Release()    override;

		SUB_SCENE_TYPE _GotoStudy();
		SUB_SCENE_TYPE _GotoHunger();
		SUB_SCENE_TYPE _GotoSociety();

	protected:
		VecSubSceneType      m_vecSubSceneFunc;
		scene::SceneBase*    m_pNowSubScene;
	};

} // namespace scene end

#endif