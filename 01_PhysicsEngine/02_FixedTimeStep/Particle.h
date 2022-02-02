#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "glm/glm.hpp"

class Particle
{
	
public:
	Particle(glm::vec2 pos, float radius);
	~Particle();

	void Update(float delta);
	void Render(aie::Renderer2D* m_2dRenderer);
	void SetGravity(float gravity) { m_gravity = gravity; };

	glm::vec2 m_velocity;

protected:
private:
	glm::vec2 m_position;
	float m_radius;
	float m_gravity;
};

