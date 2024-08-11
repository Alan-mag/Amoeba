#pragma once

#include "Core.h"

#include "Window.h"
#include "Amoeba/LayerStack.h"
#include "Amoeba/Events/Event.h"
#include "Amoeba/Events/ApplicationEvent.h"

#include "Amoeba/ImGui/ImGuiLayer.h"
//#include "Amoeba/Renderer/Shader.h"
//#include "Renderer/Buffer.h"
//#include "Renderer/VertexArray.h"
//#include "Renderer/OrthographicCamera.h"//

namespace Amoeba {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		/*std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		OrthographicCamera m_Camera;*/
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}

