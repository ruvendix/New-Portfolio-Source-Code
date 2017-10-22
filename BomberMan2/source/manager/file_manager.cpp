/*
 * <작성 날짜>
 * 2017-10-11
 *
 * <파일 설명>
 * 파일 입출력을 관리합니다.
 * 현재는 파일 스트림 생성과 닫기만 존재합니다.
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