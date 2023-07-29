#include "Car.h"

#include <glm/gtx/rotate_vector.hpp>

#include <cmath>

Car::Car(const glm::vec2& size, Eis::Ref<Eis::Texture2D> texture, const glm::vec4& tint, const float& power, const float& brakePower, const float& topSpeed, const float& turnRateMultiplier, bool computerControll)
	: m_Size(size), m_Texture(texture), m_Power(power), m_BrakePower(brakePower), m_TopSpeed(topSpeed), m_TurnRateMultiplier(turnRateMultiplier), m_ComputerControlled(computerControll),
	  m_Tint(tint), m_Pos(0.0f), m_Velocity(0.0f), m_Orientation(0.0f), m_Acceleration(0.0f)
{}


void Car::Update(Eis::TimeStep ts)
{
	glm::vec2 lastPos = m_Pos;

	if (GetSpeed() < 0.005f && (m_Acceleration.x == 0.0f && m_Acceleration.y == 0.0f))
		m_Velocity = glm::vec2(0.0f);

	m_Pos += m_Velocity * Slowdown() + m_Acceleration * ts.GetSeconds();
	m_Acceleration = glm::vec2(0.0f);

	m_Velocity = m_Pos - lastPos;
}

void Car::Render() const
{
	Eis::Renderer2D::DrawRotatedQuad(m_Pos, m_Size, m_Orientation, m_Texture, m_Tint);
}


void Car::UserInput(Eis::TimeStep ts)
{
	if (Eis::Input::IsKeyPressed(EIS_KEY_W) && GetSpeed() < m_TopSpeed)
		m_Acceleration += glm::rotate(glm::vec2(0.0f, m_Power * ts), m_Orientation);
	if (Eis::Input::IsKeyPressed(EIS_KEY_S))
		m_Velocity *= 0.99f;

	if (Eis::Input::IsKeyPressed(EIS_KEY_A))
	{
		m_Orientation += TurnRate() * ts;
		if (m_Orientation > 6.2831853f)
			m_Orientation -= 6.2831853f;

		m_Velocity = glm::rotate(glm::vec2(0.0f, glm::length(m_Velocity)), m_Orientation);
	}
	if (Eis::Input::IsKeyPressed(EIS_KEY_D))
	{
		m_Orientation -= TurnRate() * ts;
		if (m_Orientation < 0.0f)
			m_Orientation += 6.2831853f;

		m_Velocity = glm::rotate(glm::vec2(0.0f, glm::length(m_Velocity)), m_Orientation);
	}
}

void Car::ComputerInput(Eis::TimeStep ts, float acceleration, float steering)
{
	if (acceleration > 0.5f && GetSpeed() < m_TopSpeed)
		m_Acceleration += glm::rotate(glm::vec2(0.0f, m_Power * ts), m_Orientation);
	else if (acceleration < 0.5f)
		m_Velocity *= 0.99f;

	if (steering > 0.5f)
	{
		m_Orientation += TurnRate() * ts;
		if (m_Orientation > 6.2831853f)
			m_Orientation -= 6.2831853f;

		m_Velocity = glm::rotate(glm::vec2(0.0f, glm::length(m_Velocity)), m_Orientation);
	}
	else if (steering < 0.5f)
	{
		m_Orientation -= TurnRate() * ts;
		if (m_Orientation < 0.0f)
			m_Orientation += 6.2831853f;

		m_Velocity = glm::rotate(glm::vec2(0.0f, glm::length(m_Velocity)), m_Orientation);
	}
}



Car& Car::operator=(const Car& car)
{
	m_Size = car.m_Size;
	m_Texture = car.m_Texture;
	m_Tint = car.m_Tint;
	m_Pos = car.m_Pos;
	m_Velocity = car.m_Velocity;
	m_Acceleration = car.m_Acceleration;
	m_Orientation = car.m_Orientation;
	m_Power = car.m_Power;
	m_BrakePower = car.m_BrakePower;
	m_TopSpeed = car.m_TopSpeed;
	m_TurnRateMultiplier = car.m_TurnRateMultiplier;
	m_ComputerControlled = car.m_ComputerControlled;

	return *this;
}

float Car::Slowdown()
{
	if (m_Acceleration.x || m_Acceleration.y)
		return 1.0f;

	return 0.995f;
}

float Car::TurnRate()
{
	float speed = GetSpeed();

	if (speed < 0.01f)
		return 0.0f;

	return 2.5f / coshf(speed / 3) * m_TurnRateMultiplier;
}