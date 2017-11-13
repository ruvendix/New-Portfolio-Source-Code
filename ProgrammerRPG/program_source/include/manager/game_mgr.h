/*
 * <���� ��¥>
 * 2017-11-11
 *
 * <���� ����>
 * ������ �帧�� �����մϴ�.
 */

#ifndef PROGRAMMER_RPG__GAME_MANAGER_H_
#define PROGRAMMER_RPG__GAME_MANAGER_H_

#include "common.h"

namespace scene
{
	class SceneBase;
}

class GameMgr
{
	DEFINE_SINGLETON_CLASS(GameMgr);

	friend class GamePgm;

public:
	SCENE_STATE Initialize();
	SCENE_STATE Update();
	SCENE_STATE Render();
	SCENE_STATE Release();

private:
	scene::SceneBase*    m_pNowScene;
	SCENE_TYPE           m_nowSceneType;
};

#endif