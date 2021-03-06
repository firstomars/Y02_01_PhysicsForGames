#pragma once
#include "Rigidbody.h"
class Circle : public Rigidbody
{
public:
	Circle(glm::vec2 a_position, glm::vec2 a_velocity,
		float a_mass, float a_radius, glm::vec4 a_color);
	~Circle();
	virtual void MakeGizmo();
	bool CheckCollision(PhysicsObject* a_pOther);

	float GetRadius() { return m_radius; }
	glm::vec4 GetColor() { return m_color; }

protected:
	float m_radius;
	glm::vec4 m_color;
};

