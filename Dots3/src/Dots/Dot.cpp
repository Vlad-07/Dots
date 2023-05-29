#include "Dot.h"

#include "../Simulator.h"

Dot::Dot(glm::ivec2 pos) : m_Pos(pos), m_Brain() {}

Dot::Dot(glm::ivec2 pos, const Brain& brain) : m_Pos(pos), m_Brain(brain) {}

Dot::StepResponse Dot::Step()
{
	// Inputs
	Brain::Inputs inputs{};
	inputs.SetInput(0u, (float)m_Pos.x / (float)Simulator::GetInstance()->GetSize().x);
	inputs.SetInput(1u, (float)m_Pos.y / (float)Simulator::GetInstance()->GetSize().y);
	inputs.SetInput(2u, Eis::Random::Float(-1.0f, 1.0f));
	inputs.SetInput(3u, (Simulator::GetInstance()->GetTick() % 2) * 2.0f - 1.0f);
	inputs.SetInput(4u, (inputs.GetProcessedIput(0u) <= 0.5f ? (inputs.GetProcessedIput(0u) * 2.0f) : ((1.0f - inputs.GetProcessedIput(0u)) * 2.0f))); // middle is 1, near border is 0
	inputs.SetInput(5u, (inputs.GetProcessedIput(1u) <= 0.5f ? (inputs.GetProcessedIput(1u) * 2.0f) : ((1.0f - inputs.GetProcessedIput(1u)) * 2.0f))); // same
	inputs.SetInput(6u, (inputs.GetProcessedIput(4u) < inputs.GetProcessedIput(5u) ? inputs.GetProcessedIput(4u) : inputs.GetProcessedIput(5u)));
	m_Brain.SetInputs(inputs);

	// Take action
	switch (m_Brain.Compute())
	{
	case Brain::Action::None:
		return StepResponse{ true, StepResponse::DesiredAction::Other };
	case Brain::Action::MoveN:
		return StepResponse{ false, StepResponse::DesiredAction::MoveN };
	case Brain::Action::MoveS:
		return StepResponse{ false, StepResponse::DesiredAction::MoveS };
	case Brain::Action::MoveW:
		return StepResponse{ false, StepResponse::DesiredAction::MoveW };
	case Brain::Action::MoveE:
		return StepResponse{ false, StepResponse::DesiredAction::MoveE };
	case Brain::Action::MoveNW:
		return StepResponse{ false, StepResponse::DesiredAction::MoveNW };
	case Brain::Action::MoveNE:
		return StepResponse{ false, StepResponse::DesiredAction::MoveNE };
	case Brain::Action::MoveSW:
		return StepResponse{ false, StepResponse::DesiredAction::MoveSW };
	case Brain::Action::MoveSE:
		return StepResponse{ false, StepResponse::DesiredAction::MoveSE };
	}
}