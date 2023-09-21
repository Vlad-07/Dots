#pragma once

#include "../Car/Car.h"
#include "Brain.h"

#include <array>

struct Checkpoint
{
	glm::vec2 start, end;
};

class Subject
{
public:
	Subject(const std::vector<glm::vec2>& interiorLineNodes, const std::vector<glm::vec2>& exteriorLineNodes, const std::vector<Checkpoint>& checkpoints,
			const glm::vec2& startPos, const float& startOrientation, Eis::Ref<Eis::Texture2D> carTex);
	~Subject() = default;

	void Tick(Eis::TimeStep ts);
	

	void Reset();
	void Kill() { m_Alive = false; }


	bool IsAlive() const { return m_Alive; }
	int GetScore() const { return m_Score; }
	Car& GetCar() { return m_Car; }
	Brain& GetBrain() { return m_Brain; }
	const Car& GetCar() const { return m_Car; }
	const Brain& GetBrain() const { return m_Brain; }
	uint32_t GetTicksNotAdvancing() const { return m_TicksNotAdvancing; }

	void DrawNetwork() const;

	Subject& operator=(const Subject& s);

private:
	bool CheckCarCollision();
	void ReadSensors();

private:
	Car m_Car;
	Brain m_Brain;
	bool m_Alive;

	glm::vec2 m_StartPos;
	float m_StartOrientation;

	const std::vector<glm::vec2>& m_InteriorLineNodes;
	const std::vector<glm::vec2>& m_ExteriorLineNodes;
	const std::vector<Checkpoint>& m_Checkpoints;

	int m_Score;
	uint32_t m_NextCheckpointID;

	uint32_t m_TicksNotAdvancing;

	std::array<float, 5> m_RaySensorInputs;
	const float m_MaxRayDist = 10.0f;
	const int m_CheckpointValue = 10;
};