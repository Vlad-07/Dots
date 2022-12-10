#pragma once

#include <Eis.h>

#include "Dots/Dot.h"
#include "Env/Scene.h"

class Dots2 : public Eis::Layer
{
	Eis::OrthoCameraController m_CamController;

	const int sceneWidth = 50;
	const int sceneHeight = 20;
	const int dotCount = 5;

	Scene m_Scene;

	int m_Tick;

public:
	Dots2();
	virtual ~Dots2() = default;

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Eis::TimeStep ts) override;
	void OnImGuiRender() override;
	void OnEvent(Eis::Event& e) override;
};