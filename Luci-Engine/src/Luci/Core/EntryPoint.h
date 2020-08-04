#pragma once

#ifdef LUCI_PLATFORM_WINDOWS
	extern Luci::Application* Luci::CreateApplication();

	int main(int argc, char** argv) {
		Luci::Log::Init();

		LUCI_PROFILE_BEGIN_SESSION("Startup", "LuciProfileStartup.json");
		auto app = Luci::CreateApplication();
		LUCI_PROFILE_END_SESSION();

		LUCI_PROFILE_BEGIN_SESSION("Startup", "LuciProfileRuntime.json");
		app->Run();
		LUCI_PROFILE_END_SESSION();

		LUCI_PROFILE_BEGIN_SESSION("Startup", "LuciProfileShutdown.json");
		delete app;
		LUCI_PROFILE_END_SESSION();

		return 0;
	}
#endif
