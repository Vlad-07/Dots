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

	inline glm::vec2 GetSize() const { return m_Size; }
	inline int GetNrOfDots() const { return m_NrOfDots; }
	inline bool GetState() const { return m_Pause; }
	inline uint32_t GetTick() const { return m_TickCount; }

	void Update();
	void DrawScene();
	void PrintDotsPos();

	// OBSOLETE
	void DrawSceneConsole();

	bool CheckPos(glm::vec2 pos) const;

private:
	void TickDots();

private:
	glm::vec2 m_Size;
	Dot* m_Dots;
	int m_NrOfDots;
	bool m_InternalDots;
	bool m_Heuristics;
	bool m_Pause;

	uint32_t m_TickCount;
	
	const glm::vec4 m_EmptyCellColor{ 0.3f, 0.3f, 0.3f, 1.0f };
	const glm::vec4 m_CellColor{ 0.3f, 0.8f, 0.25f, 1.0f };
}; 