#include <Luci.h>

class ExampleLayer : public Luci::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		LUCI_INFO("ExampleLayer::OnUpdate");
	}

	void OnEvent(Luci::Event& event) override {
		// todo: find out why this does crashes the application
		// LUCI_TRACE("{0}", event);
	}
};

class Sandbox : public Luci::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Luci::ImGuiLayer());
	}

	~Sandbox() {}
};

Luci::Application* Luci::CreateApplication() {
	return new Sandbox();
}
