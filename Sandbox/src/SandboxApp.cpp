#include <Luci.h>

class Sandbox : public Luci::Application {
public:
	Sandbox() {}
	~Sandbox() {}
};

Luci::Application* Luci::CreateApplication() {
	return new Sandbox();
}
