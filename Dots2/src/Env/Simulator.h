#pragma once

#include <glm/glm.hpp>

#include "../Dots/Dot.h"

//  x+ ->
// y+
// |

class Simulator
{
public:
	Simulator(int xSize, int ySize, int nrOfDots, bool heuristics, bool randomStartPoses = true);
	Simulator(int xSize, int ySize, int nrOfDots, bool heuristics, Dot* dots);
	~Simulator();

	inline static Simulator* Get() { return s_Intance; }
	inline static glm::vec2 GetSize() { return Simulator::Get()->m_Size; }
	inline static int GetNrOfDots() { return Simulator::Get()->m_NrOfDots; }
	inline static bool GetState() { return Simulator::Get()->m_Pause; }
	inline static uint32_t GetTick() { return Simulator::Get()->m_TickCount; }

	void Update();
	void DrawScene();

	// OBSOLETE
	void DrawSceneConsole();

	static bool CheckPos(glm::vec2 pos);

private:
	void TickDots();
	void PrintDotsPos();

private:
	glm::vec2 m_Size;
	Dot* m_Dots;
	int m_NrOfDots;
	bool m_InternalDots;
	bool m_Heuristics;
	bool m_Pause;

	uint32_t m_TickCount;

	static Simulator* s_Intance;

	
	const glm::vec4 m_EmptyCellColor{ 0.3f, 0.3f, 0.3f, 1.0f };
	const glm::vec4 m_CellColor{ 0.3f, 0.8f, 0.25f, 1.0f };
}; 