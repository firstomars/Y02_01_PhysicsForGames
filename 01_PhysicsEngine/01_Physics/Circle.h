#pragma once
#include "RigidBody.h"

//	RigidBody(ShapeType shapeID, glm::vec2 position,
//glm::vec2 velocity, float orientation, float mass);

class Circle : public RigidBody
{
public:
	Circle(glm::vec2 position, glm::vec2 velocity,
		float mass, float radius, glm::vec4 colour);
	~Circle();

	virtual void Draw();
	
	float GetRadius() { return m_radius; }
	glm::vec4 GetColour() { return m_colour; }

protected:
private:
	float m_radius;
	glm::vec4 m_colour;
};

