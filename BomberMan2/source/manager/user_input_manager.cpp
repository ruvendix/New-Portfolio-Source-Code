/*
 * <작성 날짜>
 * 2017-10-12
 *
 * <파일 설명>
 * 사용자의 입력을 관리합니다.
 * 사용자의 입력에는 키보드, 마우스가 있습니다.
 * 일단은 키보드 입력만 처리합니다.
 */

#include "user_input_manager.h"

#include "../include/common/cmn_function.h"

static const INT32 NO_INPUT_KEY = 0;

namespace manager
{

	struct UserInputManager::ManagerDeleter
	{
		void operator() (UserInputManager* pUserInputManager)
		{
			if (pUserInputManager != nullptr)
			{
				pUserInputManager->~UserInputManager();
				cmn::SafeFree(&pUserInputManager);
			}
		}
	};

	UserInputManager& UserInputManager::ActivateManager()
	{
		static std::unique_ptr<UserInputManager, ManagerDeleter> pUserInputManager = nullptr;

		if (pUserInputManager == nullptr)
		{
			std::once_flag flag;
			std::function<void()> allocator = []() { pUserInputManager.reset(new UserInputManager); };
			std::call_once(flag, allocator);
		}

		return *pUserInputManager;
	}

	void UserInputManager::InitializeInput()
	{
		m_userInputKey = 0;
	}

	void UserInputManager::InputKeyboard()
	{
		// _kbhit()
		// 키보드를 입력하지 않으면 0을 반환하고
		// 키보드를 입력하면 0이 아닌 값을 반환합니다.
		if (_kbhit())
		{
			// 사용자의 입력값을 대문자로 변경합니다.
			// 이렇게 하면 case를 하나만 처리해도 됩니다.
			ASCII userInputKey = toupper(_getch());

			switch (userInputKey)
			{
			case 'W':
				m_userInputKey |= KEY_W;
				break;
			case 'A':
				m_userInputKey |= KEY_A;
				break;
			case 'S':
				m_userInputKey |= KEY_S;
				break;
			case 'D':
				m_userInputKey |= KEY_D;
				break;
			case 'Q':
				m_userInputKey |= KEY_Q;
				break;
			case 'T':
				m_userInputKey |= KEY_T;
				break;
			case 'Y':
				m_userInputKey |= KEY_Y;
				break;
			}
		}
	}

	void UserInputManager::InputMouse()
	{

	}

	BOOL UserInputManager::IsInputKey(INT32 inputKey)
	{
		if (m_userInputKey & inputKey)
		{
			return true;
		}

		return false;
	}

} // namespace manager end