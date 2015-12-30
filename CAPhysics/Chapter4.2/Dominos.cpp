// 
// Game Physics Assignment Year 4
//
// David Morton K00179391
// Michael O' Reilly K00171850
//
// Dominos
//
// 3D application demonstrating the Bullet physics engine and the FreeGLUT OpenGL library. 
//
// Dominos uses algorithmic patterns to place dominos in the 3d scene and provides physics simulations using
// the Bullet physics engine. FreeGLUT is used for rendering. 
//
#include "Dominos.h"
#include <math.h>
#include <cstdlib>
#include <ctime>

Dominos::Dominos() : patternType(WAVE) {}

void Dominos::InitializePhysics() {
	// create the collision configuration
	m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
	// create the dispatcher
	m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);
	// create the broadphase
	m_pBroadphase = new btDbvtBroadphase();
	// create the constraint solver
	m_pSolver = new btSequentialImpulseConstraintSolver();
	// create the world
	m_pWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pCollisionConfiguration);

	// Random number seed
	srand(static_cast <unsigned> (time(0)));

	// create our scene's physics objects
	CreateObjects();
}

void Dominos::ShutdownPhysics() {
	delete m_pWorld;
	delete m_pSolver;
	delete m_pBroadphase;
	delete m_pDispatcher;
	delete m_pCollisionConfiguration;
}

void Dominos::CreateObjects() {
	// create a ground plane
	CreateGameObject(new btBoxShape(btVector3(1, 50, 50)), 0, btVector3(0.2f, 0.6f, 0.6f), btVector3(0.0f, 0.0f, 0.0f));

	// Create domino patterns using enum in Dominos.h
	CreatePattern(110, patternType);
}

float Dominos::RandomColor(float maxValue)
{
	float randomColor = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / maxValue));
	return randomColor;
}

void Dominos::CreatePattern(int maxPoints, int type)
{
	float colorRed = 0.0f;
	float colorGreen = 0.0f;
	float colorBlue = 0.0f;

	float dominoHeight = 2.0f;

	// Create an Archimedean spiral
	if (type == SPIRAL)
	{
		// create spiral dominos
		float x = 0;
		float z = 0;
		float angle = 0.0f;
		float a = 2, b = 2;
		float previousX = 0.0f;
		float previousZ = 0.0f;

		// Create blue box to hit first domino
		CreateGameObject(new btBoxShape(btVector3(1, 1, 1)), 1.0, btVector3(0.0f, 0.2f, 0.8f), btVector3(2.0f, 8.0f, 0.0f));

		for (int i = 2; i < maxPoints; i++)
		{
			colorRed = RandomColor(2.0f);
			colorGreen = RandomColor(2.0f);
			colorBlue = RandomColor(2.0f);

			if (i % 30 == 0) dominoHeight++;

			angle = 0.15 * i;
			x = (a + b * angle) * cos(angle);
			z = (a + b * angle) * sin(angle);

			GameObject* temp = CreateGameObject(new btBoxShape(btVector3(dominoHeight, 1.5f, 0.1f)), 1.0, btVector3(colorRed, colorGreen, colorBlue), btVector3((float)x /* X Axis left or right */, 0.0f /* Domino sitting on the ground */, (float)z /* Depth */));

			float dirX = -(a + b * angle) * sin(angle) + (b * cos(angle));
			float dirZ = (a + b * angle) * cos(angle) + (b * sin(angle));
			float newAngle = atan2(dirX, dirZ);
			printf("dirX: %f - dirZ: %f - angle: %f\n", dirX, dirZ, newAngle);
			temp->setRotationYaw(newAngle);

			previousX = x;
			previousZ = z;
		}
	}
	else if (type == LOGARITHMIC) // Create a Logarithmic spiral
	{

		float a = 0.1;
		float b = 2;
		float speed = 1;
		int angle = 0;

		float previousX = 0.0f;
		float previousZ = 0.0f;

		// Create blue box to hit first domino
		CreateGameObject(new btBoxShape(btVector3(1, 1, 1)), 1.0, btVector3(0.0f, 0.2f, 0.8f), btVector3(0.0f, 8.0f, 0.0f));

		for (int i = 1; i <= maxPoints; i++) {

			colorRed = RandomColor(2.0f);
			colorGreen = RandomColor(2.0f);
			colorBlue = RandomColor(2.0f);

			angle += speed;
			dominoHeight += 0.1f;

			float x = (a * cos(angle)) * (b * angle);
			float z = (a * sin(angle)) * (b * angle);

			GameObject* temp = CreateGameObject(new btBoxShape(btVector3(dominoHeight, 0.1f, 1.5f)), 1.0, btVector3(colorRed, colorGreen, colorBlue), btVector3((float)x /* X Axis left or right */, 0.0f /* Domino sitting on the ground */, (float)z /* Depth */));

			float dirX = -(a + b * angle) * sin(angle) + (b * cos(angle));
			float dirZ = (a + b * angle) * cos(angle) + (b * sin(angle));
			float newAngle = atan2(dirX, dirZ);
			temp->setRotationYaw(newAngle);

			previousX = x;
			previousZ = z;
		}
	}
	else if (type == WAVE) // Create a Sine wave
	{
		float waveX = 0.0f;
		float waveZ = 0.0f;
		float first = 0.0f, second = 1.0f, next;

		float previousX = 0.0f;
		float previousZ = 0.0f;
		// Create blue box to hit first domino
		CreateGameObject(new btBoxShape(btVector3(1, 1, 1)), 1.0, btVector3(0.0f, 0.2f, 0.8f), btVector3(0.0f, 8.0f, -30.0f));

		// X Axis
		for (waveZ = -30; waveZ < maxPoints; waveZ++)
		{
			colorRed = RandomColor(2.0f);
			colorGreen = RandomColor(2.0f);
			colorBlue = RandomColor(2.0f);

			dominoHeight += 0.2f;

			waveX = sin(waveZ);

			GameObject *temp = CreateGameObject(new btBoxShape(btVector3(dominoHeight, 1.5, 0.1)), 1.0, btVector3(colorRed, colorGreen, colorBlue), btVector3((float)waveX /* X Axis left or right */, 0.0f /* Domino sitting on the ground */, (float)waveZ /* Depth */));
			float dirX = waveX - previousX;
			float dirZ = waveZ - previousZ;
			float newAngle = atan2(dirX, dirZ);
			temp->setRotationYaw(newAngle);

			previousX = waveX;
			previousZ = waveZ;
		}
	}
}

void Dominos::Keyboard(unsigned char key, int x, int y) {
	//Override of key functions
	//Change the pattern type with keys 1-3
	switch (key) {
	case '1':
		resetSimulation(SPIRAL);
		break;
	case '2':
		resetSimulation(LOGARITHMIC);
		break;
	case '3':
		resetSimulation(WAVE);
		break;
	}
}

void Dominos::resetSimulation(int pattern) {
	//Change pattern type
	patternType = pattern;

	//Shutdown the physics engine
	ShutdownPhysics();

	//Delete all the objects
	for (GameObject* o : m_objects) {
		delete o;
	}

	//Clear all of the objects
	m_objects.clear();

	//Restart physics
	InitializePhysics();
}