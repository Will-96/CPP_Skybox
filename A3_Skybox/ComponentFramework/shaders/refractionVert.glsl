#version 450
#extension GL_ARB_separate_shader_objects : enable


layout(location = 0) in vec3 inVertex;
layout(location = 1) in vec3 inNormal;

layout(location = 0) uniform mat4 projectionMatrix;
layout(location = 1) uniform mat4 viewMatrix;
layout(location = 2) uniform mat4 modelMatrix;

layout(location = 0) out vec3 eyeDir;

layout(location = 1) out vec3 Normal;

void main() {

    vec4 vertexPosCameraSpace = viewMatrix * modelMatrix * vec4(inVertex, 1.0);
    eyeDir = vec3(vertexPosCameraSpace);
    eyeDir = normalize(eyeDir);

     vec4 inNormal4d = vec4(inNormal.x, inNormal.y, inNormal.z, 0);

    Normal = vec3(viewMatrix * modelMatrix * inNormal4d);
    Normal = normalize(Normal);
    
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(inVertex, 1.0);

}