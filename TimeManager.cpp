#pragma once
#include "TimeManager.h"
#include <ctime>
#include <locale>

using namespace Aurora;

TimeManager::TimeManager(): 
_currentTime( time( nullptr ) )
{

}

TimeManager::~TimeManager( void )
{

}

/*
chrono::milliseconds TimeManager::GetNowMill() noexcept
{
	return chrono::system_clock::now().time_since_epoch();
}*/

void TimeManager::InitRand( void ) noexcept
{
	std::srand( static_cast<UInt32>(std::time( 0 )) );
}

Int64 TimeManager::GetNowTimestamp() noexcept
{
	return chrono::seconds( std::time( 0 ) ).count();
}

const WCHAR* TimeManager::GetNowString( const WCHAR* pFormat ) noexcept
{
	auto now = chrono::system_clock::now();
	auto time_t = chrono::system_clock::to_time_t( now );
	localtime_s( &_nowTime, &time_t );
	
	size_t size = 0;
	if( nullptr == pFormat )
	{
		size = std::wcsftime( _nowTimeSTR, (MAX_TIME_STRING_LEN-1), L"%Y/%m/%d %H:%M:%S", &_nowTime );
	}
	else
	{
		size = std::wcsftime( _nowTimeSTR, (MAX_TIME_STRING_LEN-1), pFormat, &_nowTime );
	}

	if( 0 == size )
	{
		// error
	}

	return _nowTimeSTR;
}

void TimeManager::ProcessLocalTimeWindows( void )
{
	SYSTEMTIME st, lt;
	GetLocalTime( &st );
	GetLocalTime( &lt );

	printf( "START TIME [%d-%d-%d %02d:%02d:%02d] / [%d-%d-%d %02d:%02d:%02d] SEND QUERY SUCCESS!",
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