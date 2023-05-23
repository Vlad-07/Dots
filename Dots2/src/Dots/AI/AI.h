#pragma once

#include <vector>

#include "Neuron.h"

#include "Eis/Core/Log.h"

#define MAX_NEURON_HIDDEN_CONNECTIONS 10
#define MAX_NEURON_OUT_CONNECTIONS 5
#define NEURON_CONNECTION_CHANCE 0.2f

// SUS: crapy macro
#define MAX_INPUT_HIDDEN_CONNECTIONS (m_HiddenCount / 2u)
#define INPUT_CONNECTION_CHANCE 0.7f


struct BrainConfig
{
	uint32_t inputCount;
	uint32_t outputCount;
	uint32_t maxHiddenNeurons;

	const bool operator ==(const BrainConfig& brain) const
	{
		if (inputCount != brain.inputCount)
			return false;
		if (outputCount != brain.outputCount)
			return false;
		if (maxHiddenNeurons != brain.maxHiddenNeurons)
			return false;
		return true;
	}
	const bool operator !=(const BrainConfig& brain) const
	{
		if ((inputCount != brain.inputCount) || (inputCount != brain.inputCount) || (inputCount != brain.inputCount))
			return true;
		return false;
	}
	operator bool() const
	{
		return ((bool)inputCount || (bool)outputCount || (bool)maxHiddenNeurons);
	}
};

class Brain
{
public:
	Brain(uint32_t inputCount, uint32_t outputCount, uint32_t maxHiddenNeurons);
	Brain(const BrainConfig& config);
	~Brain() = default;

	void Compute();
	void SetInput(const std::vector<float>& inputs);

	std::vector<float> GetOutput() const;
	inline BrainConfig GetConfig() const { return { m_InputCount, m_OutputCount, m_HiddenCount }; }
	inline std::vector<InputReceptor>& GetInputNeurons() { return m_Inputs; }
	inline std::vector<HiddenNeuron>& GetHiddenNeurons() { return m_Hidden; }
	inline uint32_t GetInputCount() const { return m_InputCount; }
	inline uint32_t GetHiddenCount() const { return m_HiddenCount; }
	inline uint32_t GetOutputCount() const { return m_OutputCount; }

	void SetInputNeurons(const std::vector<InputReceptor>& inputs) { m_Inputs = inputs; }
	void SetHiddenNeurons(const std::vector<HiddenNeuron>& hidden) { m_Hidden = hidden; }
	void SetInputNeuron(const InputReceptor& receptor, int pos) { m_Inputs[pos] = receptor; }
	void SetHiddenNeuron(const HiddenNeuron& hidden, int pos) { m_Hidden[pos] = hidden; }

	void Randomize();
	void DeleteNetwork();

	void operator =(const Brain& brain);

private:
	void ResetNetwork();
	void ResetOutput();

private:
	std::vector<InputReceptor> m_Inputs;
	std::vector<HiddenNeuron> m_Hidden;
	std::vector<float> m_Output;

	uint32_t m_InputCount, m_OutputCount;
	uint32_t m_HiddenCount; // technicaly all of them exist but some may be unconnected
};



class Combinator
{
public:

	enum MergeMethod
	{
		None = 0, SingleCut, MultiCut, Uniform
	};
	
	static Brain MergeBrains(Brain& brain1, Brain& brain2, MergeMethod method);
	static void MutateBrain(Brain& brain);
};