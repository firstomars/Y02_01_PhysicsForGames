#include "PhysicsScene.h"

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0,0))
{
	m_timeStep = 0.01f;
	m_gravity = { 0,0 };
}

PhysicsScene::~PhysicsScene()
{
	
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

void PhysicsScene::Update(float deltaTime)
{
	//calls update fn of each actor

	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto actor : m_actors) actor->FixedUpdate(m_gravity, m_timeStep);

		accumulatedTime -= m_timeStep;
	}
}

void PhysicsScene::Draw()
{
	//draw each object

	for (auto actor : m_actors) actor->Draw();

}

