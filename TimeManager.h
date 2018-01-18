#pragma once

#include "Includes.h"
#include <time.h>
#include <chrono>

#include "AuroraDefine.h"
#include "AuroraSingleton.h"

using namespace std;

namespace Aurora
{
	constexpr Int32 SECOND = 1000;
	constexpr Int32 MINUTE = SECOND * 60;
	constexpr Int32 HOUR = MINUTE * 60;
	
	class TimeManager : public Singleton<TimeManager>
	{
		friend class Singleton<TimeManager>;
	private:
		TimeManager();
	public:
		virtual ~TimeManager();

		void InitRand( void ) noexcept;

		//chrono::milliseconds GetNowMill() noexcept;
		Int64 GetNowTimestamp() noexcept;
		const WCHAR* GetNowString( const WCHAR* pFormat = nullptr ) noexcept;

		void ProcessLocalTime();
		void ProcessLocalTimeWindows();

		void GetCurrentDateString( WCHAR* const pCurrentTime );
		void GetCurrentTimeString( WCHAR* const pCurrentTime );
	private:
		time_t _currentTime;
		struct tm _nowTime;
		WCHAR _nowTimeSTR[MAX_TIME_STRING_LEN];
		
	};
}

#define AuroraTimeManager Aurora::TimeManager::Instance()