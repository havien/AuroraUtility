#pragma once

#include <utility>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <deque>

#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif

	#include <Windows.h>
	#include <Shellapi.h>
	#include <process.h>
	
	#pragma comment(lib, "user32.lib")
	#pragma comment(lib, "advapi32.lib")

	#define _CRTDBG_MAP_ALLOC_
#endif