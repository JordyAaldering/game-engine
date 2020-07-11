#include <Luci.h>

class ExampleLayer : public Luci::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		LUCI_INFO("ExampleLayer::OnUpdate");
	}

	void OnEvent(Luci::Event& e) override {
		LUCI_TRACE("{0}", e);
	}
};

class Sandbox : public Luci::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}
};

Luci::Application* Luci::CreateApplication() {
	return new Sandbox();
}
