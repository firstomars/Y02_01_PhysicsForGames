#include "PhysicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"
#include <glm/ext.hpp>
#include <iostream>


PhysicsApp::PhysicsApp() 
{

}

PhysicsApp::~PhysicsApp() {

}

bool PhysicsApp::startup() 
{
	//increase the 2D line count to maximize the no . of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);
	
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

	//rocket circle
	circleTest3 = new Circle(glm::vec2(90, -40),		//pos
							glm::vec2(0, 0),		//vel
							5.f,					//mass
							3.5f,					//radius
							glm::vec4(1, 0, 1, 1));	//col

	m_physicsScene->AddActor(circleTest1);
	m_physicsScene->AddActor(circleTest2);
	m_physicsScene->AddActor(circleTest3);

	//apply force to circles
	//circleTest1->ApplyForce(glm::vec2(10, 0));
	//circleTest2->ApplyForce(glm::vec2(-5, 0));

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
	if (input->isKeyDown(aie::INPUT_KEY_LEFT)) m_direction = -1;
	if (input->isKeyDown(aie::INPUT_KEY_DOWN)) m_direction = 0;
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT)) m_direction = 1;

	//rocket exhaust application
	m_timer += deltaTime;
	if (m_timer > 1) 
	{
		circleTest3->SetMass(circleTest3->GetMass() * 0.9);
		Circle* exhaustParticle;
		exhaustParticle =new Circle(circleTest3->GetPosition() + glm::vec2 (-m_direction,-5), //pos
									glm::vec2(0, 0),		//vel
									1.f,					//mass
									.5f,					//radius
									glm::vec4(1, 1, 1, 1));	//col

		m_physicsScene->AddActor(exhaustParticle);
		exhaustParticle->ApplyForceToActor(circleTest3, glm::vec2(m_direction, 1.5f));
		std::cout << "Exhaust particle created" << std::endl;

		m_timer = 0;
	}

	

	aie::Gizmos::clear();
	m_physicsScene->Update(deltaTime);
	m_physicsScene->Draw();

	if (input->isKeyDown(aie::INPUT_KEY_SPACE)) OnKeyPress();

	//delete input camera controls
	/*
	// Update the camera position using the arrow keys
	float camPosX;
	float camPosY;
	m_2dRenderer->getCameraPos(camPosX, camPosY);

	if (input->isKeyDown(aie::INPUT_KEY_UP))
		camPosY += 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		camPosY -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		camPosX -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		camPosX += 500.0f * deltaTime;

	m_2dRenderer->setCameraPos(camPosX, camPosY);
	*/

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	//draw stuff here
	static float aspectRatio = 16 / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100,
		-100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));


	//delete previous draws
	/*
	// draw a thin line
	m_2dRenderer->drawLine(300, 300, 600, 400, 2, 1);

	// draw a moving purple circle
	m_2dRenderer->setRenderColour(1, 0, 1, 1);
	m_2dRenderer->drawCircle(sin(m_timer) * 100 + 600, 150, 50);

	// draw a rotating red box
	m_2dRenderer->setRenderColour(1, 0, 0, 1);
	m_2dRenderer->drawBox(600, 500, 60, 20, m_timer);

	// draw a slightly rotated sprite with no texture, coloured yellow
	m_2dRenderer->setRenderColour(1, 1, 0, 1);
	m_2dRenderer->drawSprite(nullptr, 400, 400, 50, 50, 3.14159f * 0.25f, 1);
	
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	*/

	//m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}

void PhysicsApp::OnKeyPress()
{
	//circleTest1->ApplyForceToActor(circleTest2, glm::vec2(-5, 0));
}

