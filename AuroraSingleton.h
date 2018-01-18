#pragma once
#include "AuroraDefine.h"

namespace Aurora
{
	// Mayer's Singleton
	// thread-safe in version C++11 and above.
	template <typename T>
	class Singleton
	{		
	protected:
		Singleton(){ }
		virtual ~Singleton( void )
		{

		}
	public:
		static T* Instance( void )
		{
			static T instance;
			return &instance;
		};
	
		Singleton( const Singleton& ) = delete;				// copy construct
		Singleton( Singleton&& ) = delete;					// assign construct

		Singleton& operator=( const Singleton& ) = delete;	// copy assign
		Singleton& operator=( Singleton && ) = delete;		// move assign
	};
}