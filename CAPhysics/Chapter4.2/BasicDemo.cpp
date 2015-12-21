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
	// create our original red box
	CreateGameObject(new btBoxShape(btVector3(1, 1, 1)), 1.0, btVector3(0.0f, 0.2f, 0.8f), btVector3(-0.5f, 10.0f, 0.0f));
	CreateGameObject(new btBoxShape(btVector3(1.5,0.1,1.0)), 1.0, btVector3(1.0f, 0.2f, 0.2f), btVector3(0.0f, 0.0f, 0.0f));
	// create a second box
	CreateGameObject(new btBoxShape(btVector3(1.5,0.1,1.0)), 1.0, btVector3(0.0f, 0.2f, 0.8f), btVector3(1.0f, 0.0f, 0.0f));
	CreateGameObject(new btBoxShape(btVector3(1.5, 0.1, 1.0)), 1.0, btVector3(0.0f, 0.2f, 0.8f), btVector3(2.0f, 0.0f, -0.2f));
	CreateGameObject(new btBoxShape(btVector3(1.5, 0.1, 1.0)), 1.0, btVector3(0.0f, 0.2f, 0.8f), btVector3(3.0f, 0.0f, -0.4f));

	// Create domino patterns using enum in BasicDemo.h
	CreatePattern(150, SPIRAL);
}

void BasicDemo::CreatePattern(int maxPoints, int type)
{
	if (type == SPIRAL)
	{
		// create spiral dominos
		float x = 0;
		float y = 0;
		float angle = 0.0f;
		int a = 3, b = 3;

		for (int i = 0; i < maxPoints; i++)
		{
			angle = 0.1 * i;
			x = (a + b * angle) * cos(angle);
			y = (a + b * angle) * sin(angle);

			CreateGameObject(new btBoxShape(btVector3(1.5f, 0.1, 1.0)), 1.0, btVector3(2.0f, 0.2f, 0.8f), btVector3((float)x /* X Axis left or right */, 0.0f /* Domino sitting on the ground */, (float)y /* Depth */));

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
