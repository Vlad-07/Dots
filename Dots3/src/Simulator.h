#pragma once

#include <array>
#include <bitset>

#include "Dots/Dot.h"

// Params

const int DotNumber		= 100;
const int TicksPerGen	= 150;

const int SpaceSize		= 100; // square

// Constants

const glm::ivec2 MoveN ( 0,  1);
const glm::ivec2 MoveS ( 0, -1);
const glm::ivec2 MoveW (-1,  0);
const glm::ivec2 MoveE ( 1,  0);
const glm::ivec2 MoveNW(-1,  1);
const glm::ivec2 MoveNE( 1,  1);
const glm::ivec2 MoveSW(-1, -1);
const glm::ivec2 MoveSE( 1, -1);

//

extern bool SurvivalLaw(const Dot& dot);

class Simulator
{
public:
	Simulator();
	Simulator(Simulator&) = delete;
	Simulator(Simulator&&) = delete;
	~Simulator() = default;

	void Init();
	void FullReset();

	void Step();
	void StepGen();


	inline glm::ivec2 GetSize() const { return m_Size; }
	inline uint64_t GetTick() const { return m_Tick; }
	inline uint64_t GetGen() const { return m_Generation; }
	inline bool GetPause() const { return m_Pause; }
	inline auto GetDots() const { return m_Dots; }
	inline uint32_t GetLastGenSurviviorCnt() const { return m_LastGenSurvivorCount; }

	inline void SetPause(bool pause) { m_Pause = pause; }

	bool CheckPosAvailable(glm::ivec2 pos) const;

	static Simulator* GetInstance() { return s_Instance; }

private:
	// Defines the selection law
	int SelectDots();

private:
	static Simulator* s_Instance;

	std::array<Dot, DotNumber> m_Dots;
	std::bitset<DotNumber> m_DotSurvival;
	
	glm::ivec2 m_Size;

	uint64_t m_Tick;
	uint64_t m_Generation;
	uint32_t m_LastGenSurvivorCount;
	bool m_Pause;
};