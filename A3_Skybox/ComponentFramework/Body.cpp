#include "Body.h"
#include <QMath.h>

Body::Body() : pos{}, vel{}, accel{}, mass{1.0}, mesh{ nullptr }, texture{ nullptr }, radius{} {
}

Body::~Body() {}

void Body::UpdatePos(float deltaTime) {
	/// From 1st semester physics class
	pos += vel * deltaTime + 0.5f * accel * deltaTime * deltaTime;
	
}

void Body::UpdateVel(float deltaTime)
{
	// From 1st semester physics class
	vel += accel * deltaTime;
}

void Body::ApplyForce(Vec3 force) {
	accel = force / mass;
}

bool Body::OnCreate() {
	return true;
}

void Body::OnDestroy() {
}

void Body::Render() const {
}

void Body::ApplyTorque(Vec3 torque) {
	float inertia = (0.4 * mass * radius * radius) + (mass * radius * radius);
	float inverseinertia = 1 / inertia;

	inverserotationalInertia = Matrix3(
		inverseinertia, 0.0f, 0.0f,
		0.0f, inverseinertia, 0.0f,
		0.0f, 0.0f, inverseinertia
	);

	angularAcc = inverserotationalInertia * torque;
}

void Body::UpdateAngularVel(float deltaTime) {
	angularVel += angularAcc * deltaTime;
}

void Body::UpdateOrientation(float deltaTime) {
	// Remember, the direction of the angVel is the rotn axis
	// Magnitude is the angle
	float angleRadians = VMath::mag(angularVel) * deltaTime;

	// If angle is zero, get outta here
	if (angleRadians < VERY_SMALL) { // BEWARE! Don't use == here for floats
		return;
	}

	Vec3 axis = VMath::normalize(angularVel);
	float angleDegrees = angleRadians * RADIANS_TO_DEGREES;
	Quaternion rotation = QMath::angleAxisRotation(angleDegrees, axis);
	orientation = rotation * orientation; // Yep, order matters

}


const Matrix4 Body::GetModelMatrix() const
{
	Matrix4 T = MMath::translate(pos);
	Matrix4 R = MMath::toMatrix4(orientation);
	Matrix4 S = MMath::scale(Vec3(radius, radius, radius));

	return T * R * S;
}

void Body::StraightLineConstraint(float slope, float y_intercept, float deltaTime)
{
	float positionConstraint = pos.y - slope * pos.x - y_intercept;
	float JV = vel.y - slope * vel.x; // this is the velocity constraint

	float baumgarteStabilizationParameter = 0.1;
	float bias = baumgarteStabilizationParameter * positionConstraint / deltaTime;
	float JJT = slope * slope + 1;
	float lagrangianMultiplier = (-JV - bias) / ((1 / mass) * JJT); // this is lambda
	Vec3 JT = Vec3(-slope, 1, 0); // Jacobian transposed
	Vec3 changeInVel = (1 / mass) * JT * lagrangianMultiplier;
	vel += changeInVel;
}

void Body::QuadraticConstraint(float a, float b, float c, float deltaTime)
{
	float positionConstraint = a * pos.x * pos.x + b * pos.x + c - pos.y;
	float JV = 2 * a * pos.x * vel.x + b * vel.x - vel.y;
	Vec3 JT = Vec3(2 * a * pos.x + b, -1, 0); // Jacobian transposed
	float baumgarteStabilizationParameter = 0.1;
	float bias = baumgarteStabilizationParameter * positionConstraint / deltaTime;
	float JJT = (2 * a * pos.x + b) * (2 * a * pos.x + b) + 1;
	float lagrangianMultiplier = (-JV - bias) / ((1 / mass) * JJT); // this is lambda
	Vec3 changeInVel = (1 / mass) * JT * lagrangianMultiplier;
	vel += changeInVel;

}

void Body::CircleConstraint(float r, Vec3 circleCentrePos, float deltaTime)
{
	float positionConstraint = (pos.x - circleCentrePos.x) * (pos.x - circleCentrePos.x)
		+ (pos.y - circleCentrePos.y) * (pos.y - circleCentrePos.y) - r * r;

	float JV = (2 * pos.x - 2 * circleCentrePos.x) * vel.x + (2 * pos.y - 2 * circleCentrePos.y) * vel.y;

	Vec3 JT = Vec3(2 * pos.x - 2 * circleCentrePos.x, 2 * pos.y - 2 * circleCentrePos.y, 0);

	float baumgarteStabilizationParameter = 0.1;
	float bias = baumgarteStabilizationParameter * positionConstraint / deltaTime;

	float JJT = (2 * pos.x - 2 * circleCentrePos.x) * (2 * pos.x - 2 * circleCentrePos.x)
		+ (2 * pos.y - 2 * circleCentrePos.y) * (2 * pos.y - 2 * circleCentrePos.y);

	float lagrangianMultiplier = (-JV - bias) / ((1 / mass) * JJT); // this is lambda
	Vec3 changeInVel = (1 / mass) * JT * lagrangianMultiplier;
	vel += changeInVel;
}
