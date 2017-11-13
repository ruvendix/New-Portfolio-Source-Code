/*
 * <���� ��¥>
 * 2017-11-13
 *
 * <���� ����>
 * C++�� �����ϴ� ���� ���Դϴ�.
 */

#ifndef PROGRAMMER_RPG__STUDY_CPP_H_
#define PROGRAMMER_RPG__STUDY_CPP_H_

#include "common.h"
#include "global_data.h"
#include "scene/scene_base.h"
#include "scene/sub_scene/sub_scene_type.h"

namespace scene
{

	class StudyCPP : public SceneBase
	{
	public:
		StudyCPP();
		~StudyCPP();

		virtual SCENE_STATE Initialize();
		virtual SCENE_STATE Update();
		virtual SCENE_STATE Render();
		virtual SCENE_STATE Release();

	private:
		std::vector<ASCII**>     m_vecContents;
		STUDY_STATE              m_studyState;
		bool                     m_bFirstPage;
		bool                     m_bLastPage;
	};

} // namespace scene end

#endif