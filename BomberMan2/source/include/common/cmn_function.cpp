/*
 * <�ۼ� ��¥>
 * 2017-10-14
 *
 * <���� ����>
 * �Լ� ���ø�, �ζ��� �Լ��� ������ �Լ��� ���ǵǾ��ֽ��ϴ�.
 * ����Ǵ� �Լ����� ������ �����ϰų� 10�� �̻��� �Լ���
 * ���⿡ �����ؾ� �մϴ�.
 */

#include "cmn_function.h"

namespace common
{

	void InitializeBoolArray(BOOL boolArray[], INT32 size, BOOL bChoice)
	{
		for (int i = 0; i < size; ++i)
		{
			boolArray[i] = bChoice;
		}
	}

} // namespace common end