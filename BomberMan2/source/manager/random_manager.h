/*
 * <�ۼ� ��¥>
 * 2017-10-15
 *
 * <���� ����>
 * ������ �����ϴ� �Ŵ����Դϴ�.
 * ������ ������ �̿��ϸ� Ȯ���� ������ �� �ֽ��ϴ�.
 */

#ifndef EASIEST_RANDOM_MANAGER_H_
#define EASIEST_RANDOM_MANAGER_H_

#include <random>
#include <ctime> // �õ尪�� �ֱ� ���� �̿�, �ð� ������ chrono�� �̿��մϴ�.

#include "../include/common/cmn_type.h"

namespace manager
{

	class RandomManager
	{
	public:
		static RandomManager& ActivateManager();

		INT32   GenerateIntRandomNumber(INT32 min, INT32 max);
		FLOAT32 GenerateFloatRandomNumber(FLOAT32 min, FLOAT32 max);

	private:
		RandomManager();
		~RandomManager() = default;

		RandomManager(const RandomManager& rhs)  = delete;
		RandomManager(const RandomManager&& rhs) = delete;

		RandomManager& operator= (const RandomManager& rhs)  = delete;
		RandomManager& operator= (const RandomManager&& rhs) = delete;
		
		struct ManagerDeleter;

		std::default_random_engine m_randomNumberGenerator;
	};

} // namespace manager end
namespace mgr = manager;

#endif