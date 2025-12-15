#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 fragColor;

layout(location = 0) in vec3 eyeDir;

layout(location = 1) in vec3 Normal;

uniform samplerCube skybox;

void main() {
	vec3 dir = vec3(1,1,0);
	///////
	vec3 N = normalize(Normal);
	vec3 P = (dot(-eyeDir,Normal)) * Normal;
	vec3 reflectionVector = eyeDir + 2.0 * P;
	/////
	float thetaRatio = 1.0 / 1.52;
	vec3 incoming = eyeDir;
	float costheta = dot(-incoming, Normal);
 
	vec3 incoming_parallel = incoming + costheta * Normal;
	vec3 refraction_parallel = thetaRatio * incoming_parallel;
	float refraction_parallel_square = length(refraction_parallel) * length(refraction_parallel);
	vec3 refraction_perp = -sqrt(1 - refraction_parallel_square) * Normal;

	vec3 refractionVector = refraction_parallel + refraction_perp;

	vec4 reflectioncolor = texture(skybox,reflectionVector);
	vec4 refractioncolor = texture(skybox,refractionVector);

	float Frate = 0.2;
	float cosT = max(dot(-eyeDir, N), 0.0);
	float R = Frate + (1 - Frate) * pow(1 - cosT, 5.0);


	//fragColor = reflectioncolor;
	//fragColor = refractioncolor;

	fragColor = mix(refractioncolor, reflectioncolor, R);
	
}