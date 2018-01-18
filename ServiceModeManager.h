#pragma once
#include "AuroraSingleton.h"

namespace Aurora
{
	class WindowsServiceManager : public Singleton<WindowsServiceManager>
	{
		friend class Singleton<WindowsServiceManager>;
	private:
		WindowsServiceManager();
	public:
		virtual ~WindowsServiceManager();

		void Install();
		void Delete();
		void UpdateDesc();
	};
}