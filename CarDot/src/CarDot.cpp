#include "CarDot.h"

CarDot::CarDot()
	: m_CameraController(16.0f / 9.0f, true), m_LastFrameTime(0.0f), m_SubjectManager(m_InteriorLineNodes, m_ExteriorLineNodes, m_Checkpoints, Eis::Texture2D::Create("assets/textures/car.png"))
{}

void CarDot::OnAttach()
{
	EIS_PROFILE_FUNCTION();

	Eis::RenderCommands::Disable(0x0B71); // GL_DEPTH_TEST
	m_CameraController.OnEvent(Eis::MouseScrolledEvent(0.0f, -100.0f)); // HACK: artificial camera zoom

	#pragma region Track Bounds
	m_InteriorLineNodes.push_back(glm::vec2(17.206f, 0.0f));
	m_InteriorLineNodes.push_back(glm::vec2(17.0f, 15.441f));
	m_InteriorLineNodes.push_back(glm::vec2(-25.147f, 15.0f));
	m_InteriorLineNodes.push_back(glm::vec2(-25.0f, -15.882f));

	m_ExteriorLineNodes.push_back(glm::vec2(22.0f, 0.0f));
	m_ExteriorLineNodes.push_back(glm::vec2(22.059f, 19.412f));
	m_ExteriorLineNodes.push_back(glm::vec2(-28.676f, 19.0f));
	m_ExteriorLineNodes.push_back(glm::vec2(-28.0f, -19.412f));
	m_ExteriorLineNodes.push_back(glm::vec2(-22.059f, -19.0f));
	
	m_Checkpoints.push_back({ glm::vec2( 17.001f,   5.001f), glm::vec2( 22.0f,   5.0f) }); //  0
	m_Checkpoints.push_back({ glm::vec2( 17.001f,   8.001f), glm::vec2( 22.0f,   8.0f) }); //  1
	m_Checkpoints.push_back({ glm::vec2( 17.001f,  11.001f), glm::vec2( 22.0f,  11.0f) }); //  2
	m_Checkpoints.push_back({ glm::vec2( 17.001f,  15.001f), glm::vec2( 22.0f,  15.0f) }); //  3
	m_Checkpoints.push_back({ glm::vec2( 17.001f,  15.501f), glm::vec2( 22.0f,  19.5f) }); //  4
	m_Checkpoints.push_back({ glm::vec2( 16.901f,  15.501f), glm::vec2( 16.9f,  19.5f) }); //  5
	m_Checkpoints.push_back({ glm::vec2( 14.001f,  15.501f), glm::vec2( 14.0f,  19.5f) }); //  6
	m_Checkpoints.push_back({ glm::vec2( 11.001f,  15.501f), glm::vec2( 11.0f,  19.5f) }); //  7
	m_Checkpoints.push_back({ glm::vec2(  8.001f,  15.501f), glm::vec2(  8.0f,  19.5f) }); //  8
	m_Checkpoints.push_back({ glm::vec2(  2.001f,  15.301f), glm::vec2(  2.0f,  19.4f) }); //  9
	m_Checkpoints.push_back({ glm::vec2( -5.001f,  15.301f), glm::vec2( -5.0f,  19.4f) }); // 10
	m_Checkpoints.push_back({ glm::vec2(-12.001f,  15.301f), glm::vec2(-12.0f,  19.4f) }); // 11
	m_Checkpoints.push_back({ glm::vec2(-20.001f,  15.301f), glm::vec2(-20.0f,  19.3f) }); // 12
	m_Checkpoints.push_back({ glm::vec2(-25.001f,  15.301f), glm::vec2(-25.0f,  19.3f) }); // 13
	m_Checkpoints.push_back({ glm::vec2(-25.301f,  15.001f), glm::vec2(-28.5f,  19.3f) }); // 14
	m_Checkpoints.push_back({ glm::vec2(-25.301f,  15.001f), glm::vec2(-28.5f,  15.0f) }); // 15
	m_Checkpoints.push_back({ glm::vec2(-25.201f,  14.001f), glm::vec2(-28.5f,  14.0f) }); // 16
	m_Checkpoints.push_back({ glm::vec2(-25.101f,   5.001f), glm::vec2(-28.5f,   5.0f) }); // 17
	m_Checkpoints.push_back({ glm::vec2(-25.101f,   0.001f), glm::vec2(-28.4f,   0.0f) }); // 18
	m_Checkpoints.push_back({ glm::vec2(-25.101f,  -5.001f), glm::vec2(-28.3f,  -5.0f) }); // 19
	m_Checkpoints.push_back({ glm::vec2(-25.101f, -10.001f), glm::vec2(-28.2f, -10.0f) }); // 20
	m_Checkpoints.push_back({ glm::vec2(-25.101f, -15.901f), glm::vec2(-28.1f, -15.9f) }); // 21
	m_Checkpoints.push_back({ glm::vec2(-25.001f, -15.801f), glm::vec2(-28.1f, -19.5f) }); // 22
	m_Checkpoints.push_back({ glm::vec2(-25.001f, -15.801f), glm::vec2(-25.1f, -19.3f) }); // 23
	m_Checkpoints.push_back({ glm::vec2(-25.001f, -15.801f), glm::vec2(-22.0f, -19.3f) }); // 24
	m_Checkpoints.push_back({ glm::vec2(-19.501f, -13.001f), glm::vec2(-17.0f, -17.3f) }); // 25
	m_Checkpoints.push_back({ glm::vec2(-15.001f, -12.001f), glm::vec2(-12.0f, -14.5f) }); // 26
	m_Checkpoints.push_back({ glm::vec2( -7.001f,  -9.001f), glm::vec2( -5.0f, -11.5f) }); // 27
	m_Checkpoints.push_back({ glm::vec2(  0.001f,  -6.501f), glm::vec2(  2.0f,  -8.5f) }); // 28
	m_Checkpoints.push_back({ glm::vec2( 10.001f,  -2.701f), glm::vec2( 12.0f,  -4.2f) }); // 29
	m_Checkpoints.push_back({ glm::vec2( 17.101f,   0.001f), glm::vec2( 22.0f,   0.0f) }); // 30
	#pragma endregion

	m_SubjectManager.LoadBestSave();
}

