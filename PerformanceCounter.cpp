#pragma once
#include "PerformanceCounter.h"

using namespace Aurora;

PerformanceCounter::PerformanceCounter( /*__out Int64 &QPFTicks*/ )
{
	// support QPC?
	/*LARGE_INTEGER largeInt;

	if(TRUE == QueryPerformanceFrequency( &largeInt ) )
	{
		QPFTicks = static_cast<Int64>(largeInt.QuadPart);
	}*/

	LARGE_INTEGER LargeIntForPFC;
	QueryPerformanceCounter( &LargeIntForPFC );
}


PerformanceCounter::~PerformanceCounter()
{
}

bool PerformanceCounter::SupportQPC( void )
{
	LARGE_INTEGER largeInt;

	if( TRUE == QueryPerformanceFrequency( &largeInt ) )
	{
		return true;
	}

	return false;
}