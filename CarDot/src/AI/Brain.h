#pragma once

#include <array>

#include <Eis/Core/Random.h>

#include "Neuron.h"

const int BrainSensoryNeurons = 7;
const int BrainActionNeurons = 2;

typedef std::array<SensoryNeuron, BrainSensoryNeurons> SensoryNeurons;
typedef std::array<ActionNeuron, BrainActionNeurons> ActionNeurons;
typedef std::array<std::array<Connection, BrainActionNeurons>, BrainSensoryNeurons> Network;

class Brain
{
public:
	Brain();
	~Brain() = default;

	void SetSensorInput(uint16_t id, float signal);
	void Compute();
	float GetActionNeuronOutput(uint16_t id) const;

	void ResetNetwork();

	void FullyRandomize();

	void Merge(const Brain& b1, const Brain& b2);

	const auto& GetSensoryNeurons() const { return m_SensoryNeurons; }
	const auto& GetConnections() const { return m_SensoryNeuronsConnections; }

	void OverwriteNetwork(const Network& network) { m_SensoryNeuronsConnections = network; }
	
	Brain& operator=(const Brain& b);

private:
	SensoryNeurons m_SensoryNeurons;
	ActionNeurons m_ActionNeurons;
	Network m_SensoryNeuronsConnections;
};