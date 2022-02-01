#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Particle.h"


class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;

	float m_timer;
	float m_fixedTimeStep = 0.1f;
	float m_accumulatedTime;

private:
	Particle* m_particle;
	Particle* m_particle1;

};