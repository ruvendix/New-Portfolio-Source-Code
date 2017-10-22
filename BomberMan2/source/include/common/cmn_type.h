/*
 * <�ۼ� ��¥>
 * 2017-10-11
 *
 * <���� ����>
 * ����Ǵ� ������ ������ֽ��ϴ�.
 * �⺻ ������ �������� �͵� ���Ե˴ϴ�.
 * ������ �ܾ� �ϳ��ε� ǥ�� �����ϸ� �빮�ڷ� ǥ���մϴ�. (int => INT)
 * ������ �ܾ� �� �� �̻����� ǥ���ؾ� �Ѵٸ� �Ľ�Į�� ǥ���մϴ�. (std::unique_ptr UniquePTR)
 * ������ �ܾ �����ϰų� ��� �����ϸ� �� ����� �����ϴ�. (vetexarray => VtxArr)
 * ����ϴٰ� �������� �������� �ܾ����ٰ� �����Ǵ� �ܾ���� �����մϴ�.
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

// ���ø��� <typename _���ĸ�>���� ǥ���մϴ�.
// ���ø��� using�� �̿��ϸ� typedefó�� ����� �� �ֽ��ϴ�.
// size_t�� �⺻ ������ �������� ����մϴ�.
template <typename _Ty, size_t _size>
using ARRAY = std::array<_Ty, _size>;

template <typename _Ty, typename _Alloc = std::allocator<_Ty> >
using VECTOR = std::vector<_Ty, _Alloc>;

template <typename _Ty, typename _Alloc = std::allocator<_Ty> >
using LIST = std::list<_Ty, _Alloc>;

// ���� �̸��� �ʹ� �� ���� ����ؼ� ����մϴ�.
// ������ namespace pollution�� ����ؼ� using namespace�� ������� �ʽ��ϴ�.
// typedef�� using���� ���� �����մϴ�.
typedef std::chrono::steady_clock::time_point TimePoint;

// using���� ������ ����
// using TimePoint = std::chrono::steady_clock::time_point;

#endif