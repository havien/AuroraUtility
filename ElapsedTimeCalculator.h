#pragma once

#include "Includes.h"
#include "AuroraDefine.h"
#include "BaseObject.h"
#include <chrono>

namespace Aurora
{
	class ARElapsedTimeCal : public AuroraBase
	{
	public:
		explicit ARElapsedTimeCal();
		virtual ~ARElapsedTimeCal();

		auto GetElapsedMill() noexcept;
		//std::chrono::system_clock::time_point GetElapsedSec() noexcept;

	private:
		ARElapsedTimeCal( const ARElapsedTimeCal& ) = delete;
		ARElapsedTimeCal( ARElapsedTimeCal&& ) = delete;

		ARElapsedTimeCal& operator=( const ARElapsedTimeCal& ) = delete;
		ARElapsedTimeCal& operator=( ARElapsedTimeCal && ) = delete;

		std::chrono::system_clock::time_point _start;
	};
};