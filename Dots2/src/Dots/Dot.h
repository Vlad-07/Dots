#pragma once

#include <glm/glm.hpp>

#include "AI/AI.h"

extern class Simulator; // SUS: might cause trouble

class Dot
{
public:
	Dot() = default;
	Dot(const glm::vec2& pos, const uint32_t& id);
	~Dot() = default;

	void Move(const glm::vec2& move, const Simulator& sim);
	void MoveAI(const Simulator& sim);

	void SetBrain(const Brain& brain) { m_Brain = brain; }
	void SetPos(const glm::vec2& pos) { m_Pos = pos; }

	inline glm::vec2 GetPos() const { return m_Pos; }
	inline uint32_t GetId() const { return m_Id; }
	inline Brain& GetBrain() { return m_Brain; }

	void SetPassed(bool passed) { m_Passed = passed; }
	inline bool GetPassed() const { return m_Passed; }

private:
	Brain m_Brain;
	glm::vec2 m_Pos;
	uint32_t m_Id;

	// SUS: maybe reconsider the selection system
	bool m_Passed;
};