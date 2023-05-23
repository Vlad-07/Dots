#pragma once

#include <glm/glm.hpp>

#include "../Dots/Dot.h"

// SUS: y axis
//  x+ ->
// y+
// |
// simulator space from 0 to size


extern bool DotSelectionLaw(const Dot& dot, const Simulator& sim);


class Simulator
{
public:
	Simulator(float xSize, float ySize, uint32_t nrOfDots, bool heuristics, const Combinator::MergeMethod mergeMethod = Combinator::SingleCut);
	~Simulator() = default;

	inline glm::vec2 GetSize() const { return m_Size; }
	inline std::vector<Dot>& GetDots() { return m_Dots; }
	inline int GetNrOfDots() const { return m_NrOfDots; }
	inline bool GetState() const { return m_Pause; }
	inline uint64_t GetTick() const { return m_TickCount; }
	inline uint32_t GetGeneration() const { return m_GenerationCount; }
	inline float GetDotRenderingRadius() const { return m_DotRenderingRadius; }
	inline uint32_t GetSurvivorCount() const { return m_DotsSurvived; }

	inline void SetSimPos(const glm::vec2& pos) { m_SimulationPos = pos; }
	inline void SetState(bool pause) { m_Pause = pause; }

	void Update();
	void DrawScene();
	void PrintDotsPos();
	void NextGeneration();
	void SelectDots();

	void MutateDots();
	void RandomizeDotPositions();

	bool CheckPos(glm::vec2 pos) const;

	// OBSOLETE\
	void DrawSceneConsole();

private:
	void TickDots();

private:
	glm::vec2 m_SimulationPos;
	glm::vec2 m_Size;
	std::vector<Dot> m_Dots;
	uint32_t m_NrOfDots;
	bool m_Heuristics;
	bool m_Pause;
	Combinator::MergeMethod m_MergingMethod;

	float m_DotRenderingRadius;

	uint64_t m_TickCount;
	uint32_t m_GenerationCount;

	uint32_t m_DotsSurvived;
	
	const glm::vec4 m_EmptyCellColor{ 0.3f, 0.3f, 0.3f, 1.0f };
	const glm::vec4 m_CellColor{ 0.3f, 0.8f, 0.25f, 1.0f };
};