#pragma once

#include "Flag.h"

namespace Aurora
{
	Flag::Flag( void )
	{

	}

	Flag::~Flag( void )
	{

	}

	bool Flag::Check( const Byte f ) const
	{
		return ( (_flags & f) != 0 ); // and
		//return ( (_flags & ( 1 << f ) != 0 ); // and
	}

	void Flag::Set( const Byte f )
	{
		_flags |= f; // or
		//_flags |= ( 1 << f ); // or
	}

	void Flag::Reset( const Byte f )
	{
		_flags &= ~f; // not -> and
		//_flags &= ( 1 << ~f ); // not -> and
	}
}