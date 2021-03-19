#version 410 core

in vec3 fNormal;

out vec4 fColor;

//lighting
#define NR_POINT_LIGHTS 10  

uniform	vec3 lightDir[NR_POINT_LIGHTS];
uniform	vec3 lightColor[NR_POINT_LIGHTS];

uniform sampler2D shadowMap;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

in vec4 fragPosEye;
in vec3 lightPosEye[NR_POINT_LIGHTS];

vec3 ambient;
vec3 diffuse;
vec3 specular;

float ambientStrength = 0.2f;
float specularStrength = 0.5f;
float shininess = 30.0f;

float constant;
float linear;
float quadratic;

in vec2 fragTexCoords;

in vec4 fragPosLightSpace;

float shadow;
uniform float fogDensity = 0.00f;

float computeFog()
{
	float fragmentDistance = length(fragPosEye);
	float fogFactor = exp(-pow(fragmentDistance * fogDensity, 2));

	return clamp(fogFactor, 0.0f, 1.0f);
}

float computeShadow() 
{
	// perform perspective divide
	vec3 normalizedCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	// Transform to [0,1] range
	normalizedCoords = normalizedCoords * 0.5 + 0.5;
	// Get closest depth value from light's perspective
	float closestDepth = texture(shadowMap, normalizedCoords.xy).r;
	// Get depth of current fragment from light's perspective
	float currentDepth = normalizedCoords.z;
	// Check whether current frag pos is in shadow
	float bias = 0.005f;
	shadow = (currentDepth - bias > closestDepth) ? shadow = 1.0f : 0.0f;

	if (normalizedCoords.z > 1.0f)
	{
		return 0.0f;
	}

	return shadow;
}

void computeLightComponents(int i)
{		
	// constants
	if(i == 9){
		constant = 1.0f;
		linear = 0.07f;
		quadratic = 0.0002f;
	} else {
		constant = 1.0f;
		linear = 0.07f;
		quadratic = 0.017f;
	}
	vec3 cameraPosEye = vec3(0.0f);//in eye coordinates, the viewer is situated at the origin
	
	//--compute distance to light
	float dist = length(lightPosEye[i] -fragPosEye.xyz);
	
	//--compute attenuation
	float att = 1.0f / (constant + linear * dist + quadratic * (dist * dist));
	
	//transform normal
	vec3 normalEye = normalize(fNormal);	
	
	//compute light direction
	vec3 lightDirN = normalize(lightPosEye[i] - fragPosEye.xyz);
	
	//compute view direction 
	vec3 viewDirN = normalize(cameraPosEye - fragPosEye.xyz);

	//compute half vector
	vec3 halfVector = normalize(lightDirN + viewDirN);
	
	//compute ambient light
	ambient += att * ambientStrength * lightColor[i];
	
	//compute diffuse light
	diffuse += att * max(dot(normalEye, lightDirN), 0.0f) * lightColor[i];

	
	//compute specular light
	vec3 reflection = reflect(-lightDirN, normalEye);
	float specCoeff = pow(max(dot(normalEye, halfVector), 0.0f), shininess);
	specular += att * specularStrength * specCoeff * lightColor[i];
		
}

void main() 
{ 
	for(int i = 0; i< NR_POINT_LIGHTS; i++){
		computeLightComponents(i);
	}
	
	vec3 baseColor = vec3(0.9f, 0.35f, 0.0f);//orange
	
	ambient *= vec3(texture(diffuseTexture, fragTexCoords));
	diffuse *= vec3(texture(diffuseTexture, fragTexCoords));
	specular *= vec3(texture(specularTexture, fragTexCoords));

	vec4 fogColor = vec4 (0.5f,0.5f,0.5f,1.0f);
	float fogValue = computeFog();

	//modulate with shadow
	shadow = computeShadow();

	vec3 color = min((ambient + (1.0f - shadow) * diffuse) + (1.0f - shadow) * specular, 1.0f);

    //fColor = vec4(color, 1.0f);
	fColor = mix(fogColor, vec4(color, 1.0f), fogValue);
}
