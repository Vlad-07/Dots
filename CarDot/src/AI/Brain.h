#pragma once

#include <array>

#include <Eis/Core/Random.h>

#include "Neuron.h"

const int BrainSensoryNeurons = 8;
const int BrainActionNeurons = 2;

class Brain
{
public:
	Brain();
	~Brain() = default;

	void SetSensorInput(int id, float signal);
	void Compute();
	float GetActionNeuronOutput(int id) const;

	void ResetNetwork();

	void FullyRandomize();

	void Merge(const Brain& b1, const Brain& b2);

	const auto& GetSensoryNeurons() const { return m_SensoryNeurons; }
	const auto& GetConnections() const { return m_SensoryNeuronsConnections; }
	
	Brain& operator=(const Brain& b);

private:
	std::array<SensoryNeuron, BrainSensoryNeurons> m_SensoryNeurons;
	std::array<ActionNeuron, BrainActionNeurons> m_ActionNeurons;
	std::array<std::array<Connection, BrainActionNeurons>, BrainSensoryNeurons> m_SensoryNeuronsConnections;
};