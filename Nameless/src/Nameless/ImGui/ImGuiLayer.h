#pragma once

#include "Nameless/Core/Layer.h"
#include "Nameless/Events/ApplicationEvent.h"
#include "Nameless/Events/MouseEvent.h"
#include "Nameless/Events/KeyEvent.h"

namespace Nameless
{
	class  ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}