#pragma once

#include <Eis.h>
#include <imgui.h>

#include "Simulator.h"

extern bool SurvivalLaw(const Dot& dot);

class Dots3 : public Eis::Layer
{
public:
	Dots3();
	virtual ~Dots3() = default;

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Eis::TimeStep ts) override;
	void OnImGuiRender() override;
	void OnEvent(Eis::Event& e) override;

private:
	Eis::OrthoCameraController m_CameraController;

	Simulator m_Simulator;

	bool m_RenderDots;

private:
	const glm::vec2 DotRenderingSize = glm::vec2(0.9f);
};