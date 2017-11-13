/*
 * <제작 날짜>
 * 2017-11-12
 *
 * <파일 설명>
 * 사회로 진출하는 메인 씬입니다.
 * 플레이어는 현재 코딩력에 따라 음식을 선택할 수 있습니다.
 * 코딩력이 낮다면 먹을 수 있는 음식도 별로 없습니다.
 */

#ifndef PROGRAMMER_RPG__SOCIETY_MAIN_H_
#define PROGRAMMER_RPG__SOCIETY_MAIN_H_

#include "common.h"
#include "scene/scene_base.h"
#include "scene/sub_scene/sub_scene_type.h"

namespace scene
{

	class SocietyMain : public SceneBase
	{
	public:
		SocietyMain();
		~SocietyMain();

		virtual SCENE_STATE Initialize();
		virtual SCENE_STATE Update();
		virtual SCENE_STATE Render();
		virtual SCENE_STATE Release();
	};

} // namespace scene end

#endif