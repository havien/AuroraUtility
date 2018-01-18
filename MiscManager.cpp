#pragma once
#include <Windows.h>
#include "MiscManager.h"

#include "TimeManager.h"
#include "FileManager.h"


#include "StringManager.h"

using namespace Aurora;
	
MiscManager::MiscManager(): 
supportQFC( false )
{
	
}

MiscManager::~MiscManager( void )
{

}

int MiscManager::ConsoleTest()
{
	HANDLE                     hStdOutput, hStdInput;
	DWORD                      dwWriteByte, dwReadByte;
	TCHAR                      szBuf[256];
	CONSOLE_SCREEN_BUFFER_INFO screenBuffer;

	//system( "mode CON: COLS=80" );
	
	SetConsoleTitle( L"MY SERVER" );

	hStdOutput = GetStdHandle( STD_OUTPUT_HANDLE );
	hStdInput = GetStdHandle( STD_INPUT_HANDLE );
	GetConsoleScreenBufferInfo( hStdOutput, &screenBuffer );

	SMALL_RECT rect;
	rect.Top = 1500;
	rect.Bottom = 3000;

	rect.Left = 2000;
	rect.Right = 4000;
	SetConsoleWindowInfo( hStdOutput, TRUE, &rect );

	DWORD prev_mode;
	GetConsoleMode( hStdInput, &prev_mode );
	SetConsoleMode( hStdInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE );

	lstrcpy( szBuf, TEXT( "Hello World" ) );
	WriteConsole( hStdOutput, szBuf, lstrlen( szBuf ), &dwWriteByte, NULL );

	SetConsoleTextAttribute( hStdOutput, FOREGROUND_RED );
	WriteConsole( hStdOutput, szBuf, lstrlen( szBuf ), &dwWriteByte, NULL );

	SetConsoleTextAttribute( hStdOutput, FOREGROUND_RED | FOREGROUND_INTENSITY );
	WriteConsole( hStdOutput, szBuf, lstrlen( szBuf ), &dwWriteByte, NULL );

	SetConsoleTextAttribute( hStdOutput, BACKGROUND_BLUE );
	WriteConsole( hStdOutput, szBuf, lstrlen( szBuf ), &dwWriteByte, NULL );

	SetConsoleTextAttribute( hStdOutput, BACKGROUND_BLUE | BACKGROUND_INTENSITY );
	WriteConsole( hStdOutput, szBuf, lstrlen( szBuf ), &dwWriteByte, NULL );

	SetConsoleTextAttribute( hStdOutput, screenBuffer.wAttributes );
	lstrcpy( szBuf, TEXT( "Enterキーを押すと終了します" ) );
	WriteConsole( hStdOutput, szBuf, lstrlen( szBuf ), &dwWriteByte, NULL );

	ReadConsole( hStdInput, szBuf, sizeof( szBuf ) / sizeof( TCHAR ), &dwReadByte, NULL );
	szBuf;

	while( true )
	{
		WriteConsole( hStdOutput, szBuf, lstrlen( szBuf ), &dwWriteByte, NULL );
		Sleep( 1000 );
	}

	FreeConsole();

	return 0;
}

DWORD MiscManager::GetProcessorCount() const
{
	SYSTEM_INFO SysInfo;
	GetSystemInfo( &SysInfo );
	return SysInfo.dwNumberOfProcessors;
}

UInt16 MiscManager::GetProcessorCountU16() const
{
	return static_cast<UInt16>(GetProcessorCount());
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

Int64 MiscManager::GetQPCTick() const
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
								  const bool minimized, const Int32 exeCount,
								  DWORD time ) const
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
		for( auto counter = 0; counter < exeCount; ++counter )
		{
			Excuted = ShellExecuteEx( &execinfo );
			Sleep( time );
		}

		return Excuted ? true : false;
	}
	else
	{
		return false;
	}
}