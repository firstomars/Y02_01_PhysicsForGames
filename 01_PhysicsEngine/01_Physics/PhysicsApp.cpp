#include "PhysicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"
#include <glm/ext.hpp>
#include <iostream>


//TUTORIAL COLLISION DETECTION PAGE 5

PhysicsApp::PhysicsApp() 
{

}

PhysicsApp::~PhysicsApp() 
{

}

bool PhysicsApp::startup() 
{
	//increase the 2D line count to maximize the no . of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	setBackgroundColour(250, 235, 215);
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	//create new physics scene and set timestep
	m_physicsScene = new PhysicsScene();
	m_physicsScene->SetGravity(glm::vec2(0, 0));

	//TIMESTEP NOTES
	/*
	//smaller timestep value = 
	//higher accuracy 
	//increased processing power

	//larger timestep value = 
	//smaller accuracy (simulation will stutter)
	//lower stability
	//lower processing power
	*/
	m_physicsScene->SetTimeStep(0.01f);

	//circle collision
	SceneCircleCollision();

	//rocket circle
	SceneRocket();

	m_timer = 0;
	m_direction = 0;

	return true;
}

void PhysicsApp::shutdown() {
	
	delete m_font;
	delete m_2dRenderer;
}

void PhysicsApp::update(float deltaTime) 
{
	// input example
	aie::Input* input = aie::Input::getInstance();
	
	//set rocket direction
	SetRocketDirection(input);

	//rocket exhaust application
	m_timer += deltaTime;
	if (m_timer > 1) 
	{
		ApplyRocketExhaust();
		m_timer = 0;
	}

	aie::Gizmos::clear();
	m_physicsScene->Update(deltaTime);
	m_physicsScene->Draw();

	if (input->isKeyDown(aie::INPUT_KEY_SPACE)) OnKeyPress();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE)) quit();
}

void PhysicsApp::draw() 
{
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	//draw stuff here
	static float aspectRatio = 16 / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100,
		-100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	//m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}

void PhysicsApp::OnKeyPress()
{
	circleTest1->ApplyForceToActor(circleTest2, glm::vec2(-5, 0));
}

void PhysicsApp::SceneRocket()
{
	circleTest3 = new Circle(glm::vec2(90, -40),	//pos
		glm::vec2(0, 0),		//vel
		5.f,					//mass
		3.5f,					//radius
		glm::vec4(1, 0, 1, 1));	//col

	m_physicsScene->AddActor(circleTest3);
}

void PhysicsApp::SceneCircleCollision()
{
	//Circle* circle1;
	circleTest1 = new Circle(glm::vec2(-10, 0),		//pos
							glm::vec2(0, 0),		//vel
							3.f,					//mass
							4,						//radius
							glm::vec4(1, 0, 0, 1)); //col

								//Circle* circle2;
	circleTest2 = new Circle(glm::vec2(10, 0),		//pos
							glm::vec2(0, 0),		//vel
							8.f,					//mass
							3,						//radius
							glm::vec4(1, 1, 0, 1));	//col

	m_physicsScene->AddActor(circleTest1);
	m_physicsScene->AddActor(circleTest2);

	//apply force to circles at start
	//circleTest1->ApplyForce(glm::vec2(10, 0));
	//circleTest2->ApplyForce(glm::vec2(-5, 0));
}

void PhysicsApp::ApplyRocketExhaust()
{
	circleTest3->SetMass(circleTest3->GetMass() * 0.9);
	Circle* exhaustParticle = new Circle(circleTest3->GetPosition() + glm::vec2(-m_direction, -5), //pos
		glm::vec2(0, 0),		//vel
		1.f,					//mass
		.5f,					//radius
		glm::vec4(1, 0, 1, 1));	//col

	m_physicsScene->AddActor(exhaustParticle);
	exhaustParticle->ApplyForceToActor(circleTest3, glm::vec2(m_direction, 1.5f));
	std::cout << "Exhaust particle created" << std::endl;
}

void PhysicsApp::SetRocketDirection(aie::Input* input)
{
	if (input->isKeyDown(aie::INPUT_KEY_LEFT)) m_direction = -1;
	if (input->isKeyDown(aie::INPUT_KEY_DOWN)) m_direction = 0;
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT)) m_direction = 1;
}