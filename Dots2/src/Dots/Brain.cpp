#include "Brain.h"

#include <iostream>

void Brain::SetInputs(Inputs in)
{
	m_CurrentFrameInput = in;
}

void Brain::Compute()
{
	// Actual AI

	m_Actions = { Vec2<int>::Random(2, 2) * Vec2<int>(2) - Vec2<int>(1) };

	m_Computed = true;
}

Actions Brain::GetActions()
{
	if (!m_Computed)
		std::cout << "W - Not computed!!\n\n";
	m_Computed = false;
	return m_Actions;
}