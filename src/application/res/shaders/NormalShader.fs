precision mediump float;

#define TEXTURES_COUNT 2

#define DIRECTIONAL_LIGHTS_COUNT 1
#define POINT_LIGHTS_COUNT 2

in vec3 v_posW;
in vec2 v_uv;
in vec3 v_normalW;
in vec3 v_bitangentW;
in vec3 v_tangentW;

// 0 - texture
// 1 - normalMap
uniform sampler2D u_texture2D[TEXTURES_COUNT];

uniform vec4 u_ambientColor;
uniform float u_ambientWeight;
uniform float u_specularPower;

uniform vec3 u_camPosition;

uniform vec4 u_directionalLightColor[DIRECTIONAL_LIGHTS_COUNT];
uniform vec4 u_pointLightColor[POINT_LIGHTS_COUNT];

uniform vec3 u_lightDirection[DIRECTIONAL_LIGHTS_COUNT];
uniform vec3 u_lightPosition[POINT_LIGHTS_COUNT];

void main()
{
	vec3 normal = texture2D(u_texture2D[1], v_uv).xyz;
	mat3 TBN = mat3(normalize(v_tangentW), normalize(v_bitangentW), normalize(v_normalW));
	vec3 normalW = normalize(TBN * (2.0 * normal - 1.0));

	vec3 toEye = normalize(u_camPosition - v_posW);

	vec4 diffuseLight = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 specularLight = vec4(0.0, 0.0, 0.0, 0.0);

	for(int i = 0; i < DIRECTIONAL_LIGHTS_COUNT; ++i)
	{
		float diffuseIntensity = max( dot(normalW, -u_lightDirection[i]), 0.0 );
		diffuseLight += u_directionalLightColor[i] * diffuseIntensity;

		vec3 reflectionDir = normalize( reflect(u_lightDirection[i], normalW) );
		float specularIntensity = pow( max( dot(reflectionDir, toEye), 0.0 ), u_specularPower );
		specularLight += u_directionalLightColor[i] * specularIntensity;
	}

	for(int i = 0; i < POINT_LIGHTS_COUNT; ++i)
	{
		vec3 lightDirection = normalize(v_posW - u_lightPosition[i]);

		float diffuseIntensity = max( dot(normalW, -lightDirection), 0.0 );
		diffuseLight += u_pointLightColor[i] * diffuseIntensity;

		vec3 reflectionDir = normalize( reflect(lightDirection, normalW) );
		float specularIntensity = pow( max( dot(reflectionDir, toEye), 0.0 ), u_specularPower );
		specularLight += u_pointLightColor[i] * specularIntensity;
	}

	vec4 texture = texture2D(u_texture2D[0], v_uv);

	gl_FragColor = mix(diffuseLight, u_ambientColor, u_ambientWeight) * texture + specularLight;
	gl_FragColor.a = texture.a;
}
