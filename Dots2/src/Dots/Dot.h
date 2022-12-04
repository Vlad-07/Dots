#pragma once

#include "Brain.h"
#include "../Utils.h"

class Dot
{
public:
	Dot() = default;
	Dot(const Vec2<int>& pos, const char& id);
	~Dot() = default;

	void Move(const Vec2<int>& move, bool separateAxis = false);
	void MoveAI();

	void SetPos(const Vec2<int>& pos) { m_Pos = pos; }
	inline Vec2<int> GetPos() const { return m_Pos; }
	inline char GetId() const { return m_Id; }

private:
	Brain brain;
	Vec2<int> m_Pos;
	char m_Id;
};