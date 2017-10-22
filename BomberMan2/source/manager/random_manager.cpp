/*
 * <�ۼ� ��¥>
 * 2017-10-15
 *
 * <���� ����>
 * ������ �����ϴ� �Ŵ����Դϴ�.
 * ������ ������ �̿��ϸ� Ȯ���� ������ �� �ֽ��ϴ�.
 */

#include "random_manager.h"

#include "../include/common/cmn_function.h"

namespace manager
{

	RandomManager::RandomManager()
		: m_randomNumberGenerator(static_cast<UINT32>(time(nullptr)))
	{
		
	}

	struct RandomManager::ManagerDeleter
	{
		void operator() (RandomManager* pRandomManager)
		{
			if (pRandomManager != nullptr)
			{
				pRandomManager->~RandomManager();
				cmn::SafeFree(&pRandomManager);
			}
		}
	};

	RandomManager& RandomManager::ActivateManager()
	{
		static std::unique_ptr<RandomManager, ManagerDeleter> pRandomManager = nullptr;

		if (pRandomManager == nullptr)
		{
			std::once_flag flag;
			std::function<void()> allocator = []() { pRandomManager.reset(new RandomManager); };
			std::call_once(flag, allocator);
		}

		return *pRandomManager;
	}

	INT32 RandomManager::GenerateIntRandomNumber(INT32 min, INT32 max)
	{
		std::uniform_int_distribution<INT32> intRandomNumber(min, max);
		return intRandomNumber(m_randomNumberGenerator);
	}

	FLOAT32 RandomManager::GenerateFloatRandomNumber(FLOAT32 min, FLOAT32 max)
	{
		std::uniform_real_distribution<FLOAT32> floatRandomNumber(min, max);
		return floatRandomNumber(m_randomNumberGenerator);
	}

} // namespace manager end