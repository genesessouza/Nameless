#pragma once

#include "Nameless/Layer.h"
#include "Nameless/Events/ApplicationEvent.h"
#include "Nameless/Events/MouseEvent.h"
#include "Nameless/Events/KeyEvent.h"

namespace Nameless
{
	class NAMELESS_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	private:
		float m_Time = 0.0f;
	};
}