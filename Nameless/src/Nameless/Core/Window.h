#pragma once

#include "nmlspch.h"

#include "Nameless/Core/Core.h"
#include "Nameless/Events/Event.h"
#include "Nameless/Core/Log.h"

namespace Nameless
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Nameless Engine",
					unsigned int width = 1600, 
					unsigned int height = 900)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class  Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}