void CarDot::OnDetach() {}


void CarDot::OnUpdate(Eis::TimeStep ts)
{
	EIS_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);

	Eis::RenderCommands::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	Eis::RenderCommands::Clear();

	m_LastFrameTime = ts;

	Eis::Renderer2D::BeginScene(m_CameraController.GetCamera());

	DrawTrack();

	m_SubjectManager.DrawBestNetwork();

	m_SubjectManager.Update(ts);

	Eis::Renderer2D::EndScene();
}

void CarDot::OnImGuiRender()
{
	EIS_PROFILE_FUNCTION();

	ImGui::Begin("Stats");

	ImGui::Text("Generation: %i", m_SubjectManager.GetGeneration());
	ImGui::Text("Tick: %i", m_SubjectManager.GetTick());
	ImGui::Text("Alive: %i", m_SubjectManager.AliveSubjects());
	ImGui::Text("Best Score: %i", m_SubjectManager.GetBestScore());
	ImGui::Text("Top Score: %i", m_SubjectManager.GetTopScore());

	ImGui::NewLine();
	
	ImGui::Text("FPS: %.1f", 1.0f / m_LastFrameTime);

	/*ImGui::NewLine();

	ImGui::SliderFloat2("Pos", &m_PreviewPos.x, -30.0f, 30.0f);
	if (ImGui::Button("Place Node"))
	{
		m_ExteriorLineNodes.push_back(m_PreviewPos);
		for (const auto& pos : m_ExteriorLineNodes)
			EIS_INFO("{0}, {1}", pos.x, pos.y);
		EIS_INFO("");
	}*/

	ImGui::End();
}

void CarDot::OnEvent(Eis::Event& e)
{
	m_CameraController.OnEvent(e);
}

void CarDot::DrawTrack()
{
	EIS_PROFILE_FUNCTION();

	for (int i = 1; i < m_InteriorLineNodes.size(); i++)
		Eis::Renderer2D::DrawLine(glm::vec3(m_InteriorLineNodes[i - 1], 0.0f), glm::vec3(m_InteriorLineNodes[i], 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 1.0f);
	Eis::Renderer2D::DrawLine(glm::vec3(m_InteriorLineNodes.front(), 0.0f), glm::vec3(m_InteriorLineNodes.back(), 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 1.0f);

	for (int i = 1; i < m_ExteriorLineNodes.size(); i++)
		Eis::Renderer2D::DrawLine(glm::vec3(m_ExteriorLineNodes[i - 1], 0.0f), glm::vec3(m_ExteriorLineNodes[i], 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 1.0f);
	Eis::Renderer2D::DrawLine(glm::vec3(m_ExteriorLineNodes.front(), 0.0f), glm::vec3(m_ExteriorLineNodes.back(), 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 1.0f);

	for (int i = 0; i < m_Checkpoints.size(); i++)
		Eis::Renderer2D::DrawLine(glm::vec3(m_Checkpoints[i].start, 0.0f), glm::vec3(m_Checkpoints[i].end, 0.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), 1.0f);
}