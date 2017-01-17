#pragma once
#include "TimeManager.h"

using namespace Aurora;

void TimeManager::ProcessLocalTimeWindows( void )
{
	SYSTEMTIME st, lt;
	GetLocalTime( &st );
	GetLocalTime( &lt );

	printf( "START TIME [%d-%d-%d %02d:%02d:%02d] / [%d-%d-%d %02d:%02d:%02d] SEND QUERY SUCCESS!\n",
			st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond,
			lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond );
}

void TimeManager::ProcessLocalTime( void )
{
	_currentTime = time( nullptr );
	localtime_s( &_nowTime, &_currentTime );;
}

void TimeManager::GetCurrentDateString( WCHAR* const pCurrentTime )
{
	if( pCurrentTime )
	{
		ProcessLocalTime();

		_snwprintf_s( pCurrentTime,
					  MAX_DATETIME_STRING_LEN,
					  MAX_DATETIME_STRING_LEN - 1,
					  L"%d-%d-%d",
					  _nowTime.tm_year + 1900,
					  _nowTime.tm_mon + 1,
					  _nowTime.tm_mday );
	}
}

void TimeManager::GetCurrentTimeString( WCHAR* const pCurrentTime )
{
	if( pCurrentTime )
	{
		ProcessLocalTime();

		_snwprintf_s( pCurrentTime,
					  MAX_DATETIME_STRING_LEN,
					  MAX_DATETIME_STRING_LEN - 1,
					  L"%d-%d-%d-%02d:%02d:%02d",
					  _nowTime.tm_year + 1900,
					  _nowTime.tm_mon + 1,
					  _nowTime.tm_mday,
					  _nowTime.tm_hour,
					  _nowTime.tm_min,
					  _nowTime.tm_sec );
	}
}