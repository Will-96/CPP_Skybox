#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 fragColor;

in vec3 Normal;
in vec3 Position;

uniform samplerCube skybox;

void main() {
    vec3 reflectDir  = reflect(-Position,Normal);
    vec3 reflectionColor = texture(skybox, reflectDir).rgb;

    fragColor = vec4(reflectionColor, 1.0);

}