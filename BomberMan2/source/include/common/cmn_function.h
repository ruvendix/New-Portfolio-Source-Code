/*
 * <작성 날짜>
 * 2017-10-11
 *
 * <파일 설명>
 * 공용되는 함수가 선언 및 정의되어있습니다.
 * 함수 템플릿과 인라인 함수는 헤더 파일에 정의해야 합니다.
 * 템플릿 인자는 _Ty로 표기합니다.
 *
 * __forceinline으로 선언하면 강제로 인라인이 적용되지만
 * 되도록이면 인라인이 가능한 부분에만 사용하는 게 좋습니다.
 * 반복문, 재귀호출, 가상 등에는 인라인이 적용되지 않습니다.
 * 인라인 함수는 되도록이면 10줄 이하로 작성하는 게 좋습니다.
 */

#ifndef EASIEST_COMMON_FUNCTION_H_
#define EASIEST_COMMON_FUNCTION_H_

#include "cmn_header.h"
#include "cmn_type.h"

namespace common
{
	
	// 포인터의 동적할당을 해제하고 nullptr로 만들어주는 함수
	// 포인터가 가리키는 주소를 변경해야 하므로 더블 포인터를 인자로 받습니다.
	// 인자를 역참조해서 값을 변경해야 한다면 포인터를 인자로 받고
	// 값만 참조해야 한다면 레퍼런스를 사용하고 있습니다.
	template <typename _Ty>
	void SafeDelete(_Ty** pptr)
	{
		if (*pptr != nullptr)
		{
			delete *pptr;
			*pptr = nullptr;
		}
	}
	
	// int* pNumTable = new int[10];
	// 위에 있는 것처럼 [ ]으로 할당했을 때는 [ ]으로 해제해야 합니다.
	// [ ]을 대괄호라고 하며 영어로는 Square Brackets라고 합니다.
	template <typename _Ty>
	void SafeDeleteSquareBrackets(_Ty** ptr)
	{
		if (*ptr != nullptr)
		{
			delete[] *ptr;
			*ptr = nullptr;
		}
	}

	template <typename _Ty>
	void SafeFree(_Ty** pptr)
	{
		if (*pptr != nullptr)
		{
			free(*pptr);
			*pptr = nullptr;
		}
	}

	// Rhs => Right Hand Side(우변)
	// 반대말은 Lhs => Left Hand Side(좌변)
	template <typename _Ty>
	void SwapData(_Ty* pRhs1, _Ty* pRhs2)
	{
		_Ty temp = *pRhs1;
		*pRhs1   = *pRhs2;
		*pRhs2   = temp;
	}

	template <typename _Ty>
	void InitializeMemory(_Ty* ptr)
	{
		memset(ptr, 0, sizeof(_Ty));
	}

	template <typename _Ty>
	void InitializeMemory(_Ty* ptr, size_t size)
	{
		memset(ptr, 0, sizeof(_Ty) * size);
	}

	template <typename _Ty, size_t _size>
	void InitializeArray(ARRAY<_Ty*, _size>* ptr)
	{
		for (size_t i = 0; i < ptr->size(); ++i)
		{
			(*ptr)[i] = nullptr;
		}
	}
	
	__forceinline void PauseProgram()
	{
		printf("계속하려면 아무 키나 누르세요.\n");
		_getch();
	}

	// 콘솔창의 좌표를 조작할 때는
	// 다른 함수로 변경할 예정입니다.
	__forceinline void ClearScreen()
	{
		system("cls");
	}

	__forceinline void ShowMessageAutoNewLine(const char* message)
	{
		printf("%s\n", message);
	}

	void InitializeBoolArray(BOOL boolArray[], INT32 size, BOOL bChoice);

} // namespace common end
namespace cmn = common;

#endif