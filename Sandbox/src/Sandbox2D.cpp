#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Amoeba::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	
}

void Sandbox2D::OnUpdate(Amoeba::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Amoeba::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Amoeba::RenderCommand::Clear();

	Amoeba::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Amoeba::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Amoeba::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Amoeba::Renderer2D::DrawQuad({ 0.25f, -0.25f }, { 0.5f, 1.50f }, { 0.7f, 0.15f, 0.4f, 1.0f });
	Amoeba::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
	Amoeba::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Amoeba::Event& e)
{
	m_CameraController.OnEvent(e);
}