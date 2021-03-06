#include <iostream>
#include <Gizmos.h>
#include <glm/ext.hpp>

#include "PhysicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Circle.h"
#include "Plane.h"

#define _USE_MATH_DEFINES
#include <math.h>


PhysicsApp::PhysicsApp() {

}

PhysicsApp::~PhysicsApp() {

}

bool PhysicsApp::startup() {

	// Increase the 2d line count to maximise the number
	// of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);
		
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();

	// The lower the value the more accurate the simulation will be,
	// but it will increase the processing time required. If it is too 
	// high it will cause the sim to stutter and reduce the stability.

	m_physicsScene->SetGravity(glm::vec2(0, 0));
	m_physicsScene->SetTimeStep(0.01f);

	//CollisionDetectionTest();

	CreateCircle();

	return true;
}

void PhysicsApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void PhysicsApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->Update(deltaTime);
	m_physicsScene->Draw();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16.f / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100,
		-100 / aspectRatio, 100 / aspectRatio, -1.f, 1.f));
	
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 15);

	// done drawing sprites
	m_2dRenderer->end();
}

void PhysicsApp::CreateCircle()
{
	//cue ball
	Circle* ball1 = new Circle(glm::vec2(-20, 0), glm::vec2(0, 0), 1.7f, 4.f,
		glm::vec4(1, 1, 1, 1));
	Circle* ball2 = new Circle(glm::vec2(10, 0), glm::vec2(0, 0), 1.6f, 4.f,
		glm::vec4(0, 1, 0, 1));

	m_physicsScene->AddActor(ball1);
	m_physicsScene->AddActor(ball2);

	ball1->ApplyForce(glm::vec2(20.0f, -20.0f), ball1->GetPosition());
	ball2->ApplyForce(glm::vec2(-20.f, -20.0f), ball2->GetPosition());

	Plane* plane = new Plane(glm::vec2(0, 1), -30);
	m_physicsScene->AddActor(plane);
}

void PhysicsApp::CollisionDetectionTest()
{
	//Circle* ball1 = new Circle(glm::vec2(-20, 0), glm::vec2(0, 0), 4.f, 4.f, glm::vec4(1, 0, 0, 1));
	//Circle* ball2 = new Circle(glm::vec2(10, 0),  glm::vec2(0, 0), 4.f, 4.f, glm::vec4(0, 1, 0, 1));
	//Plane* plane = new Plane(glm::vec2(0, 1), -30);

	//m_physicsScene->AddActor(ball1);
	//m_physicsScene->AddActor(ball2);
	//m_physicsScene->AddActor(plane);

}
