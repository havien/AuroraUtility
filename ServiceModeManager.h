#pragma once
#include "AuroraSingleton.h"

namespace Aurora
{
	class WindowsServiceManager : public Singleton<WindowsServiceManager>
	{
		friend class Singleton<WindowsServiceManager>;
	private:
		WindowsServiceManager( void );
	public:
		virtual ~WindowsServiceManager( void );

		void Install( void );
		void Delete( void );
		void UpdateDesc( void );
	};
}