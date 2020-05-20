#version 330 core
precision mediump float;

#define ENABLE_SPECULAR_LIGHTNING 0

#define POINT_LIGHTS_COUNT 1
#define DIRECTIONAL_LIGHTS_COUNT 1

in vec3 v_posW;
in vec3 v_normW;
out vec4 o_color;

uniform vec4 u_color;

uniform vec4 u_ambientColor;
uniform float u_ambientWeight;

#if ENABLE_SPECULAR_LIGHTNING
uniform float u_specularPower;
#endif

uniform vec3 u_camPosition;

#if DIRECTIONAL_LIGHTS_COUNT > 0
uniform vec4 u_directionalLightColor[DIRECTIONAL_LIGHTS_COUNT];
uniform vec3 u_lightDirection[DIRECTIONAL_LIGHTS_COUNT];
#endif

#if POINT_LIGHTS_COUNT > 0
uniform vec4 u_pointLightColor[POINT_LIGHTS_COUNT];
uniform vec3 u_lightPosition[POINT_LIGHTS_COUNT];
#endif

void main()
{
	vec3 normalW = normalize(v_normW);
	vec3 toEye = normalize(u_camPosition - v_posW);

	vec4 diffuseLight = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 specularLight = vec4(0.0, 0.0, 0.0, 0.0);

#if DIRECTIONAL_LIGHTS_COUNT > 0
	for(int i = 0; i < DIRECTIONAL_LIGHTS_COUNT; ++i)
	{
		float diffuseIntensity = max( dot(normalW, -u_lightDirection[i]), 0.0 );
		diffuseLight += u_directionalLightColor[i] * diffuseIntensity;

	#if ENABLE_SPECULAR_LIGHTNING
		vec3 reflectionDir = normalize( reflect(u_lightDirection[i], normalW) );
		float specularIntensity = pow( max( dot(reflectionDir, toEye), 0.0 ), u_specularPower );
		specularLight += u_directionalLightColor[i] * specularIntensity;
	#endif
	}
#endif

#if POINT_LIGHTS_COUNT > 0
	for(int i = 0; i < POINT_LIGHTS_COUNT; ++i)
	{
		vec3 lightDirection = normalize(v_posW - u_lightPosition[i]);

		float diffuseIntensity = max( dot(normalW, -lightDirection), 0.0 );
		diffuseLight += u_pointLightColor[i] * diffuseIntensity;

	#if ENABLE_SPECULAR_LIGHTNING
		vec3 reflectionDir = normalize( reflect(lightDirection, normalW) );
		float specularIntensity = pow( max( dot(reflectionDir, toEye), 0.0 ), u_specularPower );
		specularLight += u_pointLightColor[i] * specularIntensity;
	#endif
	}
#endif

	o_color = mix(diffuseLight, u_ambientColor, u_ambientWeight) * u_color + specularLight;
	o_color.a = u_color.a;
}
