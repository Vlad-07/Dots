#pragma once

#include <glm/glm.hpp>

#include "../Dots/Dot.h"

//  x+ ->
// y+
// |

class Scene
{
public:
	Scene(int xSize, int ySize, int nrOfDots, bool randomStartPoses = true);
	Scene(int xSize, int ySize, int nrOfDots, Dot* dots);
	~Scene();

	inline static Scene* Get() { return s_Intance; }
	inline static glm::vec2 GetSize() { return Scene::Get()->m_Size; }
	inline static int GetNrOfDots() { return Scene::Get()->m_NrOfDots; }

	void Update(bool heuristics = false);
	void DrawScene();

	// OBSOLETE
	void DrawSceneConsole();

	static bool CheckPos(glm::vec2 pos);

private:
	void PrintDotsPos();

private:
	glm::vec2 m_Size;
	Dot* m_Dots;
	int m_NrOfDots;
	bool m_InternalDots;

	static Scene* s_Intance;

	
	const glm::vec4 m_EmptyCellColor{ 0.3f, 0.3f, 0.3f, 1.0f };
	const glm::vec4 m_CellColor{ 0.3f, 0.8f, 0.25f, 1.0f };
}; 