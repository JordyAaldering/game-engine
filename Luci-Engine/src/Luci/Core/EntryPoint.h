#pragma once

#include "Luci/Core/Core.h"

#ifdef LUCI_PLATFORM_WINDOWS

	extern Luci::Application* Luci::CreateApplication();

	int main(int argc, char** argv) {
		Luci::Log::Initialize();

		LUCI_PROFILE_BEGIN_SESSION("Startup", "LuciProfileStartup.json");
		auto app = Luci::CreateApplication();
		LUCI_PROFILE_END_SESSION();

		LUCI_PROFILE_BEGIN_SESSION("Runtime", "LuciProfileRuntime.json");
		app->Run();
		LUCI_PROFILE_END_SESSION();

		LUCI_PROFILE_BEGIN_SESSION("Shutdown", "LuciProfileShutdown.json");
		delete app;
		LUCI_PROFILE_END_SESSION();

		return 0;
	}

#endif
