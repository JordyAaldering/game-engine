#include "Luci.h"
#include "Luci/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Luci {

	class EditorApp : public Application {
	public:
		EditorApp() : Application("Luci Editor") {
			PushLayer(new EditorLayer());
		}

		~EditorApp() = default;
	};

	Application* CreateApplication() {
		return new EditorApp();
	}

}
