#pragma once

#include <Eis.h>
#include <glm/glm.hpp>

class Car // Verlet Integration 2D Car
{
public:
	Car() = default;
	Car(const glm::vec2& size, Eis::Ref<Eis::Texture2D> texture, const glm::vec4& tint, const float& power, const float& brakePower, const float& topSpeed, const float& turnRate, bool computerControll);
	~Car() = default;

	void Update(Eis::TimeStep ts);
	void Render() const;
	void UserInput(Eis::TimeStep ts);
	void ComputerInput(Eis::TimeStep ts, float acceleration, float steering);

	glm::vec2 GetPosition() const { return m_Pos; }
	glm::vec2 GetSize() const { return m_Size; }
	float GetOrientation() const { return 6.2831853f - m_Orientation; }
	float GetSpeed() const { return glm::length(m_Velocity) * 10.0f; }
	glm::vec4 GetTint() const { return m_Tint; }

	void Stop() { m_Velocity = m_Acceleration = glm::vec2(0.0f); }
	void SetPos(const glm::vec2& pos) { m_Pos = pos; }
	void SetOrientation(float radians) { m_Orientation = radians; }
	void SetTint(const glm::vec4& tint) { m_Tint = tint; }

	Car& operator=(const Car& car);

private:
	float Slowdown();
	float TurnRate();

private:
	glm::vec2 m_Pos;
	glm::vec2 m_Velocity;
	glm::vec2 m_Acceleration;
	float m_Orientation;

	glm::vec2 m_Size;
	Eis::Ref<Eis::Texture2D> m_Texture;
	glm::vec4 m_Tint;
	float m_Power;
	float m_BrakePower;
	float m_TopSpeed;
	float m_TurnRateMultiplier;
	bool m_ComputerControlled;
};