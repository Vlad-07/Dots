#pragma once

#include <cmath>

class Connection
{
public:
	Connection(uint32_t destID = 0, float _weight = 1.0f, bool _toAction = true) : weight(_weight), destinationID(destID), toAction(_toAction) {}
	~Connection() = default;

	void SetWeight(float _weight) { weight = _weight; }
	float GetWeight() const { return weight; }
	uint32_t GetDestinationID() const { return destinationID; }
	bool GetDestType() { return toAction; }

private:
	float weight;
	uint32_t destinationID;
	bool toAction;
};

class Neuron
{
public:
	Neuron() = default;
	~Neuron() = default;

	void ResetSignal() { signal = 0.0f; }
	void AddSignal(float _signal) { signal += _signal; }
	float GetSignal() const { return tanh(signal); }

protected:
	float signal;
};

class SensoryNeuron : public Neuron
{
public:
	SensoryNeuron() = default;
	~SensoryNeuron() = default;
};

class ActionNeuron : public Neuron
{
public:
	ActionNeuron() = default;
	~ActionNeuron() = default;
};