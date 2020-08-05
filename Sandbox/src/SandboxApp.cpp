#include <Luci.h>
#include <Luci/Core/EntryPoint.h>

#include "ExampleLayer.h"
#include "Sandbox2D.h"

class Sandbox : public Luci::Application {
public:
	Sandbox() { 
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() = default;
};

Luci::Application* Luci::CreateApplication() {
	return new Sandbox();
}
