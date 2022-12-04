#include "Dot.h"

#include "../Env/Scene.h"

#include <iostream>
#include <Windows.h>

Dot::Dot(const Vec2<int>& pos, const char& id) : m_Pos(pos), m_Id(id)
{
}

void Dot::Move(const Vec2<int>& move, bool separateAxis)
{
	if (!separateAxis)
	{
		if (Scene::CheckPos(m_Pos + move))
			m_Pos += move;
	}
	else
	{
		if (Scene::CheckPos({ m_Pos.x + move.x, m_Pos.y }))
			m_Pos.x += move.x;
		if (Scene::CheckPos({ m_Pos.x, m_Pos.y + move.y }))
			m_Pos.y += move.y;
	}
}

void Dot::MoveAI()
{
	Inputs ins = { m_Pos };
	brain.SetInputs(ins);

	brain.Compute();

	Move(brain.GetActions().movement);
}