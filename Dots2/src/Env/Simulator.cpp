#include "Simulator.h"

#include <Eis.h>

#include <glm/gtc/random.hpp>

Simulator::Simulator(float xSize, float ySize, uint32_t nrOfDots, bool heuristics, const Combinator::MergeMethod mergeMethod)
	: m_Size(xSize, ySize), m_NrOfDots(nrOfDots), m_Heuristics(heuristics), m_MergingMethod(mergeMethod),
	  m_Pause(false), m_TickCount(1ull), m_GenerationCount(0u), m_SimulationPos(0.0f), m_DotRenderingRadius(1.0f), m_DotsSurvived(0u)
{
	for (uint32_t i = 0, id = 0; i < m_NrOfDots; i++, id++)
		m_Dots.push_back(Dot(glm::vec2(Eis::Random::UInt(0, m_Size.x), Eis::Random::UInt(0, m_Size.y)), id));
	// It is possible for the rand eng to produce the same coords twice
	// does not matter bc in the next iteration, one of the dots will move 
	// might cause problems the first frame
}

void Simulator::Update()
{
	// why use 2 bool safeguards when bits
	static uint8_t safeguard = 0b11;
	if (Eis::Input::IsKeyPressed(EIS_KEY_P))
	{
		if (safeguard & BIT(0))
			m_Pause = !m_Pause, safeguard ^= BIT(0);
	}
	else
		safeguard |= BIT(0);

	if (Eis::Input::IsKeyPressed(EIS_KEY_O))
	{
		if (safeguard & BIT(1))
		{
			safeguard ^= BIT(1);
			m_Pause = true;
			TickDots();
		}
	}
	else
		safeguard |= BIT(1);

	if (!m_Pause)
		TickDots();
}

void Simulator::DrawScene()
{
	for (const Dot& dot : m_Dots)
		Eis::Renderer2D::DrawCircle(dot.GetPos() + m_SimulationPos, glm::vec2(m_DotRenderingRadius), ((dot.GetPos().x < m_Size.x / 4) ? glm::vec4(0.2f, 0.8f, 0.3f, 1.0f) : glm::vec4(0.8f, 0.2f, 0.3f, 1.0f)));

/*
	float stride = 1.2f;

	for (int y = 0; y < m_Size.y; y++)
	{
		for (int x = 0; x < m_Size.x; x++)
		{
			glm::vec4 color = m_EmptyCellColor;
			for (int i = 0; i < Simulator::GetNrOfDots(); i++)
			{
				if (!m_Dots[i].drawn && (roundf(m_Dots[i].GetPos().x) == x && roundf(m_Dots[i].GetPos().y) == y))
				{
					color = m_CellColor;
					m_Dots[i].drawn = true;
					break;
				}
			}

			Eis::Renderer2D::DrawQuad({x * stride, -y * stride, 0.0f}, {1.0f, 1.0f}, color);
		}
	}

	for (int i = 0; i < Simulator::GetNrOfDots(); i++)
		m_Dots[i].drawn = false;*/
}

void Simulator::TickDots()
{
	m_TickCount++;
	if (m_Heuristics)
	{
		int moveX = Eis::Input::IsKeyPressed(EIS_KEY_RIGHT) - Eis::Input::IsKeyPressed(EIS_KEY_LEFT);
		int moveY = Eis::Input::IsKeyPressed(EIS_KEY_DOWN) - Eis::Input::IsKeyPressed(EIS_KEY_UP);
		m_Dots[0].Move(glm::vec2(moveX, moveY), *this);

		for (int i = 1; i < m_NrOfDots; i++)
			m_Dots[i].MoveAI(*this);
		return;
	}

	for (int i = 1; i < m_NrOfDots; i++)
		m_Dots[i].MoveAI(*this);
}

// OBSOLETE
/*void Simulator::DrawSceneConsole()
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
}*/

bool Simulator::CheckPos(glm::vec2 pos) const
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= m_Size.x || pos.y >= m_Size.y)
		return false;
	return true;
}

void Simulator::PrintDotsPos()
{
	for (int i = 0; i < Simulator::GetNrOfDots(); i++)
	{
		const Dot& dot = m_Dots[i];
		EIS_TRACE("{0}, {1}, {2}", dot.GetId(), dot.GetPos().x, dot.GetPos().y);
	}
	EIS_TRACE("");
}

void Simulator::NextGeneration()
{
	m_GenerationCount++;
	m_DotsSurvived = 0;
	RandomizeDotPositions();
	SelectDots();
	MutateDots();
}

void Simulator::SelectDots()
{
	for (Dot& dot : m_Dots)
	{
		dot.SetPassed(DotSelectionLaw(dot, *this));
		m_DotsSurvived += (uint32_t)dot.GetPassed();
	}
}

void Simulator::MutateDots()
{
	std::vector<Dot> newDots = m_Dots;
	for (Dot& dot : newDots)
	{
		uint32_t parent1 = -1, parent2 = -1;

		while (parent1 == -1)
		{
			parent1 = Eis::Random::UInt(0, m_Dots.size() - 1);
			if (!m_Dots[parent1].GetPassed())
				parent1 = -1;
		}

		while (parent2 == -1)
		{
			parent2 = Eis::Random::UInt(0, m_Dots.size() - 1);
			if (!m_Dots[parent2].GetPassed() || parent1 == parent2)
				parent2 = -1;
		}

		dot.SetBrain(Combinator::MergeBrains(m_Dots[parent1].GetBrain(), m_Dots[parent2].GetBrain(), m_MergingMethod));
	}
}

void Simulator::RandomizeDotPositions()
{
	for (Dot& dot : m_Dots)
		dot.SetPos(glm::vec2(Eis::Random::Float(0.0f, m_Size.x), Eis::Random::Float(0.0f, m_Size.y)));
}