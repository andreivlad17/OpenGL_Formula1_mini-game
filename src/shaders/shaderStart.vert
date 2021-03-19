#version 410 core

layout(location=0) in vec3 vPosition;
layout(location=1) in vec3 vNormal;
layout(location=2) in vec2 vTexCoords;

#define NR_POINT_LIGHTS 10  

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform	mat3 normalMatrix;
uniform vec3 lPosEye[NR_POINT_LIGHTS];
uniform mat4 lightSpaceTrMatrix;

out vec3 fNormal;
out vec4 fragPosEye;
out vec2 fragTexCoords;
out vec3 lightPosEye[NR_POINT_LIGHTS];
out vec4 fragPosLightSpace;

void main() 
{	//compute eye space coordinates
	fragPosEye = view * model * vec4(vPosition, 1.0f);
	for(int i = 0; i< NR_POINT_LIGHTS; i++){
		lightPosEye[i] = vec3(view * vec4(lPosEye[i], 1.0f));
	}
	fNormal = normalize(normalMatrix * vNormal);
	fragTexCoords=vTexCoords;
	fragPosLightSpace = lightSpaceTrMatrix * model * vec4(vPosition, 1.0f);
	gl_Position = projection * view * model * vec4(vPosition, 1.0f);
}
