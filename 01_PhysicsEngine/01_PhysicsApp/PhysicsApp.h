#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include <glm/glm.hpp>

class PhysicsApp : public aie::Application {
public:

	PhysicsApp();
	virtual ~PhysicsApp();

	virtual bool Startup();
	virtual void shutdown();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	//aie::Texture*		m_texture;
	//aie::Texture*		m_shipTexture;
	aie::Font*			m_font;

	PhysicsScene* m_physicsScene;

	float m_timer;
};