#pragma once
#include "Includes.h"
#include "AuroraDefine.h"

namespace Aurora
{
	class PerformanceCounter
	{
	public:
		PerformanceCounter( /*__out Int64 &QPFTicks*/ );
		~PerformanceCounter();
	private:
		bool SupportQPC( void );
	};
}