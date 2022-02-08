#include "PhysicsScene.h"
#include "Circle.h"
#include <iostream>

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0,0))
{

}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}

void PhysicsScene::AddActor(PhysicsObject* actor)
{
	m_actors.push_back(actor);
}

void PhysicsScene::RemoveActor(PhysicsObject* actor)
{
	auto it = std::find(m_actors.begin(), m_actors.end(), actor);
	if (it != m_actors.end()) m_actors.erase(it);
}

//function pointer array for doing our collisions
typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] =
{
	PhysicsScene::Plane2Plane,	PhysicsScene::Plane2Sphere,
	PhysicsScene::CircleToPlane, PhysicsScene::Circle2Circle,
};

void PhysicsScene::Update(float deltaTime)
{
	static float accumulatedTime = 0.0f;
	
	//is deltaTime the amount of time passed in the last frame?
	accumulatedTime += deltaTime;

	//update physics of objects at a fixed time step
	while (accumulatedTime >= m_timeStep)
	{
		//calls update fn of each actor
		for (auto actor : m_actors) actor->FixedUpdate(m_gravity, m_timeStep);

		accumulatedTime -= m_timeStep;

		//check for collissions
		int actorCount = m_actors.size();

		//need to check for collissions against all objects except this one
		for (int outer = 0; outer < actorCount - 1; outer++)
		{
			for (int inner = outer + 1; inner < actorCount; inner++)
			{
				PhysicsObject* actor1 = m_actors[outer];
				PhysicsObject* actor2 = m_actors[inner];

				//assuming both shapes are circles
				CircleToCircle(actor1, actor2);
			}
		}
			
	}
}

void PhysicsScene::Draw()
{
	//draw each object
	for (auto actor : m_actors) actor->Draw();

}

bool PhysicsScene::CircleToCircle(PhysicsObject* a_actor1, PhysicsObject* a_actor2)
{
	//dynamic cast actors 1 and 2 into circles (i.e. circle check)
	Circle* circle1 = dynamic_cast<Circle*>(a_actor1);
	Circle* circle2 = dynamic_cast<Circle*>(a_actor2);

	//if both actors are circles
	if (circle1 != nullptr && circle2 != nullptr)
	{
		//collission check
		
		glm::vec2 pos1 = circle1->GetPosition();
		glm::vec2 pos2 = circle2->GetPosition();
		
		//if distance between the centres is less than combined radii
		if (glm::distance(pos1, pos2) < 
			(circle1->GetRadius() + circle2->GetRadius()))
		{
			circle1->ApplyForce(-(circle1->GetVelocity()));
			circle2->ApplyForce(-(circle2->GetVelocity()));

			return true;
		}

		// TODO if the spheres touch, set their velocities to zero for now
	}
	return false;
}
