#pragma once

#include "Amoeba.h"

class Sandbox2D : public Amoeba::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Amoeba::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Amoeba::Event& e) override;
private:
	Amoeba::OrthographicCameraController m_CameraController;

	// Temp
	Amoeba::Ref<Amoeba::VertexArray> m_SquareVA;
	Amoeba::Ref<Amoeba::Shader> m_FlatColorShader;

	Amoeba::Ref<Amoeba::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};