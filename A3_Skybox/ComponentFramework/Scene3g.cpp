#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Scene3g.h"
#include <MMath.h>
#include "Debug.h"
#include "Mesh.h"
#include "Shader.h"
#include "Body.h"
#include "Texture.h"

Scene3g::Scene3g() :sub{ nullptr }, shader{ nullptr }, submesh{ nullptr }, 
subtexture{ nullptr }, drawInWireMode{ false }, camera{ nullptr } {
	Debug::Info("Created Scene3: ", __FILE__, __LINE__);
}

Scene3g::~Scene3g() {
	Debug::Info("Deleted Scene3: ", __FILE__, __LINE__);
}

bool Scene3g::OnCreate() {
	Debug::Info("Loading assets Scene3: ", __FILE__, __LINE__);
	camera = new Camera();
	camera->OnCreate();

	sub = new Body();
	sub->OnCreate();
	submesh = new Mesh("meshes/Cube.obj");
	submesh->OnCreate();

	subtexture = new Texture();
	subtexture->LoadImage("textures/subTexture.jpg");

	shader = new Shader("shaders/refractionVert.glsl", "shaders/refractionFrag.glsl");
	if (shader->OnCreate() == false) {
		std::cout << "Shader failed ... we have a problem\n";
	}

	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 6.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));

	subModelMatrix.loadIdentity();
	return true;
}

void Scene3g::OnDestroy() {
	Debug::Info("Deleting assets Scene0: ", __FILE__, __LINE__);
	sub->OnDestroy();
	delete sub;

	submesh->OnDestroy();
	delete submesh;

	shader->OnDestroy();
	delete shader;

	camera->OnDestroy();
	delete camera;

}

void Scene3g::HandleEvents(const SDL_Event& sdlEvent) {
	trackball.HandleEvents(sdlEvent);
	camera->HandleEvents(sdlEvent);

	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		switch (sdlEvent.key.keysym.scancode) {
		case SDL_SCANCODE_W:
			drawInWireMode = !drawInWireMode;
			break;
		}
		break;

	case SDL_MOUSEMOTION:
		break;

	case SDL_MOUSEBUTTONDOWN:
		break;

	case SDL_MOUSEBUTTONUP:
		break;

	default:
		break;
	}
}

void Scene3g::Update(const float deltaTime) {

	subModelMatrix = MMath::toMatrix4(trackball.getQuat());
		//* MMath::rotate(30.0f, Vec3(0.0f, 1.0f, 0.0f));

}

void Scene3g::Render() const {

	/// Set the background color then clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	camera->RenderSkyBox();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);


	if (drawInWireMode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, subModelMatrix);

	glBindTexture(GL_TEXTURE_CUBE_MAP, camera->GetSkyBox()->GetTextureID());

	submesh->Render(GL_TRIANGLES);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glUseProgram(0);
	
}




