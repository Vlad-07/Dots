#include "SubjectManager.h"

SubjectManager::SubjectManager(const std::vector<glm::vec2>& interiorLineNodes, const std::vector<glm::vec2>& exteriorLineNodes, const std::vector<Checkpoint>& checkpoints,
							   Eis::Ref<Eis::Texture2D> carTex)
	: m_Gen(0), m_Tick(0), m_TopScore(0), m_GenActive(true), m_Subjects(SubjectsPerGen,
	  Subject(interiorLineNodes, exteriorLineNodes, checkpoints, SubjectStartPos, StartOrientation, carTex))
{
	ResetSimulation();

	EIS_ASSERT(KeepBestXSubjects <= SubjectsPerGen, "Number of subjects to be kept must be smaller than the total subject number!");
}


void SubjectManager::Update(Eis::TimeStep ts)
{
	EIS_PROFILE_FUNCTION();

	for (Subject& subject : m_Subjects)
		if (subject.GetTicksNotAdvancing() > MaxIdleTicksAllowed)
			subject.Kill();

	if (AliveSubjects() == 0 || m_Tick > MaxTicksPerGen)
	{
		EndGeneration();
		return;
	}

	m_GenActive = true;
	m_Tick++;

	UpdateSubjects(ts);
}

void SubjectManager::UpdateSubjects(Eis::TimeStep ts)
{
	EIS_PROFILE_FUNCTION();

	for (Subject& subject : m_Subjects)
		subject.Tick(ts);
}

bool SubjectSortFn(const Subject& s1, const Subject& s2)
{
	return s1.GetScore() > s2.GetScore();
}

void SubjectManager::EndGeneration()
{
	m_GenActive = false;
	m_Gen++;
	m_Tick = 0;

	std::sort(m_Subjects.begin(), m_Subjects.end(), SubjectSortFn);

	int sum = 0;
	int passingBrainNr = 0;
	for (const Subject& s : m_Subjects)
	{
		if (s.GetScore() > 0) // Filtering brains who didn't hit a single checkpoint 
		{
			passingBrainNr++;
			sum += s.GetScore();
			if (s.GetScore() > m_TopScore)
				m_TopScore = s.GetScore();
		}
		else
			break;
	}

	if (passingBrainNr == 0)
	{
		ResetSimulation();
		return;
	}

	float det = 1.0f / sum;

	Brain* brains = (Brain*)calloc(passingBrainNr, sizeof(Brain));
	if (brains == nullptr)
	{
		EIS_CRITICAL("Insufficient memory!");
		return;
	}

	for (int i = 0; i < passingBrainNr; i++)
		brains[i] = m_Subjects[i].GetBrain();


	for (int i = KeepBestXSubjects; i < m_Subjects.size(); i++)
	{
		float r1 = Eis::Random::Float();
		float r2 = Eis::Random::Float();

		int b1Id = 0, b2Id = 0;
		for (int j = passingBrainNr - 1; j >= 0; j--)
		{
			if (r1 < m_Subjects[j].GetScore() * det)
			{
				b1Id = j;
				break;
			}
		}
		for (int j = passingBrainNr - 1; j >= 0; j--)
		{
			if (r2 < m_Subjects[j].GetScore() * det)
			{
				b2Id = j;
				break;
			}
		}
		
		m_Subjects[i].GetCar().SetTint(glm::vec4((m_Subjects[b1Id].GetCar().GetTint() + m_Subjects[b2Id].GetCar().GetTint()) / 2.0f));
		m_Subjects[i].GetCar().SetTint(m_Subjects[i].GetCar().GetTint() + glm::vec4(Eis::Random::Vec3(-0.2f, 0.2f), 1.0f));
		m_Subjects[i].GetBrain().Merge(brains[b1Id], brains[b2Id]);
	}

	ResetSubjects();

	free(brains);
}

void SubjectManager::ResetSimulation()
{
	ResetSubjects();
	for (Subject& subject : m_Subjects)
	{
		subject.GetBrain().FullyRandomize();
		subject.GetCar().SetTint(glm::vec4(Eis::Random::Vec3(0.0f, 1.0f), 1.0f));
	}

	m_Gen = 0;
	m_Tick = 0;
	m_TopScore = 0;
	m_GenActive = false;
}

void SubjectManager::ResetSubjects()
{
	for (Subject& subject : m_Subjects)
		subject.Reset();
}

int SubjectManager::AliveSubjects() const
{
	int count = 0;
	for (const Subject& s : m_Subjects)
		count += s.IsAlive();
	return count;
}

int SubjectManager::GetBestScore() const
{
	int bestScore = INT_MIN;
	for (const Subject& s : m_Subjects)
		if (s.GetScore() > bestScore)
			bestScore = s.GetScore();
	return bestScore;
}

void SubjectManager::DrawBestNetwork() const
{
	int bestScore = GetBestScore();
	for (int i = 0; i < m_Subjects.size(); i++)
	{
		if (m_Subjects[i].GetScore() == bestScore)
		{
			m_Subjects[i].DrawNetwork();
			break;
		}
	}
}