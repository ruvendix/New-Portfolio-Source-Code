/*
 * <���� ��¥>
 * 2017-11-12
 *
 * <���� ����>
 * �����ϴ� ���� ���Դϴ�.
 * �÷��̾�� C���� C++��� �� �ϳ��� ������ �� �ֽ��ϴ�.
 * �� �����ϸ� �ٸ� ���� ���� �۵��ϰ� �˴ϴ�.
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