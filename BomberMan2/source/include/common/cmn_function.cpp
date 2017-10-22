/*
 * <작성 날짜>
 * 2017-10-14
 *
 * <파일 설명>
 * 함수 템플릿, 인라인 함수를 제외한 함수가 정의되어있습니다.
 * 공용되는 함수지만 구조가 복잡하거나 10줄 이상인 함수는
 * 여기에 정의해야 합니다.
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