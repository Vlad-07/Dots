#include "Brain.h"

#include <cmath>

Brain::Brain() : m_CurrentInputs(), m_InputLayerWeights(), m_HiddenLayers(), m_HiddenLayersWeights(), m_OutputWeights()
{
	Randomize();
}

Brain::Brain(const Brain& brain)
{
	m_CurrentInputs = {};

	m_InputLayerWeights = brain.m_InputLayerWeights;
	m_HiddenLayers = brain.m_HiddenLayers;
	m_HiddenLayersWeights = brain.m_HiddenLayersWeights;
	m_OutputWeights = brain.m_OutputWeights;
}

void Brain::Randomize()
{
	for (HiddenLayer& layer : m_HiddenLayers)
	{
		for (uint32_t i = 0; i < layer.size(); i++)
			layer[i].Randomize();
	}

	for (HiddenLayerWeights& layerWeights : m_HiddenLayersWeights)
		for (ConnectionWeights& weights : layerWeights)
			for (float& weight : weights)
				weight = Eis::Random::Float(WeightMin, WeightMax);

	for (ConnectionWeights& weights : m_InputLayerWeights)
		for (float& weight : weights)
			weight = Eis::Random::Float(WeightMin, WeightMax);

	for (OutputConnectionWeights& weights : m_OutputWeights)
		for (float& weight : weights)
			weight = Eis::Random::Float(WeightMin, WeightMax);
}

Brain::Action Brain::Compute()
{
	// First hidden layer reading from input
	{
		HiddenLayer& layer = m_HiddenLayers[0];
		for (uint32_t source = 0; source < m_CurrentInputs.GetSize(); source++)
			for (uint32_t target = 0; target < layer.size(); target++)
				layer[target].AddSignal(m_CurrentInputs.GetProcessedIput(source), m_InputLayerWeights[source][target]);
	}

	// The rest of hidden connections
	for (uint32_t layerID = 1; layerID < m_HiddenLayers.size(); layerID++)
	{
		HiddenLayer& lastLayer = m_HiddenLayers[layerID - 1];
		HiddenLayerWeights& lastLayerWeights = m_HiddenLayersWeights[layerID - 1];
		HiddenLayer& layer = m_HiddenLayers[layerID];

		for (uint32_t source = 0; source < lastLayer.size(); source++)
		{
			for (uint32_t target = 0; target < layer.size(); target++)
				layer[target].AddSignal(lastLayer[source].GetSignal(), lastLayerWeights[source][target]);
		}
	}

	// Connections from hidden layer to output
	std::array<float, OutputCount> results({}); // SUS: intellisense sees 'result' as a function without the '{}'
	{
		HiddenLayer& lastLayer = m_HiddenLayers[m_HiddenLayers.size() - 1];

		// Add all the signals
		for (uint32_t source = 0; source < lastLayer.size(); source++)
			for (uint32_t target = 0; target < results.size(); target++)
				results[target] += lastLayer[source].GetSignal() * m_OutputWeights[source][target];

		// Normalize the results
		for (float& x : results)
			x = tanhf(x);
	}

	// Figure out the action using the results
	{
		int moveX = 0;
		int moveY = 0;

		if (Eis::Random::Float() < fabs(results[0]))
			moveX = results[0] > 0 ? 1 : -1;
		if (Eis::Random::Float() < fabs(results[1]))
			moveY = results[1] > 0 ? 1 : -1;

		if (!moveX && !moveY)
			return Action::None;

		if (!moveY)
		{
			if (moveX > 0)
				return Action::MoveE;
			else if (moveX < 0)
				return Action::MoveW;
		}

		if (!moveX)
		{
			if (moveY > 0)
				return Action::MoveS;
			else if (moveY < 0)
				return Action::MoveN;
		}

		if (moveX > 0)
		{
			if (moveY > 0)
				return Action::MoveSE;
			else if (moveY < 0)
				return Action::MoveNE;
		}
		else
		{
			if (moveY > 0)
				return Action::MoveSW;
			else if (moveY < 0)
				return Action::MoveNW;
		}
	}
}

void Brain::Mutate(float chance)
{
	for (HiddenLayer& layer : m_HiddenLayers)
	{
		for (uint32_t i = 0; i < layer.size(); i++)
			if (Eis::Random::Float() < chance)
				layer[i].SetBias(Eis::Random::Float(BiasMin, BiasMax));
	}

	for (HiddenLayerWeights& layerWeights : m_HiddenLayersWeights)
		for (ConnectionWeights& weights : layerWeights)
			for (float& weight : weights)
				if (Eis::Random::Float() < chance)
					weight = Eis::Random::Float(WeightMin, WeightMax);

	for (ConnectionWeights& weights : m_InputLayerWeights)
		for (float& weight : weights)
			if (Eis::Random::Float() < chance)
				weight = Eis::Random::Float(WeightMin, WeightMax);

	for (OutputConnectionWeights& weights : m_OutputWeights)
		for (float& weight : weights)
			if (Eis::Random::Float() < chance)
				weight = Eis::Random::Float(WeightMin, WeightMax);
}