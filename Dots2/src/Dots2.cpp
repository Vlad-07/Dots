#include "Dots2.h"

Dots2::Dots2() : m_CamController(16.0f / 9.0f), m_Scene(sceneWidth, sceneHeight, dotCount), m_Tick(0)
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
	m_Tick++;
//	EIS_TRACE("Tick: {0}", m_Tick);

//	m_CamController.OnUpdate(ts); // TODO: implement key system in Eis

	Eis::RenderCommands::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	Eis::RenderCommands::Clear();

	Eis::Renderer2D::BeginScene(m_CamController.GetCamera());

	m_Scene.Update(true);
	m_Scene.DrawScene();

	Eis::Renderer2D::EndScene();
}

void Dots2::OnImGuiRender()
{
}

void Dots2::OnEvent(Eis::Event& e)
{
	m_CamController.OnEvent(e);
}