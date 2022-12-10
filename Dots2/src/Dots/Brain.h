#pragma once

#include <glm/glm.hpp>

struct Inputs
{
	glm::vec2 pos;
};

struct Actions
{
	glm::vec2 movement;
};

struct Neuron
{
	float signal;
	float threshold;

	float GetSignal()
	{
		return (signal > threshold ? signal : 0.0f);
	}
};

class Brain
{
public:
	Brain() : m_Computed(false) {}
	~Brain() = default;

	void SetInputs(Inputs in);
	void Compute();
	Actions GetActions();

private:
	Inputs m_CurrentFrameInput;
	Actions m_Actions;
	bool m_Computed;
};