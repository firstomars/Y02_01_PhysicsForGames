#include <Gizmos.h>
#include "Circle.h"
#include <glm\ext.hpp>

Circle::Circle(glm::vec2 a_position, glm::vec2 a_velocity, 
	float a_mass, float a_radius, glm::vec4 a_color) :
	Rigidbody(CIRCLE, a_position, a_velocity, 0, a_mass)
{
	m_radius = a_radius;
	m_color	 = a_color;
}

Circle::~Circle()
{
}

void Circle::MakeGizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_color);
}

bool Circle::CheckCollision(PhysicsObject* a_pOther)
{
	/*Circle* pCircle = dynamic_cast<Circle*>(a_pOther);
	if (pCircle != nullptr)
	{
		float dist = glm::distance(m_position, pCircle->m_position);
		if (m_radius + pCircle->m_radius > dist)
			return true;
	}
*/
	return false;
}
