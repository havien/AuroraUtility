#pragma once

#include "Includes.h"
#include "AuroraDefine.h"

namespace Aurora
{
	namespace Collections
	{
		const Byte DEFAULT_RESERVE_SIZE = 64;

		template <typename T>
		class Vector : public std::vector<T>
		{
			Vector( void ) { }
			virtual ~Vector( void ) { }
		};
	}
}