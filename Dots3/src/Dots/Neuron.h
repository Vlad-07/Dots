#pragma once

#include <cmath>
#include <Eis/Core/Random.h>

const float BiasMin = -0.5f;
const float BiasMax =  0.5f;

class Neuron
{
public:
	Neuron() : m_Signal(0.0f), m_Bias(0.0f) {}

	void Randomize() { m_Signal = 0.0f; m_Bias = Eis::Random::Float(BiasMin, BiasMax); }
	void SetBias(float bias) { m_Bias = bias; }
	void Reset() { m_Signal = 0.0f; }

	void AddSignal(float signal, float weight = 1.0f) { m_Signal += signal * weight; }
	float GetSignal() { return tanhf(m_Signal + m_Bias); }

private:
	float m_Signal;
	float m_Bias;
};