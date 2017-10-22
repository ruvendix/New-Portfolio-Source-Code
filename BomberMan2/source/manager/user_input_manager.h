/*
 * <작성 날짜>
 * 2017-10-12
 *
 * <파일 설명>
 * 사용자의 입력을 관리합니다.
 * 사용자의 입력에는 키보드, 마우스가 있습니다.
 * 일단은 키보드 입력만 처리합니다.
 */

#ifndef EASIEST_USER_INPUT_MANAGER_H_
#define EASIEST_USER_INPUT_MANAGER_H_

#include "../include/common/cmn_header.h"
#include "../include/common/cmn_type.h"

// 키 입력값은 비트 플래그를 이용하는 경우가 많습니다.
// 비트 플래그를 이용하면 다중 키 입력을 처리할 수 있기 때문입니다.
// 32비트 플래그를 이용하면 키 입력값을 32개 저장할 수 있습니다.
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

		INT32 m_userInputKey; // 유저의 모든 입력 정보를 저장합니다.
	};

} // namespace manager end
namespace mgr = manager;

#endif