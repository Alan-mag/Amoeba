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

#ifdef AMOEBA_ENABLE_ASSERTS
	#define AMOEBA_ASSERT(x, ...) { if(!(x)) { AMOEBA_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define AMOEBA_CORE_ASSERT(x, ...) { if(!(x)) { AMOEBA_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define AMOEBA_ASSERT(x, ...)
	#define AMOEBA_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)