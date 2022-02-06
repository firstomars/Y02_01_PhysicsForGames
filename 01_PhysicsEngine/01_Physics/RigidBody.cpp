#include "RigidBody.h"

RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position,
	glm::vec2 velocity, float orientation, float mass) : PhysicsObject(shapeID)
{
	m_shapeID = shapeID;
	m_position = position;
	m_velocity = velocity;
	m_orientation = orientation;
	m_mass = mass;
}

RigidBody::~RigidBody()
{

}

void RigidBody::FixedUpdate(glm::vec2 gravity, float timeStep)
{
	m_position += m_velocity * timeStep;
	ApplyForce(gravity * m_mass * timeStep);
}


void RigidBody::ApplyForce(glm::vec2 force)
{
	// newtown's second law
	// Applying a force to an object will either speed it up or slow it down. 
	// That is to say, applying a force will change the acceleration of an object.
	// By adding the acceleration to the current velocity, 
	// we find the object’s new velocity.
	//acceleration = force / mass

	glm::vec2 acceleration = force / m_mass;
	m_velocity += acceleration;
}

void RigidBody::ApplyForceToActor(RigidBody* actor2, glm::vec2 force)
{
	//The applyForceToActor() function prototype 
	//is a variation of the applyForce() function.
	//It allows us to simulate one actor “pushing” another.

	//to this RigidBody
	ApplyForce(-force);

	//to other RigidBody
	actor2->ApplyForce(force);
}
