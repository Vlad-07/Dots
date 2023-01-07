#pragma once

#include <Eis.h>

#include "Dots/Dot.h"
#include "Env/Simulator.h"

class Dots2 : public Eis::Layer
{
	Eis::OrthoCameraController m_CamController;

	const int sceneWidth = 20;
	const int sceneHeight = 20;
	const int dotCount = 200;

	Simulator m_Simulator;
public:
	Dots2();
	virtual ~Dots2() = default;

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Eis::TimeStep ts) override;
	void OnImGuiRender() override;
	void OnEvent(Eis::Event& e) override;
};