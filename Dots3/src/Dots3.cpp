#include "Dots3.h"

Dots3::Dots3() : m_CameraController(16.0f / 9.0f), m_RenderDots(true)
{
}

void Dots3::OnAttach()
{
	Eis::RenderCommands::Disable(0x0B71); // GL_DEPTH_TEST
	m_CameraController.OnEvent(Eis::MouseScrolledEvent(0.0f, -270.0f)); // HACK: artificial camera zoom

	m_Simulator.Init();

	EIS_INFO("Generation: 0");
	EIS_INFO("Tick: 0\n");
}

void Dots3::OnDetach() {}


void Dots3::OnUpdate(Eis::TimeStep ts)
{
	m_CameraController.OnUpdate(ts);

	Eis::RenderCommands::Clear();
	Eis::RenderCommands::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

	m_Simulator.Step();

	Eis::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Eis::Renderer2D::DrawQuad(glm::vec2(0), glm::vec2(m_Simulator.GetSize()) + DotRenderingSize, glm::vec4(0.4f, 0.4f, 0.4f, 1.0f));

	if (m_RenderDots)
	{
		for (const Dot& dot : m_Simulator.GetDots())
			Eis::Renderer2D::DrawCircle(dot.GetPos() - m_Simulator.GetSize() / 2, DotRenderingSize, glm::vec4(1.0f));
	}
	
	Eis::Renderer2D::EndScene();

	if (m_Simulator.GetTick() % TicksPerGen == 0)
	{
		m_Simulator.StepGen();
		EIS_INFO("Generation: {0}", m_Simulator.GetGen());
		EIS_INFO("Tick: {0}\n", m_Simulator.GetTick());
	}
}

void Dots3::OnImGuiRender()
{
	ImGui::Begin("Settings");

	ImGui::Checkbox("Render dots", &m_RenderDots);
	if (ImGui::Button("Pause"))
		m_Simulator.SetPause(!m_Simulator.GetPause());

	ImGui::End();
}

void Dots3::OnEvent(Eis::Event& e)
{
	m_CameraController.OnEvent(e);
}