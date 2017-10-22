/*
 * <작성 날짜>
 * 2017-10-11
 *
 * <파일 설명>
 * 파일 입출력을 관리합니다.
 * 현재는 파일 스트림 생성과 닫기만 존재합니다.
 */

#ifndef EASIEST_FILE_MANAGER_H_
#define EASIEST_FILE_MANAGER_H_

#include "../include/common/cmn_header.h"
#include "../include/common/cmn_type.h"

namespace manager
{

	class FileManager
	{
	public:
		static FileManager& ActivateManager();

		FILE* OpenFileStream(const STRING& strFileName, const STRING& strMode);
		void  CloseFileStream(FILE* pFile);
		
	private:
		FileManager()  = default;
		~FileManager() = default;

		FileManager(const FileManager& rhs)  = delete;
		FileManager(const FileManager&& rhs) = delete;

		FileManager& operator= (const FileManager& rhs)  = delete;
		FileManager& operator= (const FileManager&& rhs) = delete;

		struct ManagerDeleter;
	};

} // namespace manager end
namespace mgr = manager;

#endif;