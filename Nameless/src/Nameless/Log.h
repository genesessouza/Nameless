#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Nameless {
	class  Log
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

#define NMLS_CORE_FATAL(...) ::Nameless::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define NMLS_CORE_ERROR(...) ::Nameless::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NMLS_CORE_WARN(...) ::Nameless::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NMLS_CORE_TRACE(...) ::Nameless::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NMLS_CORE_INFO(...) ::Nameless::Log::GetCoreLogger()->info(__VA_ARGS__)

#define NMLS_FATAL(...) ::Nameless::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define NMLS_ERROR(...) ::Nameless::Log::GetClientLogger()->error(__VA_ARGS__)
#define NMLS_WARN(...) ::Nameless::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NMLS_TRACE(...) ::Nameless::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NMLS_INFO(...) ::Nameless::Log::GetClientLogger()->info(__VA_ARGS__)