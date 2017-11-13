/*
 * <���� ��¥>
 * 2017-11-12
 *
 * <���� ����>
 * ��ȸ�� �����ϴ� ���� ���Դϴ�.
 * �÷��̾�� ���� �ڵ��¿� ���� ������ ������ �� �ֽ��ϴ�.
 * �ڵ����� ���ٸ� ���� �� �ִ� ���ĵ� ���� �����ϴ�.
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