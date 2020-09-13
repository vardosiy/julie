#version 330 core
precision mediump float;

#define DIRECTIONAL_LIGHTS_COUNT 1
#define POINT_LIGHTS_COUNT 1

in vec2 v_uv;
in vec3 v_posW;
in vec3 v_normW;
out vec4 o_color;

//-----------------------------------------------------------------------------
// material props
uniform vec3 u_matAmbient;
uniform vec3 u_matDiffuse;
uniform vec3 u_matSpecular;
uniform float u_opacity;
uniform float u_shininess;

//-----------------------------------------------------------------------------
// cam and lights
uniform vec3 u_camPosition;

uniform vec3 u_ambientColor;
uniform float u_ambientWeight;

#if DIRECTIONAL_LIGHTS_COUNT > 0
uniform vec3 u_directionalLightColor[DIRECTIONAL_LIGHTS_COUNT];
uniform vec3 u_lightDirection[DIRECTIONAL_LIGHTS_COUNT];
#endif

#if POINT_LIGHTS_COUNT > 0
uniform vec3 u_pointLightColor[POINT_LIGHTS_COUNT];
uniform vec3 u_lightPosition[POINT_LIGHTS_COUNT];
#endif

//-----------------------------------------------------------------------------

void main()
{
	vec3 normal = normalize(v_normW);
	vec3 toEye = normalize(u_camPosition - v_posW);

	vec3 ambientLight = u_ambientColor * u_matAmbient;
	vec3 diffuseLight = vec3(0.0, 0.0, 0.0);
	vec3 specularLight = vec3(0.0, 0.0, 0.0);

#if DIRECTIONAL_LIGHTS_COUNT > 0
	for(int i = 0; i < DIRECTIONAL_LIGHTS_COUNT; ++i)
	{
		float diffuseIntensity = max( dot(normal, -u_lightDirection[i]), 0.0 );
		diffuseLight += u_directionalLightColor[i] * (diffuseIntensity * u_matDiffuse);

		vec3 reflectionDir = normalize( reflect(u_lightDirection[i], normal) );
		float specularIntensity = pow( max( dot(reflectionDir, toEye), 0.0 ), u_shininess );
		specularLight += u_directionalLightColor[i] * (specularIntensity * u_matSpecular);
	}
#endif

#if POINT_LIGHTS_COUNT > 0
	for(int i = 0; i < POINT_LIGHTS_COUNT; ++i)
	{
		vec3 lightDirection = normalize(v_posW - u_lightPosition[i]);

		float diffuseIntensity = max( dot(normal, -lightDirection), 0.0 );
		diffuseLight += u_pointLightColor[i] * (diffuseIntensity * u_matDiffuse);

		vec3 reflectionDir = normalize( reflect(lightDirection, normal) );
		float specularIntensity = pow( max( dot(reflectionDir, toEye), 0.0 ), u_shininess );
		specularLight += u_pointLightColor[i] * (specularIntensity * u_matSpecular);
	}
#endif

	vec3 color = mix(diffuseLight, ambientLight, u_ambientWeight) + specularLight;
	o_color = vec4(color, u_opacity);
}
