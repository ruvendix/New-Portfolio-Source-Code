/*
 * <제작 날짜>
 * 2017-11-11
 *
 * <파일 설명>
 * 씬을 관리하는 매니저입니다.
 * 모든 씬은 기본 씬을 기반으로 구현됩니다.
 */

#ifndef PROGRAMMER_RPG__MANAGER_H_
#define PROGRAMMER_RPG__MANAGER_H_

#include "common.h"
#include "scene/sub_scene/sub_scene_type.h"

namespace scene
{
	class SceneBase;
}

namespace manager
{

	class SceneMgr
	{
		DEFINE_SINGLETON_CLASS(SceneMgr);

	public:
		void ResetScene();
		void ResetSubScene(scene::SceneBase** ppSubScene);
		void SelectMenu(INT32* pSelMenu, INT32 min, INT32 max);

		bool InitializeScene();
		bool ChangeScene(SCENE_TYPE type);
		bool ChangeSubScene(SUB_SCENE_TYPE type, scene::SceneBase** ppSubScene);
		bool AdjustSubScene(const VecSubSceneType& vecSubSceneType, INT32 selMenu,
			scene::SceneBase** ppSubScene, SCENE_STATE* pSceneState);

		SCENE_STATE BackToPreviousScene(SCENE_STATE subSceneState, scene::SceneBase** ppSubScene, bool* pHold);

		// getter
		scene::SceneBase* getScene() const noexcept
		{
			return m_pScene;
		}

	private:
		scene::SceneBase* m_pScene;
	};

} // namespace manager end

#endif