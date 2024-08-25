#pragma once

#include <memory>

#ifdef AMOEBA_PLATFORM_WINDOWS
#if AMOEBA_DYNAMIC_LINK
	#ifdef AMOEBA_BUILD_DLL
		#define AMOEBA_API __declspec(dllexport)
	#else
		#define AMOEBA_API __declspec(dllimport)
	#endif
#else
	#define AMOEBA_API
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

#define AMOEBA_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Amoeba {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}