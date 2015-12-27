#include "GameObject.h"
GameObject::GameObject(btCollisionShape* pShape, float mass, const btVector3 &color, const btVector3 &initialPosition, const btQuaternion &initialRotation) {
	// store the shape for later usage
	m_pShape = pShape;

	// store the color
	m_color = color;

	// create the initial transform
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(initialPosition);
	transform.setRotation(initialRotation);

	// create the motion state from the
	// initial transform
	m_pMotionState = new OpenGLMotionState(transform);

	// calculate the local inertia
	btVector3 localInertia(0,0,0);

	// objects of infinite mass can't
	// move or rotate
	if (mass != 0.0f)
		pShape->calculateLocalInertia(mass, localInertia);

	// create the rigid body construction
	// info using the mass, motion state
	// and shape
	btRigidBody::btRigidBodyConstructionInfo cInfo(mass, m_pMotionState, pShape, localInertia);
	
	// create the rigid body
	m_pBody = new btRigidBody(cInfo);
}

GameObject::~GameObject() {
	delete m_pBody;
	delete m_pMotionState;
	delete m_pShape;
}

void GameObject::setRotationPitch(float p) {
	if (m_pBody)
	{
		//p = p * (MATH_PI / 180);

		btTransform trans = m_pBody->getWorldTransform();
		btQuaternion rot = trans.getRotation();

		float angleDiff = p - rot.getX();
		btQuaternion diffRot = btQuaternion(btVector3(1, 0, 0), angleDiff);
		rot = diffRot * rot;

		trans.setRotation(rot);
		m_pBody->setWorldTransform(trans);
	}
}

void GameObject::setRotationYaw(float y) {
	if (m_pBody)
	{
		//y = y * (MATH_PI / 180);

		btTransform trans = m_pBody->getWorldTransform();
		btQuaternion rot = trans.getRotation();

		float angleDiff = y - rot.getX();
		btQuaternion diffRot = btQuaternion(btVector3(0, 1, 0), angleDiff);
		rot = diffRot * rot;

		trans.setRotation(rot);
		m_pBody->setWorldTransform(trans);
	}
}

void GameObject::setRotationRoll(float r) {
	if (m_pBody)
	{
		//r = r * (MATH_PI / 180);

		btTransform trans = m_pBody->getWorldTransform();
		btQuaternion rot = trans.getRotation();

		float angleDiff = r - rot.getX();
		btQuaternion diffRot = btQuaternion(btVector3(0, 0, 1), angleDiff);
		rot = diffRot * rot;

		trans.setRotation(rot);
		m_pBody->setWorldTransform(trans);
	}
}