/*
 * <제작 날짜>
 * 2017-11-12
 *
 * <파일 설명>
 * 공부하는 메인 씬입니다.
 * 플레이어는 C언어와 C++언어 중 하나를 선택할 수 있습니다.
 * 언어를 선택하면 다른 서브 씬이 작동하게 됩니다.
 */

#ifndef PROGRAMMER_RPG__STUDY_MAIN_H_
#define PROGRAMMER_RPG__STUDY_MAIN_H_

#include "common.h"
#include "scene/ingame.h"

namespace scene
{

	class StudyMain : public Ingame
	{
	public:
		StudyMain();
		~StudyMain();

		virtual SCENE_STATE Initialize() override;
		virtual SCENE_STATE Update()     override;
		virtual SCENE_STATE Render()     override;
		virtual SCENE_STATE Release()    override;

		SUB_SCENE_TYPE _StudyC();
		SUB_SCENE_TYPE _StudyCPP();
	};

} // namespace scene end

#endif