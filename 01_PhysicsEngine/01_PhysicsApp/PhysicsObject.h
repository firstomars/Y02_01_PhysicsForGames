#pragma once

#include <glm/glm.hpp>

//this is a pure abstract base class
//can’t construct an instance of this - can only be created by children classes
//class is too general.
//Classes derived from PhsyicsObject will have to provide
//implementtaions of fixedUpdateand draw in order to be constructable

class PhysicsObject
{
public:
	virtual void FixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void Draw() = 0;
	virtual void ResetPosition() {};

protected:
	PhysicsObject() {};

};

