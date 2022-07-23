#pragma once

#ifdef AMOEBA_PLATFORM_WINDOWS
	#ifdef AMOEBA_BUILD_DLL
		#define AMOEBA_API __declspec(dllexport)
	#else
		#define AMOEBA_API __declspec(dllimport)
	#endif
#else
	#error Amoeba only supports windows
#endif