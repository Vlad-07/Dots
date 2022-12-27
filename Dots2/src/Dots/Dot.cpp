#include "Dot.h"

#include "../Env/Simulator.h"

Dot::Dot(const glm::vec2& pos, const uint32_t& id) : m_Pos(pos), m_Id(id)
{
}

void Dot::Move(const glm::vec2& move, bool separateAxis)
{
	if (!separateAxis)
	{
		if (Simulator::CheckPos(m_Pos + move))
			m_Pos += move;
	}
	else
	{
		if (Simulator::CheckPos({ m_Pos.x + move.x, m_Pos.y }))
			m_Pos.x += move.x;
		if (Simulator::CheckPos({ m_Pos.x, m_Pos.y + move.y }))
			m_Pos.y += move.y;
	}
}

void Dot::MoveAI()
{
	Inputs ins = { m_Pos };
	brain.SetInputs(ins);

	brain.Compute();

	Actions actions = brain.GetActions();
	Move(actions.movement);
}