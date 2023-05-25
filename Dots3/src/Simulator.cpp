#include "Simulator.h"

Simulator::Simulator() : m_Tick(0), m_Generation(0), m_Size(SpaceSize), m_Pause(false) {}

void Simulator::Init()
{
	for (int i = 0; i < DotNumber; i++)
	{
		glm::ivec2 pos = glm::ivec2(-1);
		while (!CheckPosAvailable(pos))
			pos = glm::ivec2(Eis::Random::UInt(0, SpaceSize), Eis::Random::UInt(0, SpaceSize));

		m_Dots[i] = Dot(pos);
	}
}

void Simulator::Step()
{
	// Pause and step management
	{
		static uint8_t safeguard = 0b11;
		if (Eis::Input::IsKeyPressed(EIS_KEY_P))
		{
			if (safeguard & BIT(0))
				m_Pause = !m_Pause, safeguard ^= BIT(0);
		}
		else
			safeguard |= BIT(0);

		if (Eis::Input::IsKeyPressed(EIS_KEY_O))
		{
			if (safeguard & BIT(1))
			{
				safeguard ^= BIT(1);
				m_Pause = true;
				goto _Step;
			}
		}
		else
			safeguard |= BIT(1);

		if (m_Pause)
			return;

		_Step:;
	}

	m_Tick++;

	for (Dot& dot : m_Dots)
	{
		Dot::StepResponse response = dot.Step();

		if (response.HasExecuted)
			continue;

		switch (response.Action)
		{
		case Dot::StepResponse::DesiredAction::MoveN:
			if (CheckPosAvailable(dot.GetPos() + MoveN))
				dot.Move(MoveN);
			break;
		case Dot::StepResponse::DesiredAction::MoveS:
			if (CheckPosAvailable(dot.GetPos() + MoveS))
				dot.Move(MoveS);
			break;
		case Dot::StepResponse::DesiredAction::MoveW:
			if (CheckPosAvailable(dot.GetPos() + MoveW))
				dot.Move(MoveW);
			break;
		case Dot::StepResponse::DesiredAction::MoveE:
			if (CheckPosAvailable(dot.GetPos() + MoveE))
				dot.Move(MoveE);
			break;

		case Dot::StepResponse::DesiredAction::MoveNW:
			if (CheckPosAvailable(dot.GetPos() + MoveNW))
				dot.Move(MoveNW);
			break;
		case Dot::StepResponse::DesiredAction::MoveNE:
			if (CheckPosAvailable(dot.GetPos() + MoveNE))
				dot.Move(MoveNE);
			break;
		case Dot::StepResponse::DesiredAction::MoveSW:
			if (CheckPosAvailable(dot.GetPos() + MoveSW))
				dot.Move(MoveSW);
			break;
		case Dot::StepResponse::DesiredAction::MoveSE:
			if (CheckPosAvailable(dot.GetPos() + MoveSE))
				dot.Move(MoveSE);
			break;
		}
	}
}

void Simulator::StepGen()
{
	m_Generation++;

	// Genetic Evolution
	//     Create new dots
	//     Discard old ones

	// TEMP
	for (int i = 0; i < DotNumber; i++)
	{
		glm::ivec2 pos = glm::ivec2(-1);
		while (!CheckPosAvailable(pos))
			pos = glm::ivec2(Eis::Random::UInt(0, SpaceSize), Eis::Random::UInt(0, SpaceSize));

		m_Dots[i] = Dot(pos);
	}
}


bool Simulator::CheckPosAvailable(glm::ivec2 pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= m_Size.x || pos.y >= m_Size.y)
		return false;

	for (const Dot& dot : m_Dots)
		if (dot.GetPos() == pos)
			return false;
	return true;
}