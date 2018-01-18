#pragma once
#include "AuroraSingleton.h"

namespace Aurora
{
	enum class EOperatingSystem
	{ 
		None = 0, Linux, Windows, MacOS, iOS, Android, Max
	};

	class CGlobalCommonManager : public Singleton<CGlobalCommonManager>
	{
		friend class Singleton<CGlobalCommonManager>;
	private:
		CGlobalCommonManager():
		m_OperatingSystem( GetOperatingSystem() )
		{

		}
		CGlobalCommonManager( const CGlobalCommonManager& CopyArg );
		const EOperatingSystem m_OperatingSystem;
	public:
		virtual ~CGlobalCommonManager(){}

		inline const EOperatingSystem GetOperatingSystem( void )
		{
#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
			return EOperatingSystem::Windows;
#elif defined(__APPLE__) || defined(__MAC_NA)
			return EOperatingSystem::MacOS;
#elif defined(__IPHONE_NA)
			return EOperatingSystem::iOS;
#elif defined(__linux__)
			return EOperatingSystem::Linux;
#else
			return EOperatingSystem::None;
#endif
		}
	};

}