#pragma once

#include <glm/glm.hpp>

#include "Brain.h"

class Dot
{
public:
	Dot() = default;
	Dot(const glm::vec2& pos, const uint32_t& id);
	~Dot() = default;

	void Move(const glm::vec2& move, bool separateAxis = false);
	void MoveAI();

	void SetPos(const glm::vec2& pos) { m_Pos = pos; }
	inline glm::vec2 GetPos() const { return m_Pos; }
	inline uint32_t GetId() const { return m_Id; }

private:
	Brain brain;
	glm::vec2 m_Pos;
	uint32_t m_Id;

public:
	bool drawn = false; // TEMP
};