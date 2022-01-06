#pragma once

#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Grapher
{
	class Log
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


// Core Log macros

#define GP_CORE_TRACE(...)    ::Grapher::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GP_CORE_INFO(...)     ::Grapher::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GP_CORE_WARN(...)     ::Grapher::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GP_CORE_ERROR(...)    ::Grapher::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GP_CORE_FATAL(...)    ::Grapher::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log macros

#define GP_TRACE(...)         ::Grapher::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GP_INFO(...)          ::Grapher::Log::GetClientLogger()->info(__VA_ARGS__)
#define GP_WARN(...)          ::Grapher::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GP_ERROR(...)         ::Grapher::Log::GetClientLogger()->error(__VA_ARGS__)
#define GP_FATAL(...)         ::Grapher::Log::GetClientLogger()->fatal(__VA_ARGS__)