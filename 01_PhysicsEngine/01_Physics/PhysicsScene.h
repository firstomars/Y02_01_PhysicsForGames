#pragma once

#include <glm/vec2.hpp>
#include <vector>
#include "PhysicsObject.h"



class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	void AddActor(PhysicsObject* actor);
	void RemoveActor(PhysicsObject* actor);
	void Update(float deltaTime);
	void Draw();

	void SetGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 GetGravity() const { return m_gravity; }

	void SetTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float GetTimeStep() { return m_timeStep; }

	static bool CircleToCircle(PhysicsObject* a_actor1, PhysicsObject* a_actor2);

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;

private:


};

