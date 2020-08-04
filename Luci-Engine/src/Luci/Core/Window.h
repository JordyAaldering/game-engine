#pragma once

#include "lucipch.h"
#include "Core.h"
#include "Luci/Events/Event.h"

namespace Luci {

	struct WindowProps {
		std::string Title;
		uint32_t Width, Height;

		WindowProps(const std::string& title = "Luci Engine", unsigned int width = 1280, unsigned int height = 720)
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
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
	};

}
