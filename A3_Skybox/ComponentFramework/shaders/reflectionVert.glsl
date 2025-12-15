#version 450 
#extension GL_ARB_separate_shader_objects : enable


layout(location = 0) in vec4 inVertex;
layout(location = 1) in vec3 inNormal;

layout(location = 0) uniform mat4 projectionMatrix;
layout(location = 1) uniform mat4 viewMatrix;
layout(location = 2) uniform mat4 modelMatrix;

out vec3 Normal;
out vec3 Position;

void main() {

    //vec3 vertDir = normalize(vec3(viewMatrix * modelMatrix * inVertex));

   Normal = mat3(transpose(inverse(modelMatrix))) * inNormal;
   Normal= normalize(Normal);
   
   Position = normalize(vec3(modelMatrix * inVertex));
   Position.y *= -1;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * inVertex;


}