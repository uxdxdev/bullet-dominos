#include "BasicDemo.h"
#include <math.h>

void BasicDemo::InitializePhysics() {
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

	// create our scene's physics objects
	CreateObjects();
}

void BasicDemo::ShutdownPhysics() {
	delete m_pWorld;
	delete m_pSolver;
	delete m_pBroadphase;
	delete m_pDispatcher;
	delete m_pCollisionConfiguration;
}

void BasicDemo::CreateObjects() {
	// create a ground plane
	CreateGameObject(new btBoxShape(btVector3(1,50,50)), 0, btVector3(0.2f, 0.6f, 0.6f), btVector3(0.0f, 0.0f, 0.0f));
	
	// Create blue box to hit first domino
	CreateGameObject(new btBoxShape(btVector3(1, 1, 1)), 1.0, btVector3(0.0f, 0.2f, 0.8f), btVector3(2.0f, 8.0f, 0.0f));
	
	// Create domino patterns using enum in BasicDemo.h
	CreatePattern(100, SPIRAL);
}

void BasicDemo::CreatePattern(int maxPoints, int type)
{
	if (type == SPIRAL)
	{
		// create spiral dominos
		float x = 0;
		float z = 0;
		float angle = 0.0f;
		int a = 2, b = 2;
		float previousX = 0.0f;
		float previousZ = 0.0f;
		
		float dominoHeight = 2.0f;

		for (int i = 2; i < maxPoints; i++)
		{
			if (i % 30 == 0) dominoHeight++;

			angle = 0.15 * i;
			x = (a + b * angle) * cos(angle);
			z = (a + b * angle) * sin(angle);

			GameObject* temp = CreateGameObject(new btBoxShape(btVector3(dominoHeight, 1.5f, 0.1f)), 1.0, btVector3(2.0f, 0.2f, 0.8f), btVector3((float)x /* X Axis left or right */, 0.0f /* Domino sitting on the ground */, (float)z /* Depth */));

			float dirX = -(a + b * angle) * sin(angle) + (b * cos(angle));
			float dirZ = (a + b * angle) * cos(angle) + (b * sin(angle));
			float newAngle = atan2(dirX, dirZ);
			printf("dirX: %f - dirZ: %f - angle: %f\n", dirX, dirZ, newAngle);
			temp->setRotationYaw(newAngle);
			
			previousX = x;
			previousZ = z;
		}
	}
	else if (type == LOGARITHMIC)
	{
		// Log pattern
	}
	else if (type == WAVE)
	{
		int x, y, first = 0, second = 1, next;

		// X Axis
		for (x = 0; x < maxPoints; x++)
		{
			if (x <= 1)
				next = x;
			else
			{
				next = first + second;
				first = second;
				second = next;
			}

			y = sin(x) - 0.5*x;

			CreateGameObject(new btBoxShape(btVector3(1.5, 0.1, 1.0)), 1.0, btVector3(2.0f, 0.2f, 0.8f), btVector3((float)x /* X Axis left or right */, 0.0f /* Domino sitting on the ground */, (float)y /* Depth */));
		}
	}
}
