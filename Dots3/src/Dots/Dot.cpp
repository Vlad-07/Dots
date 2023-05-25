#include "Dot.h"


Dot::Dot(glm::ivec2 pos) : m_Pos(pos), m_Brain() {}

Dot::Dot(glm::ivec2 pos, const Brain& brain) : m_Pos(pos), m_Brain(brain)
{
}

Dot::StepResponse Dot::Step()
{
	// Inputs
	Brain::Inputs inputs = { m_Pos.x, m_Pos.y };
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