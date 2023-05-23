#include "Dots2.h"

#include <string>

const float sceneWidth = 100;
const float sceneHeight = 100;
const int dotCount = 100;



bool DotSelectionLaw(const Dot& dot, const Simulator& sim)
{
	return (dot.GetPos().x < sim.GetSize().x / 4);
}



Dots2::Dots2() : m_CameraController(16.0f / 9.0f), m_Simulator(sceneWidth, sceneHeight, dotCount, false), m_Draw(true)
{
}

void Dots2::OnAttach()
{
	Eis::RenderCommands::Disable(0x0B71); // GL_DEPTH_TEST

	m_Simulator.SetSimPos(glm::vec2(-sceneWidth / 2.0f, -sceneHeight / 2.0f));
	m_CameraController.OnEvent(Eis::MouseScrolledEvent(0.0f, -270.0f)); // HACK: artificial camera zoom
}

void Dots2::OnDetach()
{
}

void Dots2::OnUpdate(Eis::TimeStep ts)
{
	m_CameraController.OnUpdate(ts);

	Eis::RenderCommands::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	Eis::RenderCommands::Clear();

	// generation
	if (m_Simulator.GetTick() % 1000 == 0)
	{
		EIS_INFO("Generation: {0}", m_Simulator.GetGeneration());
		m_Simulator.NextGeneration();
		EIS_INFO("Survived: {0}\n", m_Simulator.GetSurvivorCount());
	}

	Eis::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Eis::Renderer2D::DrawQuad(glm::vec2(0.0f), m_Simulator.GetSize() + m_Simulator.GetDotRenderingRadius(), glm::vec4(0.5, 0.5f, 0.5f, 1.0f));
	m_Simulator.Update();
	if (m_Draw)
		m_Simulator.DrawScene();

	Eis::Renderer2D::EndScene();
}

void Dots2::OnImGuiRender()
{
	ImGui::Begin("Settings");

	ImGui::Checkbox("Draw dots", &m_Draw);

	ImGui::End();
}

void Dots2::OnEvent(Eis::Event& e)
{
	m_CameraController.OnEvent(e);
}