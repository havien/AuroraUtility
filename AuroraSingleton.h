#pragma once
#include "AuroraDefine.h"

namespace Aurora
{
	// non thread-safe.
	template <typename T>
	class Singleton
	{		
	protected:
		Singleton( void ) { }
	public:
		virtual ~Singleton( void )
		{
		}

		static T* Instance( void )
		{
			static T instance;
			return &instance;
		};
	private:
		NON_COPYABLE( Singleton );
		/*Singleton( const Singleton& CopyArg );
		const Singleton& operator=( const Singleton& );*/
	};
}