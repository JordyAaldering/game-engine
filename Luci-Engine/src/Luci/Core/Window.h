#pragma once

#include "Luci/Core/Core.h"
#include "Luci/Events/Event.h"

#include <sstream>

namespace Luci {

	struct WindowProps {
		std::string Title;
		uint32_t Width, Height;

		WindowProps(const std::string& title = "Luci Engine",
					uint32_t width = 1600, uint32_t height = 900)
			: Title(title), Width(width), Height(height) {}
	};

	/// <summary>
	/// Interface representing a desktop system based window.
	/// </summary>
	class Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual void* GetNativeWindow() const = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
	};

}
