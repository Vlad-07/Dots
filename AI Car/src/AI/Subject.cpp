#include "Subject.h"

#include <glm/gtx/rotate_vector.hpp>

Subject::Subject(const std::vector<glm::vec2>& interiorLineNodes, const std::vector<glm::vec2>& exteriorLineNodes, const std::vector<Checkpoint>& checkpoints,
				 const glm::vec2& startPos, const float& startOrientation, Eis::Ref<Eis::Texture2D> carTex)
	: m_Car(glm::vec2(0.5f, 1.0f), carTex, glm::vec4(Eis::Random::Vec3(0.0f, 1.0f), 1.0f), 5.0f, 3.0f, 3.0f, 1.0f, false), m_Alive(true),
	  m_InteriorLineNodes(interiorLineNodes), m_ExteriorLineNodes(exteriorLineNodes),m_Checkpoints(checkpoints),
	  m_StartPos(startPos), m_StartOrientation(startOrientation), m_Score(0), m_NextCheckpointID(0), m_TicksNotAdvancing(0), m_RaySensorInputs(), m_DebugMode(false)
{}


void Subject::Tick(Eis::TimeStep ts)
{
	m_Alive = !CheckCarCollision() && m_Alive;

	if (!m_Alive)
		return;

	ReadSensors();

	m_Brain.ResetNetwork();

	m_Brain.SetSensorInput(0, glm::length(m_Car.GetSpeed()) / 3.0f);	// Velocity
	for (int i = 0; i < 5; i++)											// Rays
		m_Brain.SetSensorInput(i + 2, m_RaySensorInputs[i] / m_MaxRayDist);
	m_Brain.SetSensorInput(5, 1.0f);									// Bias

	m_Brain.Compute();

	m_Car.ComputerInput(ts, m_Brain.GetActionNeuronOutput(0), m_Brain.GetActionNeuronOutput(1));
	m_Car.Update(ts);
	m_Car.Render();


	m_TicksNotAdvancing++;
}

void Subject::Reset()
{
	m_Alive = true;
	m_Score = 0;
	m_NextCheckpointID = 0;
	m_TicksNotAdvancing = 0;
	m_Car.Stop();
	m_Car.SetPos(m_StartPos);
	m_Car.SetOrientation(m_StartOrientation);
}

glm::vec2 IntersectionPoint(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4)
{
	// Store the values for fast access and easy
	// equations-to-code conversion
	float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
	float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0) return glm::vec2(FLT_MAX);

	// Get the x and y
	float pre = (x1 * y2 - y1 * x2), post = (x3 * y4 - y3 * x4);
	float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
	float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

	// Check if the x and y coordinates are within both lines
	if (x < std::min(x1, x2) || x > std::max(x1, x2) || x < std::min(x3, x4) || x > std::max(x3, x4))
		return glm::vec2(FLT_MAX);

	if (y < std::min(y1, y2) || y > std::max(y1, y2) || y < std::min(y3, y4) || y > std::max(y3, y4))
		return glm::vec2(FLT_MAX);

	// Return the point of intersection

	return glm::vec2(x, y);
}

