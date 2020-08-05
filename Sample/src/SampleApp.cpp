#include <Luci.h>
#include <Luci/Core/EntryPoint.h>

#include "GameLayer.h"

class Game : public Luci::Application {
public:
	Game() {
		PushLayer(new GameLayer());
	}

	~Game() = default;
};

Luci::Application* Luci::CreateApplication() {
	return new Game();
}
