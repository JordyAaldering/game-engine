#include <Luci.h>

class ExampleLayer : public Luci::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		if (Luci::Input::IsKeyPressed(LUCI_KEY_TAB)) {
			LUCI_INFO("Tab key pressed.");
		}
	}

	void OnEvent(Luci::Event& event) override {
		if (event.GetEventType() == Luci::EventType::KeyPressed) {
			Luci::KeyPressedEvent& e = (Luci::KeyPressedEvent&)event;
			LUCI_TRACE("{0}", (char)e.GetKeyCode());
		}
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
