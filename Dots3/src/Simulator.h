#pragma once

#include <array>

#include "Dots/Dot.h"

// Params

const int DotNumber		= 50;
const int TicksPerGen	= 500;

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

class Simulator
{
public:
	Simulator();
	~Simulator() = default;

	void Init();

	void Step();

	void StepGen();

	bool CheckPosAvailable(glm::ivec2 pos);

	inline glm::ivec2 GetSize() const { return m_Size; }
	inline uint64_t GetTick() const { return m_Tick; }
	inline uint64_t GetGen() const { return m_Generation; }
	inline bool GetPause() const { return m_Pause; }
	inline auto GetDots() const { return m_Dots; }

	inline void SetPause(bool pause) { m_Pause = pause; }

private:
	std::array<Dot, DotNumber> m_Dots;
	glm::ivec2 m_Size;

	uint64_t m_Tick;
	uint64_t m_Generation;
	bool m_Pause;
};