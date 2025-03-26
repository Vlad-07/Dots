#include "Brain.h"

Brain::Brain() : m_SensoryNeurons(), m_ActionNeurons(), m_SensoryNeuronsConnections()
{
	FullyRandomize();
}

void Brain::Compute()
{
	for (int i = 0; i < m_SensoryNeurons.size(); i++)
	{
		const SensoryNeuron& s = m_SensoryNeurons[i];
		for (const Connection& c : m_SensoryNeuronsConnections[i])
			m_ActionNeurons[c.GetDestinationID()].AddSignal(s.GetSignal() * c.GetWeight());
	}
}

void Brain::ResetNetwork()
{
	for (SensoryNeuron& s : m_SensoryNeurons)
		s.ResetSignal();
	for (ActionNeuron& a : m_ActionNeurons)
		a.ResetSignal();
}

void Brain::FullyRandomize()
{
	for (auto& neuronConns : m_SensoryNeuronsConnections)
		for (int i = 0; i < neuronConns.size(); i++)
			neuronConns[i] = Connection(i, Eis::Random::Float(-2.0f, 2.0f), true);
}

void Brain::Merge(const Brain& b1, const Brain& b2)
{
	for (int i = 0; i < m_SensoryNeuronsConnections.size(); i++)
	{
		for (int j = 0; j < m_SensoryNeuronsConnections[i].size(); j++)
		{
			float randomVal = Eis::Random::Float();
			if (randomVal > 0.55f)	// First Parent
				m_SensoryNeuronsConnections[i][j].SetWeight(b1.m_SensoryNeuronsConnections[i][j].GetWeight());
			else if (randomVal > 0.2f) // Second parent
				m_SensoryNeuronsConnections[i][j].SetWeight(b2.m_SensoryNeuronsConnections[i][j].GetWeight());
			else						// Mutate
				m_SensoryNeuronsConnections[i][j].SetWeight(Eis::Random::Float(-2.0f, 2.0f));
		}
	}
}

void Brain::SetSensorInput(uint16_t id, float signal)
{
	if (id >= BrainSensoryNeurons)
		EIS_ASSERT(false, "Writing to invalid sensory neuron!");

	m_SensoryNeurons[id].AddSignal(signal);
}
float Brain::GetActionNeuronOutput(uint16_t id) const
{
	if (id >= BrainSensoryNeurons)
		EIS_ASSERT(false, "Reading invalid action neuron!");

	return m_ActionNeurons[id].GetSignal();
}

Brain& Brain::operator=(const Brain& b)
{
	ResetNetwork();
	m_SensoryNeuronsConnections = b.m_SensoryNeuronsConnections;
	return *this;
}