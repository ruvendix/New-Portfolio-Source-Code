/*
 * <제작 날짜>
 * 2017-11-12
 *
 * <파일 설명>
 * 캐릭터의 기본 구현입니다.
 * 모든 캐릭터는 Chara 클래스를 기반으로 구현됩니다.
 */

#include "object/chara.h"

namespace object
{

	Chara::Chara()
	{

	}

	Chara::~Chara()
	{

	}

	OBJECT_STATE Chara::Initialize()
	{
		return OBJECT_STATE::INIT_SUCCESS;
	}

	OBJECT_STATE Chara::Update()
	{
		return OBJECT_STATE::UPDATE_SUCCESS;
	}

	OBJECT_STATE Chara::Render()
	{
		return OBJECT_STATE::RENDER_SUCCESS;
	}

	OBJECT_STATE Chara::Release()
	{
		return OBJECT_STATE::RELEASE_SUCCESS;
	}

} // namespace object end