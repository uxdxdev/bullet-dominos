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
#include "Dominos.h"
#include "FreeGLUTCallbacks.h"

int main(int argc, char** argv)
{
	Dominos demo;
	return glutmain(argc, argv, 1024, 768, "Introduction to Game Physics with Bullet Physics and OpenGL", &demo);
}