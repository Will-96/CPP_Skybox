#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 fragColor;

layout(location = 0) in vec3 vertNormal;
layout(location = 1) in vec3 lightDir[4];

layout(location = 5) in vec3 eyeDir; 
layout(location = 6) in vec2 textureCoords; 

uniform sampler2D myTexture; 

uniform vec4 diffuseColor[4];  
uniform vec4 specularColor[4];

void main() {
    vec4 ka = vec4(0.1, 0.1, 0.1, 1.0);  
    vec4 kt = texture(myTexture, textureCoords); 

    vec4 finalColor = vec4(0.0);

    for (int i = 0; i < 4; i++) {
        float diff = max(dot(vertNormal, lightDir[i]), 0.0);
        vec3 reflection = normalize(reflect(-lightDir[i], vertNormal));
        float spec = max(dot(eyeDir, reflection), 0.0);
        spec = pow(spec, 14.0);

        finalColor += (ka + (diff * diffuseColor[i]) + (spec * specularColor[i])) * kt;
    }


    fragColor = finalColor;
}