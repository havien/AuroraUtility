#pragma once

#include "Includes.h"
#include "AuroraDefine.h"
#include "AuroraSingleton.h"
#include "TimeManager.h"
#include "FileManager.h"

#include "Lock.h"
#include "MiscManager.h"
#include "StringManager.h"

using namespace Aurora;
	
MiscManager::MiscManager( void ) : 
supportQFC( false )
{
	InitializeCriticalSection(&_monitorObject);
}

MiscManager::~MiscManager( void )
{
	DeleteCriticalSection( &_monitorObject );
}

void MiscManager::SetLogFile( WCHAR* pLogFileName )
{
	if( pLogFileName )
	{
		bool openResult = AuroraFileManager->Open( pLogFileName );
		if( true == openResult )
		{
			AuroraStringManager->ClearAndCopy( pLogFileName, logFileName, MAX_NORMAL_STRING_LEN );
		}
	}
}

DWORD MiscManager::GetProcessorCount( void ) const
{
	SYSTEM_INFO SysInfo;
	GetSystemInfo( &SysInfo );
	return SysInfo.dwNumberOfProcessors;
}

UInt16 MiscManager::GetProcessorCountUInt16( void ) const
{
	return static_cast<UInt16>(GetProcessorCount());
}

void MiscManager::PrintDebugTextToOutputWindow( ELogPrintType LogPrintType, WCHAR* szFormat, ... )
{
	if( szFormat )
	{
		static WCHAR currentTime[MAX_DATETIME_STRING_LEN] = { 0 };
		static WCHAR szBuff[MAX_SUPER_STRING_LEN] = { 0 };
		static va_list args;

		static const size_t tempWCHARLen = (MAX_SUPER_STRING_LEN + MAX_DATETIME_STRING_LEN) + 1;
		static WCHAR tempWCHAR[tempWCHARLen] = { 0 };

		CAutoLockWindows AutoLocker( &_monitorObject );
		{
			AuroraTimeManager->GetCurrentTimeString( currentTime );
			
			memset( tempWCHAR, 0, tempWCHARLen );
			wsprintf( tempWCHAR, L"[%s] %s", currentTime, szFormat );

			va_start( args, szFormat );
			_vsnwprintf_s( reinterpret_cast<WCHAR*>(szBuff), MAX_SUPER_STRING_LEN, MAX_SUPER_STRING_LEN, tempWCHAR, args );
			va_end( args );

			wprintf_s( reinterpret_cast<WCHAR*>(&szBuff), MAX_SUPER_STRING_LEN );
			OutputDebugString( reinterpret_cast<WCHAR*>(szBuff) );

			if( LogPrintType == ELogPrintType::WriteLog )
			{
				AuroraFileManager->Write( reinterpret_cast<WCHAR*>(szBuff) );
			}
		}
	}
}

const bool MiscManager::SupportQPF( Int64 &QPFTick )
{
	LARGE_INTEGER LargeIntQPC;
	if( TRUE == QueryPerformanceFrequency( &LargeIntQPC ) )
	{
		QPFTick = static_cast<Int64>(LargeIntQPC.QuadPart);
		supportQFC = true;
	}
	else
	{
		supportQFC = false;
	}

	return supportQFC;
}

Int64 MiscManager::GetQPCTick( void ) const
{
	if( true == supportQFC )
	{
		static LARGE_INTEGER LargeInteger;
		QueryPerformanceCounter( &LargeInteger );
		return static_cast<Int64>(LargeInteger.QuadPart);
	}

	return -1;
}

Int64 MiscManager::GetQPCElapsedMicroSecond( const Int64 &QPFTick, const Int64 &StartTick, const Int64 &EndTick )
{
	double TempQPFTick = static_cast<double>((QPFTick / 1000000.0));
	return static_cast<Int64>((EndTick - StartTick) / (TempQPFTick));
}

Int64 MiscManager::GetQPCElapsedSecond( const Int64 &QPFTick, const Int64 &StartTick, const Int64 &EndTick ) const
{
	return ((EndTick - StartTick) / (QPFTick));
}

bool MiscManager::ExecuteProcess( const WCHAR* pProcessName, const WCHAR* pParameters,
									const bool minimized, const UInt32 ExecuteCount,
									DWORD SleepTime ) const
{
	if( pProcessName )
	{
		SHELLEXECUTEINFO execinfo;

		memset( &execinfo, 0, sizeof( execinfo ) );
		execinfo.cbSize = sizeof( execinfo );
		execinfo.lpVerb = L"open";
		execinfo.lpFile = pProcessName;
		execinfo.lpParameters = pParameters;
		execinfo.fMask = SEE_MASK_FLAG_NO_UI | SEE_MASK_NOCLOSEPROCESS | SEE_MASK_UNICODE;
		minimized ? execinfo.nShow = SW_SHOWMINIMIZED : execinfo.nShow = SW_SHOWNORMAL;

		BOOL Excuted = FALSE;
		for( UInt32 counter = 0; counter < ExecuteCount; ++counter )
		{
			Excuted = ShellExecuteEx( &execinfo );
			Sleep( SleepTime );
		}

		return Excuted ? true : false;
	}
	else
	{
		return false;
	}
}