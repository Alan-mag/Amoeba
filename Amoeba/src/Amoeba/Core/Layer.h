#pragma once

#include "Amoeba/Core/Core.h"
#include "Amoeba/Events/Event.h"
#include "Amoeba/Core/Timestep.h"

namespace Amoeba
{

	class AMOEBA_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};

}