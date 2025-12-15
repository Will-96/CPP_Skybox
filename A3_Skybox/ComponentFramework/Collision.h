#pragma once
#include "Body.h"

namespace COLLISION {
	// Checks if two spheres have collided and return true or false.  
	// We are assuming that all Body objects are spheres.  
	// I know it's weird, we'll fix it next course 
	// Notice the const keyword here.   
	// That is a promise to the compilar that we won't change the Body objects.  
	// We are just detecting collisions after all 
	bool SphereSphereCollisionDetected(const Body* ball, const Body* target);

	// If a collision has occurred, we need to immediately change the velocity 
	// of both spheres.  
	// We will definitely be changing the objects so no const keywords here  
	void SphereSphereCollisionResponse(Body* ball, Body* target);
}