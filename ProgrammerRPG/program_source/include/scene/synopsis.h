/*
 * <제작 날짜>
 * 2017-11-11
 *
 * <파일 설명>
 * 게임의 시놉시스 씬입니다.
 * 시놉시스는 게임의 개요를 보여줍니다.
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