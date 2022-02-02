#pragma once
#include "PhysicsObject.h"\

// A one-sided object, and it considered to extend infinity along 
// both sides of it's edge and backwards from it's normal direction

class Rigidbody;

class Plane : public PhysicsObject
{
public:
	Plane(glm::vec2 a_normal, float a_distanceToOrigin);
	Plane();
	~Plane();

	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep);
	virtual void MakeGizmo();
	virtual void Debug() {};
	virtual void ResetPosition() {};

	void ResolvePlaneCollision(Rigidbody* a_rigidbody, glm::vec2 a_contact);

	glm::vec2 GetNormal() { return m_normal; }
	float GetDistance() { return m_distanceToOrigin; }
	glm::vec4 GetColor() { return m_color; }


protected:
	glm::vec2 m_normal;
	float m_distanceToOrigin;
	glm::vec4 m_color;

};

