#include "Dot.h"

#include "../Env/Scene.h"

#include <iostream>
#include <Windows.h>

Dot::Dot(Vec2<int> pos, char id) : m_Pos(pos), m_Id(id)
{
}

void Dot::Move(Vec2<int> move)
{
	if (Scene::CheckPos(m_Pos + move))
		m_Pos += move;
}

void Dot::MoveAI()
{
	Vec2<int> moveVec = Vec2<int>::Random(2, 2) * Vec2<int>(2, 2) - Vec2<int>(1, 1);

	// actual AI

	Move(moveVec);
}