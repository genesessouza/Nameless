#pragma once

#include "Nameless/Layer.h"
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
		virtual void OnUpdate() override;
		virtual void OmImGuiRender();

	private:
		float m_Time = 0.0f;
	};
}