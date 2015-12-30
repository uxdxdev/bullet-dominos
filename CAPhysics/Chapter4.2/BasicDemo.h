#include "BulletOpenGLApplication.h"
#include "btBulletDynamicsCommon.h"

#define PI 3.14159265

// Domino patterns
enum Pattern{
	SPIRAL,
	LOGARITHMIC,
	WAVE
};

class BasicDemo : public BulletOpenGLApplication {
public:
	virtual void InitializePhysics() override;
	virtual void ShutdownPhysics() override;

	void CreateObjects();

	// Create Domino patterns based on algorithm choice
	void CreatePattern(int maxPoints, int type);

	float RandomColor(float maxValue);

};