bool Subject::CheckCarCollision()
{
	glm::vec2 carCorner1 = m_Car.GetPosition() + glm::rotate(m_Car.GetSize() * glm::vec2(0.5f, 0.5f), -m_Car.GetOrientation());
	glm::vec2 carCorner2 = m_Car.GetPosition() + glm::rotate(m_Car.GetSize() * glm::vec2(0.5f, -0.5f), -m_Car.GetOrientation());
	glm::vec2 carCorner3 = m_Car.GetPosition() + glm::rotate(m_Car.GetSize() * glm::vec2(-0.5f, -0.5f), -m_Car.GetOrientation());
	glm::vec2 carCorner4 = m_Car.GetPosition() + glm::rotate(m_Car.GetSize() * glm::vec2(-0.5f, 0.5f), -m_Car.GetOrientation());

	// Draw car bounding box
	if (m_DebugMode && m_Alive)
	{
		Eis::Renderer2D::DrawLine(carCorner1, carCorner2, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
		Eis::Renderer2D::DrawLine(carCorner2, carCorner3, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		Eis::Renderer2D::DrawLine(carCorner3, carCorner4, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		Eis::Renderer2D::DrawLine(carCorner4, carCorner1, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	}	

	// Check checkpoint
	if (IntersectionPoint(m_Checkpoints[m_NextCheckpointID].start, m_Checkpoints[m_NextCheckpointID].end, carCorner1, carCorner2) != glm::vec2(FLT_MAX))
	{
		m_Score += m_CheckpointValue;
		m_NextCheckpointID++;
		m_TicksNotAdvancing = 0;
	}
	else if (IntersectionPoint(m_Checkpoints[m_NextCheckpointID].start, m_Checkpoints[m_NextCheckpointID].end, carCorner2, carCorner3) != glm::vec2(FLT_MAX))
	{
		m_Score += m_CheckpointValue;
		m_NextCheckpointID++;
		m_TicksNotAdvancing = 0;
	}
	else if (IntersectionPoint(m_Checkpoints[m_NextCheckpointID].start, m_Checkpoints[m_NextCheckpointID].end, carCorner3, carCorner4) != glm::vec2(FLT_MAX))
	{
		m_Score += m_CheckpointValue;
		m_NextCheckpointID++;
		m_TicksNotAdvancing = 0;
	}
	else if (IntersectionPoint(m_Checkpoints[m_NextCheckpointID].start, m_Checkpoints[m_NextCheckpointID].end, carCorner4, carCorner1) != glm::vec2(FLT_MAX))
	{
		m_Score += m_CheckpointValue;
		m_NextCheckpointID++;
		m_TicksNotAdvancing = 0;
	}

	m_NextCheckpointID %= m_Checkpoints.size();

	// Inner Fence
	for (int i = 1; i < m_InteriorLineNodes.size(); i++)
	{
		if (IntersectionPoint(m_InteriorLineNodes[i - 1], m_InteriorLineNodes[i], carCorner1, carCorner2) != glm::vec2(FLT_MAX))
			return true;
		if (IntersectionPoint(m_InteriorLineNodes[i - 1], m_InteriorLineNodes[i], carCorner2, carCorner3) != glm::vec2(FLT_MAX))
			return true;
		if (IntersectionPoint(m_InteriorLineNodes[i - 1], m_InteriorLineNodes[i], carCorner3, carCorner4) != glm::vec2(FLT_MAX))
			return true;
		if (IntersectionPoint(m_InteriorLineNodes[i - 1], m_InteriorLineNodes[i], carCorner4, carCorner1) != glm::vec2(FLT_MAX))
			return true;
	}
	if (IntersectionPoint(m_InteriorLineNodes.front(), m_InteriorLineNodes.back(), carCorner1, carCorner2) != glm::vec2(FLT_MAX))
		return true;
	if (IntersectionPoint(m_InteriorLineNodes.front(), m_InteriorLineNodes.back(), carCorner2, carCorner3) != glm::vec2(FLT_MAX))
		return true;
	if (IntersectionPoint(m_InteriorLineNodes.front(), m_InteriorLineNodes.back(), carCorner3, carCorner4) != glm::vec2(FLT_MAX))
		return true;
	if (IntersectionPoint(m_InteriorLineNodes.front(), m_InteriorLineNodes.back(), carCorner4, carCorner1) != glm::vec2(FLT_MAX))
		return true;

	// Outer Fence
	for (int i = 1; i < m_ExteriorLineNodes.size(); i++)
	{
		if (IntersectionPoint(m_ExteriorLineNodes[i - 1], m_ExteriorLineNodes[i], carCorner1, carCorner2) != glm::vec2(FLT_MAX))
			return true;
		if (IntersectionPoint(m_ExteriorLineNodes[i - 1], m_ExteriorLineNodes[i], carCorner2, carCorner3) != glm::vec2(FLT_MAX))
			return true;
		if (IntersectionPoint(m_ExteriorLineNodes[i - 1], m_ExteriorLineNodes[i], carCorner3, carCorner4) != glm::vec2(FLT_MAX))
			return true;
		if (IntersectionPoint(m_ExteriorLineNodes[i - 1], m_ExteriorLineNodes[i], carCorner4, carCorner1) != glm::vec2(FLT_MAX))
			return true;
	}
	if (IntersectionPoint(m_ExteriorLineNodes.front(), m_ExteriorLineNodes.back(), carCorner1, carCorner2) != glm::vec2(FLT_MAX))
		return true;
	if (IntersectionPoint(m_ExteriorLineNodes.front(), m_ExteriorLineNodes.back(), carCorner2, carCorner3) != glm::vec2(FLT_MAX))
		return true;
	if (IntersectionPoint(m_ExteriorLineNodes.front(), m_ExteriorLineNodes.back(), carCorner3, carCorner4) != glm::vec2(FLT_MAX))
		return true;
	if (IntersectionPoint(m_ExteriorLineNodes.front(), m_ExteriorLineNodes.back(), carCorner4, carCorner1) != glm::vec2(FLT_MAX))
		return true;

	return false;
}

void Subject::ReadSensors()
{
	float angle = -60.0f;
	for (int i = 0; i < 5; i++, angle += 30.0f)
	{
		glm::vec2 rayOrigin = m_Car.GetPosition();
		glm::vec2 rayEnd = rayOrigin + glm::rotate(glm::vec2(0.0f, m_MaxRayDist), -m_Car.GetOrientation() + glm::radians(angle));


		glm::vec2 intP(0.0f);
		for (int i = 1; i < m_InteriorLineNodes.size(); i++)
		{
			intP = IntersectionPoint(m_InteriorLineNodes[i - 1], m_InteriorLineNodes[i], rayOrigin, rayEnd);
			if (intP != glm::vec2(FLT_MAX))
				goto _found;
		}
		intP = IntersectionPoint(m_InteriorLineNodes.front(), m_InteriorLineNodes.back(), rayOrigin, rayEnd);
		if (intP != glm::vec2(FLT_MAX))
			goto _found;

		// Outer Fence
		for (int i = 1; i < m_ExteriorLineNodes.size(); i++)
		{
			intP = IntersectionPoint(m_ExteriorLineNodes[i - 1], m_ExteriorLineNodes[i], rayOrigin, rayEnd);
			if (intP != glm::vec2(FLT_MAX))
				goto _found;
		}
		intP = IntersectionPoint(m_ExteriorLineNodes.front(), m_ExteriorLineNodes.back(), rayOrigin, rayEnd);
		if (intP != glm::vec2(FLT_MAX))
			goto _found;

		m_RaySensorInputs[i] = m_MaxRayDist;

		if (m_DebugMode)
			Eis::Renderer2D::DrawLine(rayOrigin, rayEnd, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		continue;

	_found:
		m_RaySensorInputs[i] = glm::distance(rayOrigin, intP);
		if (m_DebugMode)
			Eis::Renderer2D::DrawLine(rayOrigin, intP, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	}
}

void Subject::DrawNetwork() const
{
	glm::vec2 bottomRightCorner(25.0f, 2.0f);
	const auto& conns = m_Brain.GetConnections();

	for (int i = 0; i < conns.size(); i++)
	{
		for (int j = 0; j < conns[0].size(); j++)
		{
			Eis::Renderer2D::DrawLine({ bottomRightCorner.x, bottomRightCorner.y + i * 2 }, { bottomRightCorner.x + 10.0f, bottomRightCorner.y + 6.0f + m_Brain.GetConnections()[i][j].GetDestinationID() * 2 },
				glm::vec4((conns[i][j].GetWeight() > 0 ? 1.0f : 0.0f), 0.0f, (conns[i][j].GetWeight() < 0 ? 1.0f : 0.0f), 1.0f));
		}

		Eis::Renderer2D::DrawCircle({ bottomRightCorner.x, bottomRightCorner.y + i * 2 }, glm::vec2(0.5f),
			glm::vec4(glm::vec3(m_Brain.GetSensoryNeurons()[i].GetSignal() > 0.0f ? m_Brain.GetSensoryNeurons()[i].GetSignal() : 0.0f, 0.0f,
								m_Brain.GetSensoryNeurons()[i].GetSignal() < 0.0f ? m_Brain.GetSensoryNeurons()[i].GetSignal() : 0.0f), 1.0f));
	}

	for (int i = 0; i < conns[0].size(); i++)
	{
		Eis::Renderer2D::DrawCircle({ bottomRightCorner.x + 10.0f, bottomRightCorner.y + 6.0f + i * 2 }, glm::vec2(0.5f),
			glm::vec4(glm::vec3(m_Brain.GetSensoryNeurons()[i].GetSignal() > 0.0f ? m_Brain.GetSensoryNeurons()[i].GetSignal() : 0.0f, 0.0f,
								m_Brain.GetSensoryNeurons()[i].GetSignal() < 0.0f ? m_Brain.GetSensoryNeurons()[i].GetSignal() : 0.0f), 1.0f));
	}
}

Subject& Subject::operator=(const Subject& s)
{
	m_Car = s.m_Car;
	m_Brain = s.m_Brain;
	m_Alive = s.m_Alive;
	m_StartPos = s.m_StartPos;
	m_StartOrientation = s.m_StartOrientation;
	m_Score = s.m_Score;
	m_NextCheckpointID = s.m_NextCheckpointID;
	m_TicksNotAdvancing = s.m_TicksNotAdvancing;

	return *this;
}