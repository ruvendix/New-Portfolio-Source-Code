/*
 * <���� ��¥>
 * 2017-11-12
 *
 * <���� ����>
 * ĳ������ �⺻ �����Դϴ�.
 * ��� ĳ���ʹ� Chara Ŭ������ ������� �����˴ϴ�.
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