#pragma once

#include <vector>

#include "Subject.h"


const int SubjectsPerGen = 50;
const int MaxTicksPerGen = 10000;
const int MaxIdleTicksAllowed = 500;

const int KeepBestXSubjects = 2;

const glm::vec2 SubjectStartPos(19.5f, 2.0f);
const float StartOrientation = 0.0f; // Radians

const int NetworkSaveInterval = 10; // Generations


class SubjectManager
{
public:
	SubjectManager(const std::vector<glm::vec2>& interiorLineNodes, const std::vector<glm::vec2>& exteriorLineNodes, const std::vector<Checkpoint>& checkpoints,
				   Eis::Ref<Eis::Texture2D> carTex);
	~SubjectManager() = default;

	void Update(Eis::TimeStep ts);

	void ResetSubjects();
	void UpdateSubjects(Eis::TimeStep ts);
	void EndGeneration();

	void ResetSimulation();

	int AliveSubjects() const;
	const Subject& GetBestSubject() const;
	int GetBestScore() const;

	void DrawBestNetwork() const { GetBestSubject().DrawNetwork(); }
	void SaveBestNetwork();
	void RemoveSaveFiles();

	void LoadSave(const std::string& path);
	void LoadBestSave();

	uint32_t GetGeneration() const { return m_Gen; }
	uint32_t GetTick() const { return m_Tick; }
	uint32_t GetTopScore() const { return m_TopScore; }

private:
	std::vector<Subject> m_Subjects;
	uint32_t m_Gen;
	uint32_t m_Tick;
	bool m_GenActive;

	uint32_t m_TopScore;
};