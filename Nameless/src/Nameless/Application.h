#pragma once

#include "Core.h"

#include "Window.h"
#include "Nameless/LayerStack.h"
#include "Nameless/Events/Event.h"
#include "Nameless/Events/ApplicationEvent.h"

#include "Nameless/ImGui/ImGuiLayer.h"

namespace Nameless
{
	class  Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}