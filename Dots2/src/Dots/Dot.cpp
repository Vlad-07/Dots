#include "Dot.h"

#include <Eis/Core/Random.h>

#include "../Env/Simulator.h"

// TODO: brain config more accesible
Dot::Dot(const glm::vec2& pos, const uint32_t& id) : m_Brain(3, 2, 10), m_Pos(pos), m_Id(id), m_Passed(false)
{
}

void Dot::Move(const glm::vec2& move, const Simulator& sim)
{
	if (sim.CheckPos(glm::vec2(m_Pos.x + move.x, m_Pos.y)))
		m_Pos.x += move.x;
	if (sim.CheckPos(glm::vec2(m_Pos.x, m_Pos.y + move.y)))
		m_Pos.y += move.y;
}

void Dot::MoveAI(const Simulator& sim)
{
	std::vector<float> inputs;
	inputs.push_back((m_Pos.x / sim.GetSize().x) * 2.0f - 1.0f); // x
	inputs.push_back((m_Pos.y / sim.GetSize().y) * 2.0f - 1.0f); // y
	inputs.push_back(Eis::Random::Float(-1.0f, 1.0f));			 // random

	m_Brain.SetInput(inputs);

	m_Brain.Compute();

	std::vector<float> actions = m_Brain.GetOutput();
	Move({ actions[0], actions[1] }, sim);
}