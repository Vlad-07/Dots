#include "Brain.h"

#include <glm/gtc/random.hpp>

void Brain::SetInputs(Inputs in)
{
	m_CurrentFrameInput = in;
}

void Brain::Compute()
{
	// Actual AI

	m_Actions = {glm::circularRand(1)};

	m_Computed = true;
}

Actions Brain::GetActions()
{
//	if (!m_Computed)
//		std::cout << "W - Not computed!!\n\n";
	m_Computed = false;
	return m_Actions;
}