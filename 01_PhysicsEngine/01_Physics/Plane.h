#pragma once
#include "PhysicsObject.h"
#include "glm/glm.hpp"

class Plane : public PhysicsObject
{
public:
	Plane(glm::vec2 a_normal, float a_distance);
	~Plane();

	virtual void FixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void Draw();
	virtual void ResetPosition();

	glm::vec2 GetNormal() { return m_normal; }
	float GetDistToOrigin() { return m_distanceToOrigin; }

protected:
	glm::vec2 m_normal;
	float m_distanceToOrigin;

private:
};

