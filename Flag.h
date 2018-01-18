#pragma once
#include "AuroraDefine.h"

namespace Aurora
{
	class Flag
	{
	public:
		Flag();
		~Flag();

		bool Check( const Byte f ) const;
		void Set( const Byte f );
		void Reset( const Byte f );

	private:
		Byte _flags;
	};
}