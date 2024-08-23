#include <Amoeba.h>

#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Amoeba::Layer 
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Amoeba::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Amoeba::Ref<Amoeba::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Amoeba::VertexBuffer::Create(vertices, sizeof(vertices)));
		Amoeba::BufferLayout layout = {
			{ Amoeba::ShaderDataType::Float3, "a_Position" },
			{ Amoeba::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Amoeba::Ref<Amoeba::IndexBuffer> indexBuffer;
		indexBuffer.reset(Amoeba::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Amoeba::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Amoeba::Ref<Amoeba::VertexBuffer> squareVB;
		squareVB.reset(Amoeba::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Amoeba::ShaderDataType::Float3, "a_Position" },
			{ Amoeba::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Amoeba::Ref<Amoeba::IndexBuffer> squareIB;
		squareIB.reset(Amoeba::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Amoeba::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(Amoeba::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

		m_TextureShader.reset(Amoeba::Shader::Create("assets/shaders/Texture.glsl"));

		m_Texture = Amoeba::Texture2D::Create("assets/textures/Checkerboard.png");
		m_AmoebaLogoTexture = Amoeba::Texture2D::Create("assets/textures/Amoeba-Icon-256.png");

		std::dynamic_pointer_cast<Amoeba::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Amoeba::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Amoeba::Timestep ts) override
	{
		if (Amoeba::Input::IsKeyPressed(AMOEBA_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Amoeba::Input::IsKeyPressed(AMOEBA_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Amoeba::Input::IsKeyPressed(AMOEBA_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Amoeba::Input::IsKeyPressed(AMOEBA_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Amoeba::Input::IsKeyPressed(AMOEBA_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Amoeba::Input::IsKeyPressed(AMOEBA_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Amoeba::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Amoeba::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Amoeba::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Amoeba::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Amoeba::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Amoeba::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Amoeba::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_AmoebaLogoTexture->Bind();
		Amoeba::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		// Amoeba::Renderer::Submit(m_Shader, m_VertexArray);

		Amoeba::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Amoeba::Event& event) override
	{
	}
private:
	Amoeba::Ref<Amoeba::Shader> m_Shader;
	Amoeba::Ref<Amoeba::VertexArray> m_VertexArray;

	Amoeba::Ref<Amoeba::Shader> m_FlatColorShader, m_TextureShader;
	Amoeba::Ref<Amoeba::VertexArray> m_SquareVA;

	Amoeba::Ref<Amoeba::Texture2D> m_Texture, m_AmoebaLogoTexture;

	Amoeba::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};
class Sandbox : public Amoeba::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Amoeba::Application* Amoeba::CreateApplication()
{
	return new Sandbox();
}