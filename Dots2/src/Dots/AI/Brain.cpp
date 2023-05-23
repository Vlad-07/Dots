#include "AI.h"

#include <Eis/Core/Random.h>
#include <Eis/Core/Log.h>


Brain::Brain(uint32_t inputCount, uint32_t outputCount, uint32_t maxHiddenNeurons)
	: m_InputCount(inputCount), m_OutputCount(outputCount), m_HiddenCount(maxHiddenNeurons),
	  m_Inputs(inputCount), m_Output(outputCount, 0.0f), m_Hidden(maxHiddenNeurons)
{
	Randomize();
}

Brain::Brain(const BrainConfig& config) : m_InputCount(config.inputCount), m_OutputCount(config.outputCount), m_HiddenCount(config.maxHiddenNeurons)
{
	Randomize();
}

void Brain::SetInput(const std::vector<float>& inputs)
{
	if (inputs.size() != m_InputCount)
	{
		EIS_ERROR("Invalid brain input array given!");
		return;
	}

	for (uint32_t i = 0; i < m_Inputs.size(); i++)
		m_Inputs[i].SetSignal(inputs[i]);
}

std::vector<float> Brain::GetOutput() const
{
	std::vector<float> output = m_Output;
	for (float& out : output)
		out = tanh(out);
	return output;
}

void Brain::Compute()
{
	ResetNetwork();
	ResetOutput();

	// handle inputs
	for (const InputReceptor& r : m_Inputs)
	{
		for (uint32_t id : r.connections)
			m_Hidden[id].AddSignal(r.Func());
	}

	// handle hidden layer
	for (uint32_t i = 0; i < m_Hidden.size(); i++)
	{
		HiddenNeuron& n = m_Hidden[i];

		if (n.Func() == 0.0f)
			continue;

		// handle connections inside the hidden layer
		for (uint32_t i = 0; i < n.connections.size(); i++)
		{
			const uint32_t& id = n.connections[i];
			if (id <= i)
			{
//				EIS_WARN("Write operation will have no effect!");
				n.connections.erase(n.connections.begin() + i);
			}

			m_Hidden[id].AddSignal(n.Func());
		}

		// handle connections to output
		for (uint32_t id : n.outConnections)
			m_Output[id] += n.Func();
	}
}

void Brain::Randomize()
{
	DeleteNetwork();

	// generate input connections
	for (int i = 0; i < m_InputCount; i++)
	{
		InputReceptor& r = m_Inputs[i];
		
		for (int j = 0; j < MAX_INPUT_HIDDEN_CONNECTIONS; j++)
		{
			if (!(Eis::Random::Float(0.0f, 1.0f) < INPUT_CONNECTION_CHANCE / (r.connections.size() + 1)))
				continue;

			int64_t id = 0;
			while (true)
			{
				id = Eis::Random::UInt(0, m_HiddenCount - 1);
				for (int idd : r.connections)
				{
					if (id == idd)
					{
						id = -1;
						break;
					}
				}
				if (id >= 0)
					break;
			}
			r.connections.push_back(id);
		}
	}

	// generate neuron connections
	for (int i = 0; i < m_HiddenCount; i++)
	{
		HiddenNeuron& n = m_Hidden[i];

		n.SetWeight(Eis::Random::Float(-2.0f, 2.0f));

		// generate hidden connections
		for (int j = 0;
			j < MAX_NEURON_HIDDEN_CONNECTIONS && i != m_HiddenCount - 1 && n.connections.size() < MAX_NEURON_HIDDEN_CONNECTIONS && n.connections.size() < m_HiddenCount - 1; j++)
		{
			if (!(Eis::Random::Float(0.0f, 1.0f) < NEURON_CONNECTION_CHANCE))
				continue;

			uint32_t id = 0;
			while (id <= i && m_HiddenCount - i - 1 > n.connections.size())
			{
				id = Eis::Random::UInt(0, m_HiddenCount - 1);
				for (int idd : n.connections)
				{
					if (id == idd)
					{
						id = 0;
						break;
					}
				}
			}
			n.connections.push_back(id);
		}

		// generate out connections
		for (int j = 0; j < MAX_NEURON_OUT_CONNECTIONS && n.outConnections.size() < MAX_NEURON_OUT_CONNECTIONS && n.outConnections.size() < m_OutputCount; j++)
		{
			if (!(Eis::Random::Float(0.0f, 1.0f) < NEURON_CONNECTION_CHANCE))
				continue;
			
			int64_t id = 0;
			while (true)
			{
				id = Eis::Random::UInt(0, m_OutputCount - 1);
				for (int idd : n.outConnections)
				{
					if (id == idd)
					{
						id = -1;
						break;
					}
				}
				if (id >= 0)
					break;
			}
			n.outConnections.push_back(id);
		}
	}
}

void Brain::DeleteNetwork()
{
	m_Inputs.clear();
	m_Inputs.resize(m_InputCount);

	m_Hidden.clear();
	m_Hidden.resize(m_HiddenCount);
}

void Brain::ResetNetwork()
{
	for (Neuron& n : m_Hidden)
		n.Reset();
}

void Brain::ResetOutput()
{
	for (int i = 0; i < m_Output.size(); i++)
		m_Output[i] = 0.0f;
}


void Brain::operator=(const Brain& brain)
{
	m_InputCount = brain.m_InputCount;
	m_OutputCount = brain.m_OutputCount;
	m_HiddenCount = brain.m_HiddenCount;

	m_Inputs = brain.m_Inputs;
	m_Hidden = brain.m_Hidden;
}