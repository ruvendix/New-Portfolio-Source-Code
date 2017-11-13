/*
 * <���� ��¥>
 * 2017-11-11
 *
 * <���� ����>
 * ������ Ÿ��Ʋ ���Դϴ�.
 * Ÿ��Ʋ������ ���� ����, �ҷ�����, ���ᰡ �����մϴ�.
 */

#ifndef PROGRAMMER_RPG__TITLE_H_
#define PROGRAMMER_RPG__TITLE_H_

#include "scene/scene_base.h"

namespace scene
{

	class Title : public SceneBase
	{
	public:
		Title();
		virtual ~Title();

		virtual SCENE_STATE Initialize() override;
		virtual SCENE_STATE Update()     override;
		virtual SCENE_STATE Render()     override;
		virtual SCENE_STATE Release()    override;

		SCENE_STATE NewGame();
		SCENE_STATE LoadUser();
		SCENE_STATE ExitGame();

	private:
		VecSceneState    m_vecTitleFunc;
		ASCII**          m_ppTitle;
	};

} // namespace scene end

#endif