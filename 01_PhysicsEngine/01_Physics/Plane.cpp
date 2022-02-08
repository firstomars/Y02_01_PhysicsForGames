#include "Plane.h"

Plane::Plane(glm::vec2 a_normal, float a_distance) : PhysicsObject(PLANE)
{

}

Plane::~Plane()
{

}

void Plane::FixedUpdate(glm::vec2 gravity, float timeStep)
{

}

void Plane::Draw()
{
	float lineSegmentLength = 300;
	glm::vec2 centrePoint = m_normal * m_distanceToOrigin;

	glm::vec2 parallel = { m_normal.y, -m_normal.x };
	//glm::vec4 colourFade = m_colour;

}

void Plane::ResetPosition()
{

}