/*
 * <�ۼ� ��¥>
 * 2017-10-11
 *
 * <���� ����>
 * ����Ǵ� �Լ��� ���� �� ���ǵǾ��ֽ��ϴ�.
 * �Լ� ���ø��� �ζ��� �Լ��� ��� ���Ͽ� �����ؾ� �մϴ�.
 * ���ø� ���ڴ� _Ty�� ǥ���մϴ�.
 *
 * __forceinline���� �����ϸ� ������ �ζ����� ���������
 * �ǵ����̸� �ζ����� ������ �κп��� ����ϴ� �� �����ϴ�.
 * �ݺ���, ���ȣ��, ���� ��� �ζ����� ������� �ʽ��ϴ�.
 * �ζ��� �Լ��� �ǵ����̸� 10�� ���Ϸ� �ۼ��ϴ� �� �����ϴ�.
 */

#ifndef EASIEST_COMMON_FUNCTION_H_
#define EASIEST_COMMON_FUNCTION_H_

#include "cmn_header.h"
#include "cmn_type.h"

namespace common
{
	
	// �������� �����Ҵ��� �����ϰ� nullptr�� ������ִ� �Լ�
	// �����Ͱ� ����Ű�� �ּҸ� �����ؾ� �ϹǷ� ���� �����͸� ���ڷ� �޽��ϴ�.
	// ���ڸ� �������ؼ� ���� �����ؾ� �Ѵٸ� �����͸� ���ڷ� �ް�
	// ���� �����ؾ� �Ѵٸ� ���۷����� ����ϰ� �ֽ��ϴ�.
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
	// ���� �ִ� ��ó�� [ ]���� �Ҵ����� ���� [ ]���� �����ؾ� �մϴ�.
	// [ ]�� ���ȣ��� �ϸ� ����δ� Square Brackets��� �մϴ�.
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

	// Rhs => Right Hand Side(�캯)
	// �ݴ븻�� Lhs => Left Hand Side(�º�)
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
		printf("����Ϸ��� �ƹ� Ű�� ��������.\n");
		_getch();
	}

	// �ܼ�â�� ��ǥ�� ������ ����
	// �ٸ� �Լ��� ������ �����Դϴ�.
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