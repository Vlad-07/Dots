#include "Simulator.h"

// HACK: Eis.h includes max macro definition, wich breaks glm random functions
#include <Eis/Core/Log.h>
#include <Eis/Core/Core.h>
#include <Eis/Core/Random.h>
#include <Eis/Input/Input.h>
#include <Eis/Input/Keycodes.h>
#include <Eis/Renderer/Renderer/Renderer2D.h>

#include <glm/gtc/random.hpp>

#include <iostream> // TODO: remove iostream

Simulator* Simulator::s_Intance = nullptr;

Simulator::Simulator(int xSize, int ySize, int nrOfDots, bool heuristics, bool randomStartPoses)
	: m_Size(xSize, ySize), m_NrOfDots(nrOfDots), m_InternalDots(true), m_Heuristics(heuristics), m_Pause(false), m_TickCount(0)
{
	if (s_Intance)
		EIS_ASSERT(false, "Simulator already exists!");
	Simulator::s_Intance = this;

	m_Dots = new Dot[nrOfDots];

	if (randomStartPoses)
		for (uint32_t i = 0, id = 0; i < m_NrOfDots; i++, id++)
			m_Dots[i] = Dot(glm::vec2(Eis::Random::UInt(0, m_Size.x), Eis::Random::UInt(0, m_Size.y)), id);
	// It is possible for the rand eng to produce the same coords twice
	// does not matter bc in the next iteration, one of the dots will move 
	// might cause problems the first frame
	
	PrintDotsPos();
}

Simulator::Simulator(int xSize, int ySize, int nrOfDots, bool heuristics, Dot* dots)
	: m_Size(xSize, ySize), m_NrOfDots(nrOfDots), m_Dots(dots), m_InternalDots(false), m_Heuristics(heuristics), m_Pause(false), m_TickCount(0)
{
	if (s_Intance)
		DebugBreak();
	Simulator::s_Intance = this;
}

Simulator::~Simulator()
{
	if (m_InternalDots)
		delete[] m_Dots;
	Simulator::s_Intance = nullptr;
}

void Simulator::Update()
{
	// why use 2 separate bool safeguards when you can use bits
	static char safeguard = 0b11;
	if (Eis::Input::IsKeyPressed(EIS_KEY_P))
	{
		if (safeguard & 0b01)
			m_Pause = !m_Pause, safeguard ^= 0b01;
	}
	else
		safeguard |= 0b01;

	if (Eis::Input::IsKeyPressed(EIS_KEY_O))
	{
		if (safeguard & 0b10)
		{
			safeguard ^= 0b10;
			if (!m_Pause)
				m_Pause = true;
			TickDots();
		}
	}
	else
		safeguard |= 0b10;

	if (!m_Pause)
		TickDots();
}

void Simulator::DrawScene()
{
	// TODO: Simulator::DrawScene() - slow implementation
	
	float stride = 1.2f;

	for (int y = 0; y < m_Size.y; y++)
	{
		for (int x = 0; x < m_Size.x; x++)
		{
			glm::vec4 color = m_EmptyCellColor;
			for (int i = 0; i < Simulator::GetNrOfDots(); i++)
				if (!m_Dots[i].drawn && (m_Dots[i].GetPos().x == x && m_Dots[i].GetPos().y == y))
				{
					color = m_CellColor;
					m_Dots[i].drawn = true;
					break;
				}

			Eis::Renderer2D::DrawQuad({x * stride, -y * stride, 0.0f}, {1.0f, 1.0f}, color);
		}
	}

	for (int i = 0; i < Simulator::GetNrOfDots(); i++)
		m_Dots[i].drawn = false;
}

void Simulator::TickDots()
{
	m_TickCount++;
	if (m_Heuristics)
	{
		int moveX = Eis::Input::IsKeyPressed(EIS_KEY_RIGHT) - Eis::Input::IsKeyPressed(EIS_KEY_LEFT);
		int moveY = Eis::Input::IsKeyPressed(EIS_KEY_DOWN) - Eis::Input::IsKeyPressed(EIS_KEY_UP);

		Simulator::Get()->m_Dots[0].Move({ moveX, moveY});
		for (int i = 1; i < Simulator::Get()->m_NrOfDots; i++)
			Simulator::Get()->m_Dots[i].MoveAI();
		return;
	}

	for (int i = 1; i < Simulator::Get()->m_NrOfDots; i++)
		Simulator::Get()->m_Dots[i].MoveAI();
}

// OBSOLETE
void Simulator::DrawSceneConsole() 
{	
	char* scene = new char[m_Size.x * m_Size.y];

	for (int i = 0; i < m_Size.x * m_Size.y; i++)
		scene[i] = ' ';

	for (int i = 0; i < m_NrOfDots; i++)
	{
		const Dot& dot = m_Dots[i];
		scene[(int)(dot.GetPos().y * m_Size.x + dot.GetPos().x)] = dot.GetId();
	}

	for (int i = 0; i < m_Size.x + 2; i++)
		std::cout << '_';
	std::cout << '\n';

	for (int j = 0; j < m_Size.y; j++)
	{
		std::cout << '|';
		for (int i = 0; i < m_Size.x; i++)
			std::cout << scene[j * (int)m_Size.x + i];
		std::cout << "|\n";
	}

	std::cout << '|';
	for (int i = 0; i < m_Size.x; i++)
		std::cout << '_';
	std::cout << "|\n";
	

	PrintDotsPos();

	delete[] scene;
}

bool Simulator::CheckPos(glm::vec2 pos)
{
	if (pos.x < 0 || pos.y < 0)
		return false;

	if (pos.x >= Simulator::Get()->m_Size.x || pos.y >= Simulator::Get()->m_Size.y)
		return false;

	for (int i = 0; i < Simulator::Get()->m_NrOfDots; i++)
	{
		if (Simulator::Get()->m_Dots[i].GetPos() == pos)
			return false;
	}
	return true;
}

void Simulator::PrintDotsPos()
{
	for (int i = 0; i < Simulator::GetNrOfDots(); i++)
	{
		const Dot& dot = m_Dots[i];
		std::cout << dot.GetId() << ' ' << dot.GetPos().x << ' ' << dot.GetPos().y << '\n';
	}
	std::cout << '\n';
}