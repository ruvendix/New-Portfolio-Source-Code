/*
 * <작성 날짜>
 * 2017-10-11
 *
 * <파일 설명>
 * 공용되는 형식이 선언되있습니다.
 * 기본 형식을 재정의한 것도 포함됩니다.
 * 형식이 단어 하나로도 표현 가능하면 대문자로 표기합니다. (int => INT)
 * 형식이 단어 두 개 이상으로 표현해야 한다면 파스칼로 표기합니다. (std::unique_ptr UniquePTR)
 * 형식의 단어가 유명하거나 축약 가능하면 그 방식을 따릅니다. (vetexarray => VtxArr)
 * 사용하다가 가독성이 떨어지는 단어진다고 생각되는 단어들은 수정합니다.
 */

#ifndef EASIEST_COMMON_TYPE_H_
#define EASIEST_COMMON_TYPE_H_

#include "cmn_header.h"

typedef signed char           ASCII;
typedef std::string           STRING;
						      
typedef signed char           INT8;
typedef signed short          INT16;
typedef signed long           INT32;
typedef signed long long      INT64;
						      
typedef unsigned char         UINT8;
typedef unsigned short        UINT16;
typedef unsigned long         UINT32;
typedef unsigned long long    UINT64;
						      
typedef float                 FLOAT32;
typedef double                FLOAT64;
						      
typedef bool                  BOOL;

// 템플릿은 <typename _형식명>으로 표현합니다.
// 템플릿은 using을 이용하면 typedef처럼 사용할 수 있습니다.
// size_t는 기본 재정의 형식으로 사용합니다.
template <typename _Ty, size_t _size>
using ARRAY = std::array<_Ty, _size>;

template <typename _Ty, typename _Alloc = std::allocator<_Ty> >
using VECTOR = std::vector<_Ty, _Alloc>;

template <typename _Ty, typename _Alloc = std::allocator<_Ty> >
using LIST = std::list<_Ty, _Alloc>;

// 형식 이름이 너무 길 때는 축약해서 사용합니다.
// 하지만 namespace pollution을 우려해서 using namespace는 사용하지 않습니다.
// typedef는 using으로 변경 가능합니다.
typedef std::chrono::steady_clock::time_point TimePoint;

// using으로 변경한 예제
// using TimePoint = std::chrono::steady_clock::time_point;

#endif