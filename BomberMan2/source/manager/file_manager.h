/*
 * <�ۼ� ��¥>
 * 2017-10-11
 *
 * <���� ����>
 * ���� ������� �����մϴ�.
 * ����� ���� ��Ʈ�� ������ �ݱ⸸ �����մϴ�.
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