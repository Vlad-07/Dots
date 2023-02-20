#include "Dots2.h"

Dots2::Dots2() : m_CamController(16.0f / 9.0f), m_Simulator(sceneWidth, sceneHeight, dotCount, false)
{
}

void Dots2::OnAttach()
{
}

void Dots2::OnDetach()
{
}

void Dots2::OnUpdate(Eis::TimeStep ts)
{
//	EIS_TRACE("Tick: {0}", m_Tick);

	// TODO: Gen sys

	m_CamController.OnUpdate(ts);

	Eis::RenderCommands::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	Eis::RenderCommands::Clear();

	Eis::Renderer2D::BeginScene(m_CamController.GetCamera());

	m_Simulator.Update();
	m_Simulator.DrawScene();

	Eis::Renderer2D::EndScene();
}

void Dots2::OnImGuiRender()
{
}

void Dots2::OnEvent(Eis::Event& e)
{
	m_CamController.OnEvent(e);
}