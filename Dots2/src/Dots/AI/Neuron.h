#pragma once

#include <cmath>

class Neuron
{
public:
	Neuron() : m_Signal(0.0f) {}
	virtual ~Neuron() = default;

	virtual float Func() const = 0;

	inline void Reset()
	{
		m_Signal = 0.0f;
	}


protected:
	float m_Signal;
};


class InputReceptor : public Neuron
{
public:
	InputReceptor() = default;

	virtual float Func() const override { return m_Signal; }

	inline void SetSignal(float signal) { m_Signal = signal; }

public:
	std::vector<uint32_t> connections;
};

class HiddenNeuron : public Neuron
{
public:
	HiddenNeuron() : Neuron(), m_Weight(1.0f) {}

	virtual float Func() const override
	{
		float sig = tanh(m_Signal * m_Weight);
		return sig;
	}

	inline void AddSignal(float signal) { m_Signal += signal; }

	inline void SetWeight(float weight)
	{
		m_Weight = weight;
	}

public:
	std::vector<uint32_t> connections;
	std::vector<uint32_t> outConnections;

private:
	float m_Weight;
};