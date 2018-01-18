#pragma once

#include "Includes.h"
#include "AuroraDefine.h"
#include "AuroraSingleton.h"

namespace Aurora
{
	class LogManager : public Singleton<LogManager>
	{
	public:
		explicit LogManager();
		virtual ~LogManager();

		void SetLogFile( WCHAR* pLogFileName );
		void PrintToDebugWindow( const WCHAR* const pText ) noexcept;

		void Trace( const WCHAR* const pFormat, ... );
		void Error( const WCHAR* const pFormat, ... );
		void Warning( const WCHAR* const pFormat, ... );
		void Critical( const WCHAR* const pFormat, ... );
	private:
		WCHAR _logFileName[DEFAULT_NORMAL_STR_LEN];
		CRITICAL_SECTION _monitor;

		WCHAR _tempBuffer[DEFAULT_BIGGER_STR_LEN];
		WCHAR _buffer[DEFAULT_BIGGEST_STR_LEN];
	};
}

#define AuroraLogManager Aurora::LogManager::Instance()