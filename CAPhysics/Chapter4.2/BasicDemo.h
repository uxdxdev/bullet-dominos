#include "BulletOpenGLApplication.h"
#include "btBulletDynamicsCommon.h"

// Domino patterns
enum Pattern{
	SPIRAL,
	LOGARITHMIC
};

class BasicDemo : public BulletOpenGLApplication {
public:
	virtual void InitializePhysics() override;
	virtual void ShutdownPhysics() override;

	void CreateObjects();

	// Create Domino patterns based on algorithm choice
	void CreatePattern(int maxNumberOfDominos, int type);

};