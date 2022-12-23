#include "Brain.h"

#include <glm/gtc/random.hpp>

#include <Eis/Core/Log.h>

void Brain::SetInputs(Inputs in)
{
	m_CurrentFrameInput = in;
}

void Brain::Compute()
{
	// Actual AI

	glm::vec2 tmp = glm::ivec2(glm::diskRand(1.0f) * 2.0f);


	m_Actions = {tmp};

	m_Computed = true;
}

Actions Brain::GetActions()
{
	if (!m_Computed)
		EIS_WARN("Actions not computed!");
	m_Computed = false;
	return m_Actions;
}