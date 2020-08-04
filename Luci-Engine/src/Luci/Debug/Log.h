#pragma once

#include "Luci/Core/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Luci {

	class Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// core log macros
#define LUCI_CORE_TRACE(...) ::Luci::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LUCI_CORE_INFO(...)  ::Luci::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LUCI_CORE_WARN(...)  ::Luci::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LUCI_CORE_ERROR(...) ::Luci::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LUCI_CORE_FATAL(...) ::Luci::Log::GetCoreLogger()->critical(__VA_ARGS__)

// client log macros
#define LUCI_TRACE(...)      ::Luci::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LUCI_INFO(...)       ::Luci::Log::GetClientLogger()->info(__VA_ARGS__)
#define LUCI_WARN(...)       ::Luci::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LUCI_ERROR(...)      ::Luci::Log::GetClientLogger()->error(__VA_ARGS__)
#define LUCI_FATAL(...)      ::Luci::Log::GetClientLogger()->critical(__VA_ARGS__)
