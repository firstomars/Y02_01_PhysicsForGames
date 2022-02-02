#include "Particle.h"
#include "Application2D.h"

Particle::Particle(glm::vec2 pos, float radius)
{
	m_radius = radius;
	m_position = pos;
	m_velocity = { 0 , 0 };
	m_gravity = 0;
}

Particle::~Particle()
{

}

void Particle::Update(float delta)
{
	m_position += m_velocity * delta;
	m_velocity.y += m_gravity * delta;
}

void Particle::Render(aie::Renderer2D* m_2dRenderer)
{
	m_2dRenderer->setRenderColour(1, 1, 1, 1);
	m_2dRenderer->drawCircle(m_position.x, m_position.y, m_radius);
}

