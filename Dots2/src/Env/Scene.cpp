#include "Scene.h"

#include <iostream>
#include <Windows.h>

Scene* Scene::s_Intance = nullptr;

Scene::Scene(int xSize, int ySize, int nrOfDots, bool randomStartPoses) : m_Size(xSize, ySize), m_NrOfDots(nrOfDots), m_InternalDots(true)
{
	if (s_Intance)
		DebugBreak();
	Scene::s_Intance = this;

	m_Dots = new Dot[nrOfDots];

	if (randomStartPoses)
		for (int i = 0, id = 'a'; i < m_NrOfDots; i++, id++)
			m_Dots[i] = Dot(Vec2<int>::Random(m_Size.x, m_Size.y), id);
	PrintDotsPos();
}

Scene::Scene(int xSize, int ySize, int nrOfDots, Dot* dots) : m_Size(xSize, ySize), m_NrOfDots(nrOfDots), m_Dots(dots), m_InternalDots(false)
{
	if (s_Intance)
		DebugBreak();
	Scene::s_Intance = this;
}

Scene::~Scene()
{
	if (m_InternalDots)
		delete[] m_Dots;
	Scene::s_Intance = nullptr;
}

void Scene::Update(bool heuristics)
{
	if (heuristics)
	{
		int moveX = 0; short code1 = (GetKeyState(0x41) - GetKeyState(0x44));
		if (code1 > 1) // wierd toggle stuff
			moveX = 1;
		else if (code1 < -1)
			moveX = -1;

		int moveY = 0; short code2 = (GetKeyState(0x57) - GetKeyState(0x53));
		if (code2 > 1)
			moveY = 1;
		else if (code2 < -1)
			moveY = -1;

		Scene::Get()->m_Dots[0].Move({ moveX, moveY });
		for (int i = 1; i < Scene::Get()->m_NrOfDots; i++)
			Scene::Get()->m_Dots[i].MoveAI();
		return;
	}

	for (int i = 1; i < Scene::Get()->m_NrOfDots; i++)
		Scene::Get()->m_Dots[i].MoveAI();
}

void Scene::DrawScene()
{	
	char* scene = new char[m_Size.x * m_Size.y];

	for (int i = 0; i < m_Size.x * m_Size.y; i++)
		scene[i] = ' ';

	for (int i = 0; i < m_NrOfDots; i++)
	{
		const Dot& dot = m_Dots[i];
		scene[dot.GetPos().y * m_Size.x + dot.GetPos().x] = dot.GetId();
	}

	for (int i = 0; i < m_Size.x + 2; i++)
		std::cout << '_';
	std::cout << '\n';

	for (int j = 0; j < m_Size.y; j++)
	{
		std::cout << '|';
		for (int i = 0; i < m_Size.x; i++)
			std::cout << scene[j * m_Size.x + i];
		std::cout << "|\n";
	}

	std::cout << '|';
	for (int i = 0; i < m_Size.x; i++)
		std::cout << '_';
	std::cout << "|\n";

	PrintDotsPos();

	delete[] scene;
}

bool Scene::CheckPos(Vec2<int> pos)
{
	if (pos.x < 0 || pos.y < 0)
		return false;

	if (pos.x >= Scene::Get()->m_Size.x || pos.y >= Scene::Get()->m_Size.y)
		return false;

	for (int i = 0; i < Scene::Get()->m_NrOfDots; i++)
	{
		if (Scene::Get()->m_Dots[i].GetPos() == pos)
			return false;
	}
	return true;
}

void Scene::PrintDotsPos()
{
	for (int i = 0; i < Scene::Get()->m_NrOfDots; i++)
	{
		const Dot& dot = m_Dots[i];
		std::cout << dot.GetId() << ' ' << dot.GetPos().x << ' ' << dot.GetPos().y << '\n';
	}
	std::cout << '\n';
}