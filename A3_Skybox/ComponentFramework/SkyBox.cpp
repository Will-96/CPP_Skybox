#include <glew.h>
#include "Texture.h"
#include "SkyBox.h"
#include <SDL_image.h>


SkyBox::SkyBox(const char* posXfileName_, const char* posYfileName_, const char* posZfileName_,
	const char* negXfileName_, const char* negYfileName_, const char* negZfileName_){

	posXfileName = posXfileName_;
	posYfileName = posYfileName_;
	posZfileName = posZfileName_;
	negXfileName = negXfileName_;
	negYfileName = negYfileName_;
	negZfileName = negZfileName_;

}

SkyBox::~SkyBox() {
	
}

bool SkyBox::OnCreate() {
	cube_mesh = new Mesh("meshes/Cube.obj");
	if (cube_mesh->OnCreate() == false) {
		delete cube_shader;
		delete cube_mesh;
		return false;
	}
	
	cube_shader = new Shader("shaders/skyboxVert.glsl", "shaders/skyboxFrag.glsl");
	if (cube_shader->OnCreate() == false) {
		delete cube_shader;
		return false;
	}
	

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	SDL_Surface *textureSurface = nullptr;
	int mode;

	textureSurface = IMG_Load(posXfileName);
	if (textureSurface == nullptr) {
		return false;
	}

	// ( ) = (if here is ture) ? (return here) : (false here)
	//int mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;

	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);

	/****************************************************************/
	textureSurface = IMG_Load(posYfileName);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	/****************************************************************/


	/****************************************************************/
	textureSurface = IMG_Load(posZfileName);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	/****************************************************************/

	/****************************************************************/
	textureSurface = IMG_Load(negXfileName);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	/****************************************************************/

	/****************************************************************/
	textureSurface = IMG_Load(negYfileName);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	/****************************************************************/

	/****************************************************************/
	textureSurface = IMG_Load(negZfileName);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	/****************************************************************/



	/// Wrapping and filtering options
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return true;
}

void SkyBox::OnDestroy(){
	if (textureID) {
		glDeleteTextures(1, &textureID);
	}
	
	if (cube_shader) {
		cube_shader->OnDestroy();
		delete cube_shader;
	}
	if (cube_mesh) {
		cube_mesh->OnDestroy();
		delete cube_mesh;
	}
}

void SkyBox::Render() const{
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	cube_mesh->Render();
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
