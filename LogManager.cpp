#pragma once
#include "FileManager.h"
#include "StringManager.h"
#include "TimeManager.h"
#include "WindowsConsoleManager.h"

#include "LogManager.h"


namespace Aurora
{
	LogManager::LogManager( void )
	{
		AuroraStringManager->Clear( _buffer, DEFAULT_BIG_STR_LEN );
	}

	LogManager::~LogManager( void )
	{
	}

	void LogManager::SetLogFile( WCHAR* pLogFileName )
	{
		if( pLogFileName )
		{
			if( true == AuroraFileManager->Open( pLogFileName ) )
			{
				AuroraStringManager->ClearAndCopy( pLogFileName, _logFileName, DEFAULT_NORMAL_STR_LEN );
			}
		}
	}

	void LogManager::PrintToDebugWindow( const WCHAR* const pText ) noexcept
	{
		if( pText )
		{
			OutputDebugStringW( pText );
			OutputDebugStringW( L"\n" );
		}
	}

	void LogManager::Trace( const WCHAR* const pFormat, ... )
	{
		va_list args;
		
		va_start( args, pFormat );
		wsprintfW( _tempBuffer, L"[%s] %s", AuroraTimeManager->GetNowString(), pFormat );
		_vsnwprintf_s( _buffer, _TRUNCATE, DEFAULT_BIGGEST_STR_LEN, _tempBuffer, args );
		va_end( args );

		AuroraConsoleManager->WriteWhiteLN( _buffer );
		PrintToDebugWindow( _buffer );
	}

	void LogManager::Error( const WCHAR* const pFormat, ... )
	{
		va_list args;
		va_start( args, pFormat );
		wsprintfW( _tempBuffer, L"[%s] %s", AuroraTimeManager->GetNowString(), pFormat );
		_vsnwprintf_s( _buffer, _TRUNCATE, DEFAULT_BIGGEST_STR_LEN, _tempBuffer, args );
		va_end( args );

		AuroraConsoleManager->WriteRedLN( _buffer );
		PrintToDebugWindow( _buffer );
	}

	void LogManager::Warning( const WCHAR* const pFormat, ... )
	{
		va_list args;
		va_start( args, pFormat );
		wsprintfW( _tempBuffer, L"[%s] %s", AuroraTimeManager->GetNowString(), pFormat );
		_vsnwprintf_s( _buffer, _TRUNCATE, DEFAULT_BIGGEST_STR_LEN, _tempBuffer, args );
		va_end( args );

		AuroraConsoleManager->WriteBlueLN( _buffer );
		PrintToDebugWindow( _buffer );

	}

	void LogManager::Critical( const WCHAR* const pFormat, ... )
	{
		va_list args;
		va_start( args, pFormat );
		wsprintfW( _tempBuffer, L"[%s] %s", AuroraTimeManager->GetNowString(), pFormat );
		_vsnwprintf_s( _buffer, _TRUNCATE, DEFAULT_BIGGEST_STR_LEN, _tempBuffer, args );
		va_end( args );

		AuroraConsoleManager->WriteYellowLN( _buffer );
		PrintToDebugWindow( _buffer );
	}
}