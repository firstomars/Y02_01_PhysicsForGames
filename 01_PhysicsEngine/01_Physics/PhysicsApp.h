#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include "Circle.h"
#include "Input.h"

class PhysicsApp : public aie::Application {
public:

	PhysicsApp();
	virtual ~PhysicsApp();

	virtual bool startup();
	void SceneRocket();
	void SceneCircleCollision();
	virtual void shutdown();

	virtual void update(float deltaTime);
	void ApplyRocketExhaust();
	void SetRocketDirection(aie::Input* input);
	virtual void draw();

protected:
private:
	void OnKeyPress();

protected:

	aie::Renderer2D*	m_2dRenderer;
	//aie::Texture*		m_texture;
	//aie::Texture*		m_shipTexture;
	aie::Font*			m_font;

	PhysicsScene* m_physicsScene;

	float m_timer;

private:
	Circle* circleTest1;
	Circle* circleTest2;
	Circle* circleTest3;

	float m_direction;
};