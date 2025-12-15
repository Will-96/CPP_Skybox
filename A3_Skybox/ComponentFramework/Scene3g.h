#ifndef SCENE3_H
#define SCENE3_H
#include "Scene.h"
#include "Vector.h"
#include <Matrix.h>
#include "Texture.h"
#include "Trackball.h"
#include "Camera.h"

using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Body;
class Mesh;
class Shader;

class Scene3g : public Scene {
private:
	Body* sub;
	Shader* shader;
	Mesh* submesh;
	Texture* subtexture;

	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 subModelMatrix;

	bool drawInWireMode;

	Camera* camera;
	Trackball trackball;

public:
	explicit Scene3g();
	virtual ~Scene3g();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE3_H