#pragma once

#include "Nameless/Core/Core.h"
#include "Nameless/Events/Event.h"
#include "Timestep.h"

namespace Nameless
{
	class  Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate(Timestep timestep);
		virtual void OnImGuiRender();
		virtual void OnEvent(Event& event);

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}