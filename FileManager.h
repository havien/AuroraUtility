#pragma once

#include "Includes.h"
#include <filesystem>

#include "AuroraDefine.h"
#include "AuroraSingleton.h"

namespace Aurora
{
	class FileManager : public Singleton<FileManager>
	{
	public:
		explicit FileManager();
		virtual ~FileManager();

		bool IsOpen( const WCHAR* pFileName, const EFileOpenMode mode = EFileOpenMode::Read );
		bool Open( const WCHAR* pFileName, const EFileOpenMode mode = EFileOpenMode::ReadWrite );
		bool Write( const WCHAR* pWrite );
		void Close();

		int Rename( const char* pPath, const char* pOld, const char* pNew ) const;
		void Rename( const WCHAR* pPath, const WCHAR* pOld, const WCHAR* pNew );

		void DetermineExtension( const char* pFileName, OUT char* pExtension ) const;
	private:
		FILE *_pWorkFile;
		errno_t _lastErrno;
	};

	#define AuroraFileManager FileManager::Instance()
}
