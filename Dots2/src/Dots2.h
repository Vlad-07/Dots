#pragma once

#include <imgui.h>

#include <Eis.h>

#include "Dots/Dot.h"
#include "Env/Simulator.h"

// Promising but flawed attempt

class Dots2 : public Eis::Layer
{
public:
	Dots2();
	virtual ~Dots2() = default;

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Eis::TimeStep ts) override;
	void OnImGuiRender() override;
	void OnEvent(Eis::Event& e) override;

private:
	Eis::OrthoCameraController m_CameraController;
	Simulator m_Simulator;

	bool m_Draw;
};