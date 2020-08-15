#pragma once

#include "Luci/Core/Core.h"

namespace Luci {

	class GraphicsContext {
	public:
		static Scope<GraphicsContext> Create(void* window);
		virtual ~GraphicsContext() = default;

		virtual void Initialize() = 0;
		virtual void SwapBuffers() = 0;
	};

}
