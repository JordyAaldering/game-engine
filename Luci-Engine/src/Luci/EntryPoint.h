#pragma once

#ifdef LUCI_PLATFORM_WINDOWS
extern Luci::Application* Luci::CreateApplication();

int main(int argc, char** argv) {
	Luci::Log::Init();
	LUCI_CORE_WARN("Initialized log.");
	LUCI_INFO("Initialized log. Var={0}.", 5);

	auto app = Luci::CreateApplication();
	app->Run();
	delete app;

	return 0;
}
#endif // LUCI_PLATFORM_WINDOWS
