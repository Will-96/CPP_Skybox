#pragma once
#include "Shader.h"
#include "Mesh.h"

class Mesh;
class Shader;

class SkyBox
{
private:
	unsigned int textureID;
	const char* posXfileName, *posYfileName, *posZfileName, *negXfileName, *negYfileName, *negZfileName;

	Shader* cube_shader;
	Mesh* cube_mesh;

public:
	SkyBox(const char* posXfileName_, const char* posYfileName_, const char* posZfileName_,
		const char* negXfileName_, const char* negYfileName_, const char* negZfileName_);
	~SkyBox();

	Shader* GetShader()const { return cube_shader; }

	int GetTextureID()const { return textureID; }

	bool OnCreate();
	void OnDestroy();
	void Render() const;
};

