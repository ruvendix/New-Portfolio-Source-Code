/*
 * <제작 날짜>
 * 2017-11-11
 *
 * <파일 설명>
 * 게임의 인게임 씬입니다.
 * 인게임에서는 플레이어가 게임을 할 수 있습니다.
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