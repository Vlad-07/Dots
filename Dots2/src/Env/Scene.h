#pragma once

#include "../Dots/Dot.h"
#include "../Utils.h"


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
	inline static Vec2<int> GetSize() { return Scene::Get()->m_Size; }
	inline static Vec2<int> GetNrOfDots() { return Scene::Get()->m_NrOfDots; }

	void Update(bool heuristics = false);
	void DrawScene();

	static bool CheckPos(Vec2<int> pos);

private:
	void PrintDotsPos();

private:
	Vec2<int> m_Size;
	Dot* m_Dots;
	int m_NrOfDots;
	bool m_InternalDots;


	static Scene* s_Intance;
};