/*
 * <�ۼ� ��¥>
 * 2017-10-12
 *
 * <���� ����>
 * ������� �Է��� �����մϴ�.
 * ������� �Է¿��� Ű����, ���콺�� �ֽ��ϴ�.
 * �ϴ��� Ű���� �Է¸� ó���մϴ�.
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
		// Ű���带 �Է����� ������ 0�� ��ȯ�ϰ�
		// Ű���带 �Է��ϸ� 0�� �ƴ� ���� ��ȯ�մϴ�.
		if (_kbhit())
		{
			// ������� �Է°��� �빮�ڷ� �����մϴ�.
			// �̷��� �ϸ� case�� �ϳ��� ó���ص� �˴ϴ�.
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