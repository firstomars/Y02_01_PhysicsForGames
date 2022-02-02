#pragma once
#include "PhysicsObject.h"
#include <iostream>
#include <functional>
#include <glm/glm.hpp>

class Rigidbody : public PhysicsObject
{
public:
	Rigidbody(ShapeType a_shapeID, glm::vec2 a_position,
		glm::vec2 a_velocity, float a_rotation, float a_mass);
	~Rigidbody() {};

	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep);
	virtual void Debug()
	{ std::cout << "position: " << m_position.x << ', ' <<
			m_position.y << std::endl; }

	//===
	//COLLISION RESOLUTION 
	//void ResolveCollision(Rigidbody* a_actor2);
	void ResolveCollision(Rigidbody* a_otherActor, glm::vec2 a_contact,
		glm::vec2* a_collisionNormal = nullptr);
	
	virtual bool CheckCollision(PhysicsObject* pOther) = 0;

	void ApplyForce(glm::vec2 a_force, glm::vec2 a_contact);
	//void ApplyForceToActor(Rigidbody* a_actor2, glm::vec2 a_force);


	glm::vec2 GetPosition() { return m_position; }
	glm::vec2 GetVelocity() { return m_velocity; }
	float GetRotation() { return m_rotation; }
	float GetMass() { return m_mass; }

	float GetKineticEnergy();
	float GetAngularVelocity() { return m_angularVelocity; }
	float GetMoment() { return m_moment; }

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_rotation;
	float m_mass;
	float m_angularVelocity;
	float m_moment;
};

