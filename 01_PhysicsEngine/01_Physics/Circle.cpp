#include "Circle.h"
#include "Gizmos.h"

//(ShapeType shapeID, glm::vec2 position,
//glm::vec2 velocity, float orientation, float mass)


Circle::Circle(glm::vec2 position, glm::vec2 velocity,
	float mass, float radius, glm::vec4 colour) :
	RigidBody(CIRCLE, position, velocity, 0, mass)
{
	m_radius = radius;
	m_colour = colour;
}

Circle::~Circle()
{

}

void Circle::Draw()
{
	//As shape sub-classes require a different type of gizmo 
	//to represent them visually, 
	//it makes sense to provide them with unique draw() functions

	//unsure if this is correct
	aie::Gizmos::add2DCircle(GetPosition(), m_radius, 12, m_colour);
}