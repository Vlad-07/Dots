#pragma once

#include"../Utils.h"

struct Inputs
{
	Vec2<int> pos;
};

struct Actions
{
	Vec2<int> movement;
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