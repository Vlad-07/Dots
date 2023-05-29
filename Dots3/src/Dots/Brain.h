#pragma once

#include <Eis.h>
#include <array>
#include <utility>

#include "Neuron.h"

// NN Params

const int InputCount			 = 7;
const int OutputCount			 = 2;

const int NeuronsPerHiddenLayer	 = 3;
const int HiddenLayerCount		 = 3;

const float ActionActivThreshold = 0.65f;

const float WeightMin			 = -4.0f;
const float WeightMax			 =  4.0f;
// bias range defined in Neuron.h

const float DefaultMutationChance = 0.0025f;

// Hidden
typedef std::array<Neuron, NeuronsPerHiddenLayer> HiddenLayer;
typedef std::array<HiddenLayer, HiddenLayerCount> HiddenLayers;


// Weights of one neuron
typedef std::array<float, NeuronsPerHiddenLayer> ConnectionWeights;
typedef std::array<float, OutputCount> OutputConnectionWeights;

// Weights of a layer (any one layer)
typedef std::array<ConnectionWeights, InputCount> InputLayerWeights;
typedef std::array<ConnectionWeights, NeuronsPerHiddenLayer> HiddenLayerWeights;
typedef std::array<OutputConnectionWeights, NeuronsPerHiddenLayer> OutputLayerWeights; // Weights for the last hidden layer, thus the -1 below

// All hidden layer weights
typedef std::array<HiddenLayerWeights, HiddenLayerCount - 1> HiddenLayersWeights; // -1 explained above



class Brain
{
public:
	// Acts as the input layer
	struct Inputs
	{
		static int GetSize() { assert(InputCount == 7, "Update input count var!"); return InputCount; }

		// Value should be in -1 to 1 range!
		void SetInput(uint32_t id, float val)
		{
			switch (id)
			{
			case 0:
				posX = val;
				break;
			case 1:
				posY = val;
				break;
			case 2:
				random = val;
				break;
			case 3:
				oscilator = val;
				break;
			case 4:
				borderDistNS = val;
				break;
			case 5:
				borderDistWE = val;
				break;
			case 6:
				nearestBorder = val;
				break;
			default:
				EIS_ASSERT(false, "Invalid input id to set: {0}", id);
				break;
			}
		}
		float GetProcessedIput(uint32_t id)
		{
			switch (id)
			{
			case 0:
				return posX;
			case 1:
				return posY;
			case 2:
				return random;
			case 3:
				return oscilator;
			case 4:
				return borderDistNS;
			case 5:
				return borderDistWE;
			case 6:
				return nearestBorder;
			default:
				EIS_ASSERT(false, "Invalid input id requested: {0}", id);
				return 0.0f;
			}
		}

		inline void ResetInputs()
		{
			posX = 0.0f;
			posY = 0.0f;
		}

		void operator =(const Inputs& ins)
		{
			posX = ins.posX;
			posY = ins.posY;
		}

	private:
		float posX, posY, random, oscilator, borderDistNS, borderDistWE, nearestBorder;
	};

	enum Action
	{
		None = 0, MoveN, MoveS, MoveW, MoveE, MoveNW, MoveNE, MoveSW, MoveSE
	};

public:
	Brain();
	Brain(const Brain& brain);
	~Brain() = default;

	void Randomize();

	inline void SetInputs(const Inputs& inputs) { m_CurrentInputs = inputs; }

	Action Compute();

	void Mutate(float chance = DefaultMutationChance);

private:
	Inputs m_CurrentInputs;
	InputLayerWeights m_InputLayerWeights;
	HiddenLayers m_HiddenLayers;
	HiddenLayersWeights m_HiddenLayersWeights;
	OutputLayerWeights m_OutputWeights;
};