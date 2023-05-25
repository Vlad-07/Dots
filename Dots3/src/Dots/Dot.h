#pragma once

#include <glm/glm.hpp>

#include "Brain.h"

class Dot
{
public:

	struct StepResponse
	{
		enum DesiredAction
		{
			Other = 0, MoveN, MoveS, MoveW, MoveE, MoveNW, MoveNE, MoveSW, MoveSE
		};
		
		bool HasExecuted;
		DesiredAction Action;
	};

public:
	Dot() = default;
	Dot(glm::ivec2 pos);
	Dot(glm::ivec2 pos, const Brain& brain);
	~Dot() = default;

	StepResponse Step();

	inline void Move(glm::ivec2 move) { m_Pos += move; }

	inline glm::ivec2 GetPos() const { return m_Pos; }

private:
	glm::ivec2 m_Pos;

	Brain m_Brain;
};