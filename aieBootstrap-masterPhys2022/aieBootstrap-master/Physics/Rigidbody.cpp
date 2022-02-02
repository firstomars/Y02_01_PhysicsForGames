#include "Rigidbody.h"
#include <glm/glm.hpp>

Rigidbody::Rigidbody(ShapeType a_shapeID, glm::vec2 a_position, 
	glm::vec2 a_velocity, float a_rotation, float a_mass) : PhysicsObject(a_shapeID)
{
	m_position = a_position;
	m_velocity = a_velocity;
	m_rotation = a_rotation;
	m_mass = a_mass;
	m_elasticity = 1;
	m_angularVelocity = 0;
}

void Rigidbody::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
	m_position += GetVelocity() * a_timeStep;
	ApplyForce(a_gravity * GetMass() * a_timeStep, glm::vec2(0));

	m_rotation += m_angularVelocity * a_timeStep;
}

void Rigidbody::ResolveCollision(Rigidbody* a_otherActor, glm::vec2 a_contact, glm::vec2* a_collisionNormal)
{
	//find vector between centres 
	//OR 
	//use the provided directional force - ensure it is normalised

	glm::vec2 normal = glm::normalize(
		a_collisionNormal ? *a_collisionNormal : 
		a_otherActor->GetPosition() - m_position);

	// get perpendicular vector to the collision normal
	glm::vec2 perpendicularColNorm(normal.y, -normal.x);

	float radiusThis = glm::dot(a_contact - m_position, -perpendicularColNorm);
	float radiusOther = glm::dot(a_contact - a_otherActor->GetPosition(), perpendicularColNorm);

	// the velocity of the contact points
	float cp_velocityThis = glm::dot(m_velocity, normal) - radiusThis * m_angularVelocity;
	float cp_velocityOther = glm::dot(a_otherActor->GetVelocity(), normal) 
		+ radiusOther * a_otherActor->GetAngularVelocity();

	if (cp_velocityThis > cp_velocityOther) //true - moving closer
	{
		//this will calculate the effective mass at the contact point for each object
		//ie. how much the contact point will move due to the forces applied

		float massThis = 1.0f / (1.0f / m_mass + 
			glm::pow(radiusThis, 2.0f) / m_moment);

		float massOther = 1.0f / (1.0f / a_otherActor->GetMass() + 
			glm::pow(radiusOther, 2.0f) / a_otherActor->GetMoment());

		float elasticity = (m_elasticity + a_otherActor->GetElasticity()) / 2.0f;

		glm::vec2 impact = ((1.0f + elasticity) * 
			massThis * massOther) / (massThis + massOther) * 
			(cp_velocityThis - cp_velocityOther) * 
			normal;

		ApplyForce(-impact, a_contact - m_position);
		a_otherActor->ApplyForce(impact, a_contact - a_otherActor->GetPosition());
	}
}

//void Rigidbody::ResolveCollision(Rigidbody* a_actor2)
//{
//	glm::vec2 normal = glm::normalize(a_actor2->GetPosition() - m_position);
//	glm::vec2 relativeVelocity = a_actor2->GetVelocity() - m_velocity;
//
//	float elasticity = 1;
//
//	//impulse magnitude
//	float j = glm::dot(-(1 + elasticity) * relativeVelocity, normal) / 
//		((1 / a_actor2->GetMass()) + (1 / m_mass));
//
//	glm::vec2 force = normal * j;
//
//	//calculate forces on objects
//	float kEPrevious = GetKineticEnergy();
//	float otherKePrevious = a_actor2->GetKineticEnergy();
//
//	//ApplyForceToActor(a_actor2, force);
//
//	//std::cout << "KE" << kEPrevious << std::endl;
//	//std::cout << "Other KE" << otherKePrevious << std::endl;
//}

void Rigidbody::ApplyForce(glm::vec2 a_force, glm::vec2 a_contact)
{
	m_velocity += a_force / GetMass();

	m_angularVelocity += (a_force.y * a_contact.x - a_force.x * a_contact.y) / GetMoment();
}

//void Rigidbody::ApplyForceToActor(Rigidbody* a_actor2, glm::vec2 a_force)
//{
//	ApplyForce(-a_force);
//	a_actor2->ApplyForce(a_force);
//}

float Rigidbody::GetKineticEnergy()
{
	//Ek = 0.5 * m * (v * v)
	float totalEnergy = (m_mass * glm::dot(m_velocity, m_velocity)) / 2;

	return totalEnergy;
}