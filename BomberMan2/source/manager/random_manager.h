/*
 * <작성 날짜>
 * 2017-10-15
 *
 * <파일 설명>
 * 난수를 생성하는 매니저입니다.
 * 생성된 난수를 이용하면 확률을 조정할 수 있습니다.
 */

#ifndef EASIEST_RANDOM_MANAGER_H_
#define EASIEST_RANDOM_MANAGER_H_

#include <random>
#include <ctime> // 시드값을 주기 위해 이용, 시간 관리는 chrono를 이용합니다.

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