#version 450
#extension GL_ARB_separate_shader_objects : enable


layout(location = 0) in vec4 vVertex;

layout(location = 1) uniform mat4 projectionMatrix;
layout(location = 2) uniform mat4 viewOrientationMatrix;

out vec3 uvwCoords;

void main() {
    uvwCoords = vec3(vVertex);
    gl_Position = projectionMatrix * viewOrientationMatrix * vVertex;
}