/*
 * <�ۼ� ��¥>
 * 2017-10-12
 *
 * <���� ����>
 * ������� �Է��� �����մϴ�.
 * ������� �Է¿��� Ű����, ���콺�� �ֽ��ϴ�.
 * �ϴ��� Ű���� �Է¸� ó���մϴ�.
 */

#ifndef EASIEST_USER_INPUT_MANAGER_H_
#define EASIEST_USER_INPUT_MANAGER_H_

#include "../include/common/cmn_header.h"
#include "../include/common/cmn_type.h"

// Ű �Է°��� ��Ʈ �÷��׸� �̿��ϴ� ��찡 �����ϴ�.
// ��Ʈ �÷��׸� �̿��ϸ� ���� Ű �Է��� ó���� �� �ֱ� �����Դϴ�.
// 32��Ʈ �÷��׸� �̿��ϸ� Ű �Է°��� 32�� ������ �� �ֽ��ϴ�.
const INT32 KEY_W = 0X00000001; // 0000 0000 0000 0000 0000 0000 0000 0001
const INT32 KEY_A = 0X00000002; // 0000 0000 0000 0000 0000 0000 0000 0010
const INT32 KEY_S = 0X00000004; // 0000 0000 0000 0000 0000 0000 0000 0100
const INT32 KEY_D = 0X00000008; // 0000 0000 0000 0000 0000 0000 0000 1000
const INT32 KEY_Q = 0X00000010; // 0000 0000 0000 0000 0000 0000 0001 0000
const INT32 KEY_T = 0X00000020; // 0000 0000 0000 0000 0000 0000 0010 0000
const INT32 KEY_Y = 0X00000040; // 0000 0000 0000 0000 0000 0000 0100 0000

namespace manager
{

	class UserInputManager
	{
	public:
		static UserInputManager& ActivateManager();

		void InitializeInput();
		void InputKeyboard();
		void InputMouse();

		BOOL IsInputKey(INT32 inputKey);

	private:
		UserInputManager()  = default;
		~UserInputManager() = default;

		UserInputManager(const UserInputManager& rhs)  = delete;
		UserInputManager(const UserInputManager&& rhs) = delete;

		UserInputManager& operator= (const UserInputManager& rhs)  = delete;
		UserInputManager& operator= (const UserInputManager&& rhs) = delete;

		struct ManagerDeleter;

		INT32 m_userInputKey; // ������ ��� �Է� ������ �����մϴ�.
	};

} // namespace manager end
namespace mgr = manager;

#endif