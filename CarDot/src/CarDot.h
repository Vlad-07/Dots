#pragma once

#include <Eis.h>
#include <imgui.h>

#include "Car/Car.h"
#include "AI/Subject.h"
#include "AI/SubjectManager.h"

class CarDot : public Eis::Layer
{
public:
	CarDot();
	virtual ~CarDot() = default;


	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Eis::TimeStep ts) override;
	void OnImGuiRender() override;
	void OnEvent(Eis::Event& e) override;

	void DrawTrack();

private:
	Eis::OrthoCameraController m_CameraController;

	SubjectManager m_SubjectManager;

	std::vector<glm::vec2> m_InteriorLineNodes;
	std::vector<glm::vec2> m_ExteriorLineNodes;
	std::vector<Checkpoint> m_Checkpoints;

	float m_LastFrameTime;
	bool m_DebugMode;
	bool m_Running;

	float m_ScoreSamples[20];
	int m_LastGen;
};