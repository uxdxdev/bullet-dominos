// 
// Game Physics Assignment Year 4
//
// David Morton K00179391
// Michael O' Reilly K00...
//
// Dominos
//
// 3D application demonstrating the Bullet physics engine and the FreeGLUT OpenGL library. 
//
// Dominos uses algorithmic patterns to place dominos in the 3d scene and provides physics simulations using
// the Bullet physics engine. FreeGLUT is used for rendering. 
//
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#define MATH_PI 3.14159

#include "btBulletDynamicsCommon.h"

#include "OpenGLMotionState.h"

class GameObject {
public:
	GameObject(btCollisionShape* pShape, float mass, const btVector3 &color, const btVector3 &initialPosition = btVector3(0,0,0), const btQuaternion &initialRotation = btQuaternion(0,0,1,1));
	~GameObject();

	// accessors
	btCollisionShape* GetShape() { return m_pShape; }

	btRigidBody* GetRigidBody() { return m_pBody; }

	btMotionState* GetMotionState() { return m_pMotionState; }

	void GetTransform(btScalar* transform) { 
		if (m_pMotionState) m_pMotionState->GetWorldTransform(transform); 
	}
	
	btVector3 GetColor() { return m_color; }
	void setRotationPitch(float p);
	void setRotationYaw(float y);
	void setRotationRoll(float r);
protected:
	btCollisionShape*  m_pShape;
	btRigidBody*    m_pBody;
	OpenGLMotionState*  m_pMotionState;
	btVector3      m_color;
};
#endif
