#pragma once
#include "ElapsedTimeCalculator.h"
#include "TimeManager.h"

namespace Aurora
{
	ARElapsedTimeCal::ARElapsedTimeCal():
	_start( std::chrono::system_clock::now() )
	{

	}

	ARElapsedTimeCal::~ARElapsedTimeCal( void )
	{

	}

	auto ARElapsedTimeCal::GetElapsedMill() noexcept
	{
		//std::chrono::duration_cast
			//<std::chrono::milliseconds>(AuroraTimeManager->GetNow() - _start).count();
	}

	/*std::chrono::system_clock::time_point GetElapsedSec( void )
	{

	}*/
};