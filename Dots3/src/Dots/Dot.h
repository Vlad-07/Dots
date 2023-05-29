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
	Dot() : m_Pos(0), m_Brain() {}
	Dot(glm::ivec2 pos);
	Dot(glm::ivec2 pos, const Brain& brain);
	~Dot() = default;

	StepResponse Step();

	inline void Move(glm::ivec2 move) { m_Pos += move; }

	inline glm::ivec2 GetPos() const { return m_Pos; }
	inline Brain& GetBrain() { return m_Brain; }

	inline void SetPos(glm::ivec2 pos) { m_Pos = pos; }

private:
	Brain m_Brain;
	glm::ivec2 m_Pos;
};