#include "AI.h"

#include "Eis/Core/Random.h"

Brain UniformMerge(Brain& brain1, Brain& brain2);
Brain SingleCutMerge(Brain& brain1, Brain& brain2);

Brain Combinator::MergeBrains(Brain& brain1, Brain& brain2, Combinator::MergeMethod method)
{
	if (brain1.GetConfig() != brain2.GetConfig())
	{
		EIS_ERROR("Trying to merge incompatible brains!");
		return Brain({});
	}

	switch (method)
	{
	case Combinator::None:
		EIS_ERROR("Invalid brain merging method selected: None");
		break;
	case Combinator::SingleCut:
		return SingleCutMerge(brain1, brain2);
	case Combinator::MultiCut:
		EIS_ERROR("Brain merging method not implemented: MultiCut");
		break;
	case Combinator::Uniform:
		return UniformMerge(brain1, brain2);
	}
	return Brain({});
}

Brain SingleCutMerge(Brain& brain1, Brain& brain2)
{
	Brain result(brain1.GetConfig());
	result.DeleteNetwork();

	uint32_t inputCutPoint = Eis::Random::UInt(0, result.GetInputCount() - 1);
	for (uint32_t i = 0; i < inputCutPoint; i++)
		result.SetInputNeuron(brain1.GetInputNeurons()[i], i);
	for (uint32_t i = inputCutPoint; i < result.GetInputCount(); i++)
		result.SetInputNeuron(brain2.GetInputNeurons()[i], i);

	uint32_t hiddenCutPoint = Eis::Random::UInt(0, result.GetHiddenCount() - 1);
	for (uint32_t i = 0; i < hiddenCutPoint; i++)
		result.SetHiddenNeuron(brain1.GetHiddenNeurons()[i], i);
	for (uint32_t i = hiddenCutPoint; i < result.GetHiddenCount(); i++)
		result.SetHiddenNeuron(brain2.GetHiddenNeurons()[i], i);

	return result;
}

Brain UniformMerge(Brain& brain1, Brain& brain2)
{
	Brain result(brain1.GetConfig());
	result.DeleteNetwork();

	const auto& inputs1 = brain1.GetInputNeurons();
	const auto& inputs2 = brain2.GetInputNeurons();
	for (uint32_t i = 0; i < result.GetInputNeurons().size(); i++)
	{
		if (Eis::Random::Float() > 0.5f)
			result.SetInputNeuron(inputs1[i], i);
		else
			result.SetInputNeuron(inputs2[i], i);
	}

	const auto& hidden1 = brain1.GetHiddenNeurons();
	const auto& hidden2 = brain2.GetHiddenNeurons();
	for (uint32_t i = 0; i < result.GetHiddenNeurons().size(); i++)
	{
		if (Eis::Random::Float() > 0.5f)
			result.SetHiddenNeuron(hidden1[i], i);
		else
			result.SetHiddenNeuron(hidden2[i], i);
	}

	return result;
}


void Combinator::MutateBrain(Brain& brain)
{
	if (Eis::Random::Float() < 0.9f)
		return;

	for (InputReceptor& r : brain.GetInputNeurons())
	{
		// mutate connections
		if (Eis::Random::Float() < 0.3f)
		{
			if (Eis::Random::Float() > 0.5f && r.connections.size() > 1)
				r.connections.erase(r.connections.begin() + Eis::Random::UInt(0, r.connections.size() - 1));
			else
			{
				int64_t id = 0;
				while (true)
				{
					id = Eis::Random::UInt(0, brain.GetOutputCount() - 1);
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
	}

	for (uint32_t i = 0; i < brain.GetHiddenCount(); i++)
	{
		HiddenNeuron& n = brain.GetHiddenNeurons()[i];

		// leave alone
		if (Eis::Random::Float() < 0.7f)
			continue;

		// mutate weight
		if (Eis::Random::Float() < 0.7f)
			n.SetWeight(Eis::Random::Float(-2.0f, 2.0f));

		// mutate hidden connections
		if (Eis::Random::Float() < 0.3f)
		{
			if (Eis::Random::Float() > 0.5f && n.connections.size() > 1)
				n.connections.erase(n.connections.begin() + Eis::Random::UInt(0, n.connections.size() - 1));
			else
			{
				uint32_t id = 0;
				while (id <= i && brain.GetHiddenCount() - i - 1 > n.connections.size())
				{
					id = Eis::Random::UInt(0, brain.GetHiddenCount() - 1);
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
		}

		// mutate out connections
		if (Eis::Random::Float() < 0.3f)
		{
			if (Eis::Random::Float() > 0.5f && n.connections.size() > 1)
				n.connections.erase(n.connections.begin() + Eis::Random::UInt(0, n.connections.size() - 1));
			else
			{
				uint32_t id = 0;
				while (id <= i && brain.GetHiddenCount() - i - 1 > n.connections.size())
				{
					id = Eis::Random::UInt(0, brain.GetHiddenCount() - 1);
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
		}
	}
}