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
#include "BulletOpenGLApplication.h"
#include "btBulletDynamicsCommon.h"

#define PI 3.14159265

class Dominos : public BulletOpenGLApplication {
public:
	Dominos();

	virtual void InitializePhysics() override;
	virtual void ShutdownPhysics() override;

	void CreateObjects();

	// Create Domino patterns based on algorithm choice
	void CreatePattern(int maxPoints, int type);

	// Pick a random color for each domino
	float RandomColor(float maxValue);

	// Reset the simulation to allow different patterns
	virtual void resetSimulation(int pattern);

protected:
	int patternType;
};