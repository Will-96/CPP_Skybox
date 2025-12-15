#version 450
#extension GL_ARB_separate_shader_objects : enable


layout(location = 0) in vec3 vVertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUVCoord;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;


out ve2 uvCoordFormVert;
out vec3 normalFormVert;
out float vertDistance;

void main() {
	uvCoordFormVert = uvCoord;
	//vertDistance = length(viewMatrix * modelMatrix * vVertex);
	normalFromVert = vNormal;
	gl_Position = vVertex;

}