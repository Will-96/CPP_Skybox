#include "Collision.h"



bool COLLISION::SphereSphereCollisionDetected(const Body* ball, const Body* target) {
	// TODO for YOU
	// 
	// Collision has occured if
	// distance between centres is LESS THAN the two radii added together
	// float distance = ....

	Vec3 between = ball->pos - target->pos;
	float distance = VMath::mag(between);
	float sumRad = ball->radius + target->radius;

	if (distance <= sumRad) {
		return true;
	}
	else {
		return false;
	}

	// else
	// return false;
}

void COLLISION::SphereSphereCollisionResponse(Body* ball, Body* target) {
	// Step 1
	// Find the collision normal vector
	// Vector goes from one centre to the other (normalize after you are done)
	// Vec3 normal = ....

	Vec3 normal = VMath::normalize(ball->pos - target->pos);
	
	float relativeVel = VMath::dot((ball->vel - target->vel), normal);

	if (relativeVel > 0) {
		return;
	}

	const float e = 0.4f;
	float massSum = (1.0f / ball->mass) + (1.0f / target->mass);

	float j = (- (1 + e) * relativeVel) / massSum;


	Vec3 impulse = j * normal;
	ball->vel += impulse / ball->mass;
	target->vel -= impulse / target->mass;


	/*ball->angularVel = VMath::cross(ball->vel, normal) / ball->radius;
	target->angularVel = VMath::cross(target->vel, normal) / target->radius;*/


	// Immediately change velocities
	// These are just example values for now
	//body1->vel += normal * J
	//body2->vel -= normal * J
}
