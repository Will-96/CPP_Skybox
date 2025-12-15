#ifndef BODY_H
#define BODY_H
#include <Vector.h> /// This is in GameDev
#include <Matrix.h>
#include <MMath.h>
#include <Quaternion.h>
using namespace MATH; 

/// Just forward declair these classes so I can define a pointer to them
/// Used later in the course
class Mesh;
class Texture;

class Body {
public:
    Body();
    ~Body();

//private: /// Physics stuff
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float mass;

	float radius;
	Vec3 angularVel;
	Vec3 angularAcc;
	Matrix3 inverserotationalInertia;
	Quaternion orientation;

private: /// Graphics stuff 
	Mesh *mesh;
	Texture *texture;
	
public:
	bool OnCreate();
	void OnDestroy();
	void Render() const;
	void ApplyForce(Vec3 force);
	void setAccel(const Vec3 &accel_) { accel = accel_;}


	// Updates angular acceleration using torque and rotational inertia
	void ApplyTorque(Vec3 torque);

	// Updates angular velocity using rotational equations of motion
	void UpdateAngularVel(float deltaTime);

	// Updates orientation quaternion using the angular velocity
	void UpdateOrientation(float deltaTime);

	// Update position or velocity using the equations of motion. 
	// It's handy later on with constraints to have these as separate methods
	void UpdatePos(float deltaTime);
	void UpdateVel(float deltaTime);

	// Build a model matrix to send to the GPU
	const Matrix4 GetModelMatrix() const;

	// Building the easiest constraint Umer could think of
	void StraightLineConstraint(float slope, float y_intercept, float deltaTime);

	// Next up the quadratic constraint (a parabola)
	void QuadraticConstraint(float a, float b, float c, float deltaTime);

	void CircleConstraint(float r, Vec3 circleCentrePos, float deltaTime);
};

#endif
