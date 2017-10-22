/*
 * <�ۼ� ��¥>
 * 2017-10-11
 *
 * <���� ����>
 * ���� ������� �����մϴ�.
 * ����� ���� ��Ʈ�� ������ �ݱ⸸ �����մϴ�.
 */

#include "file_manager.h"

#include "../include/common/cmn_function.h"

const INT32 FILE_STREAM_OPEN_SUCCESS = 0;

namespace manager
{
	
	struct FileManager::ManagerDeleter
	{
		void operator() (FileManager* pFileManager)
		{
			if (pFileManager != nullptr)
			{
				pFileManager->~FileManager();
				cmn::SafeFree(&pFileManager);
			}
		}
	};

	FileManager& FileManager::ActivateManager()
	{
		static std::unique_ptr<FileManager, ManagerDeleter> pFileManager = nullptr;
		
		if (pFileManager == nullptr)
		{
			std::once_flag flag;
			std::function<void()> allocator = []() { pFileManager.reset(new FileManager); };
			std::call_once(flag, allocator);
		}

		return *pFileManager;
	}

	FILE* FileManager::OpenFileStream(const STRING& strFileName, const STRING& strMode)
	{
		FILE* pFile;
		fopen_s(&pFile, strFileName.c_str(), strMode.c_str());

		if (ferror(pFile) != FILE_STREAM_OPEN_SUCCESS)
		{
			perror("File Stream Open Fail!");
			pFile = nullptr;
		}

		return pFile;
	}

	void FileManager::CloseFileStream(FILE* pFile)
	{
		if (pFile != nullptr)
		{
			fclose(pFile);
		}
	}

} // namespace manager end