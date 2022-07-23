#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Amoeba {

	class AMOEBA_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define AMOEBA_CORE_TRACE(...)    ::Amoeba::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AMOEBA_CORE_INFO(...)     ::Amoeba::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AMOEBA_CORE_WARN(...)     ::Amoeba::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AMOEBA_CORE_ERROR(...)    ::Amoeba::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AMOEBA_CORE_FATAL(...)    ::Amoeba::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define AMOEBA_TRACE(...)		  ::Amoeba::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AMOEBA_INFO(...)		  ::Amoeba::Log::GetClientLogger()->info(__VA_ARGS__)
#define AMOEBA_WARN(...)		  ::Amoeba::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AMOEBA_ERROR(...)		  ::Amoeba::Log::GetClientLogger()->error(__VA_ARGS__)
#define AMOEBA_FATAL(...)		  ::Amoeba::Log::GetClientLogger()->fatal(__VA_ARGS__)