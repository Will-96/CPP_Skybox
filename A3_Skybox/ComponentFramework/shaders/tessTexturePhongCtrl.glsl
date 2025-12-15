#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(vertices = 3) out;


uniform float tesslevelInner;
uniform float tesslevelOuter;


in vec2 uvCoordFromVert[];
in vec3 normalFromVert[];
in float verDistance[];


out vec2 uvCoordFromCtrl[];
out vec3 normalFromCtrl[];


void main() {
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	uvCoordFromCtrl[gl_InvocationID] = uvCoordFromVert[gl_InvocationID];
	ormalFromCtrl[gl_InvocationID] = normalFromVert[gl_InvocationID];

	float tesslevel =1.0;

	if (gl_InvocationID == 0){
		tesslevel = 16.0;
		
		gl_tesslevelInner[0]=tesslevel;

		gl_tesslevelOuter[0]=tesslevel;
		gl_tesslevelOuter[1]=tesslevel;
		gl_tesslevelOuter[2]=tesslevel;

	}
	

}