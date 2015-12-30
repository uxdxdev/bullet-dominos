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
#ifndef _OPENGLMOTIONSTATE_H_
#define _OPENGLMOTIONSTATE_H_

#include "btBulletCollisionCommon.h"

class OpenGLMotionState : public btDefaultMotionState {
public:
	OpenGLMotionState(const btTransform &transform) : btDefaultMotionState(transform) {}

	void GetWorldTransform(btScalar* transform) {
		btTransform trans;
		getWorldTransform(trans);
		trans.getOpenGLMatrix(transform);
	}
};

#endif