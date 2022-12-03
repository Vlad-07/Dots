#pragma once

#include "../Utils.h"

class Dot
{
public:
	Dot() = default;
	Dot(Vec2<int> pos, char id);
	~Dot() = default;

	void Move(Vec2<int> move);
	void MoveAI();

	void SetPos(Vec2<int> pos) { m_Pos = pos; }
	inline Vec2<int> GetPos() const { return m_Pos; }
	inline char GetId() const { return m_Id; }

private:
	Vec2<int> m_Pos;
	char m_Id;
};