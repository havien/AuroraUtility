#pragma once

#include "Includes.h"
#include <time.h>

#include "AuroraDefine.h"
#include "AuroraSingleton.h"

namespace Aurora
{
	const Int32 SECOND = 1000;
	const Int32 MINUTE = SECOND * 60;
	const Int32 HOUR = MINUTE * 60;

	class TimeManager : public Singleton<TimeManager>
	{
		friend class Singleton<TimeManager>;

		TimeManager( void ) : _currentTime( time( nullptr ) )
		{
		}
	public:
		virtual ~TimeManager( void )
		{

		}

		void ProcessLocalTime( void );
		void ProcessLocalTimeWindows( void );

		void GetCurrentDateString( WCHAR* const pCurrentTime );
		void GetCurrentTimeString( WCHAR* const pCurrentTime );
	private:
		time_t _currentTime;
		struct tm _nowTime;
	};

#define AuroraTimeManager TimeManager::Instance()
}