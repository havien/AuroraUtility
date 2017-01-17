#pragma once
#include "Includes.h"
#include "AuroraDefine.h"
#include "AuroraSingleton.h"

namespace Aurora
{
	enum class EFileOpenMode : Byte
	{
		ReadOnly = 0,
		ReadWrite,
	};

	enum class ELogType : Byte
	{
		Info = 0,
		Trace,
		Warning,
		Critical,
		Size
	};

	class FileManager : public Singleton<FileManager>
	{
		friend class Singleton<FileManager>;
	private:
		FileManager( void );
		NON_COPYABLE( FileManager );
	public:
		virtual ~FileManager( void );

		bool OpenFile( const WCHAR* pFileName, const EFileOpenMode OpenMode = EFileOpenMode::ReadWrite );
		bool WriteFile( const WCHAR* pWrite );
		void CloseFile( void );
	private:
		FILE *_pWorkFile;
		errno_t _lastErrno;
	};

	#define AuroraFileManager FileManager::Instance()
}