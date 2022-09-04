#pragma once

#include "Amoeba/Layer.h"

#include "Amoeba/Events/ApplicationEvent.h"
#include <Amoeba/Events/MouseEvent.h>
#include <Amoeba/Events/KeyEvent.h>

namespace Amoeba {
	
	class AMOEBA_API ImGuiLayer : public Layer
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