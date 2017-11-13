/*
 * <���� ��¥>
 * 2017-11-11
 *
 * <���� ����>
 * ������ �ó�ý� ���Դϴ�.
 * �ó�ý��� ������ ���並 �����ݴϴ�.
 */

#ifndef PROGRAMMER_RPG__SYNOPSIS_H_
#define PROGRAMMER_RPG__SYNOPSIS_H_

#include "scene/scene_base.h"

namespace scene
{

	class Synopsis : public SceneBase
	{
	public:
		Synopsis();
		virtual ~Synopsis();

		virtual SCENE_STATE Initialize() override;
		virtual SCENE_STATE Update()     override;
		virtual SCENE_STATE Render()     override;
		virtual SCENE_STATE Release()    override;

	private:
		ASCII**    m_ppSynopsis;
		bool       m_bGameStart;
	};

} // namespace scene end

#endif