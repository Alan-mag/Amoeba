#pragma once

#include "Amoeba.h"

class ExampleLayer : public Amoeba::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Amoeba::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Amoeba::Event& e) override;
private:
	Amoeba::ShaderLibrary m_ShaderLibrary;
	Amoeba::Ref<Amoeba::Shader> m_Shader;
	Amoeba::Ref<Amoeba::VertexArray> m_VertexArray;

	Amoeba::Ref<Amoeba::Shader> m_FlatColorShader;
	Amoeba::Ref<Amoeba::VertexArray> m_SquareVA;

	Amoeba::Ref<Amoeba::Texture2D> m_Texture, m_ChernoLogoTexture;

	Amoeba::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};
