precision mediump float;

#define TEXTURES_2D_COUNT 3

#define DIRECTIONAL_LIGHTS_COUNT 1
#define POINT_LIGHTS_COUNT 2

varying vec3 v_posW;
varying vec2 v_uv;
varying vec2 v_uvTiling;
varying vec3 v_normalW;
varying vec3 v_bitangentW;
varying vec3 v_tangentW;

// TEXTURES

// 0 - underlying texture
// 1 - normal map
// 2 - displacment map
uniform sampler2D u_texture[TEXTURES_2D_COUNT];
uniform samplerCube u_cubeTexture;

// LIGHTS

uniform vec4 u_ambientColor;
uniform float u_ambientWeight;

uniform vec3 u_camPosition;

uniform vec4 u_directionalLightColor[DIRECTIONAL_LIGHTS_COUNT];
uniform vec4 u_pointLightColor[POINT_LIGHTS_COUNT];

uniform vec3 u_lightDirection[DIRECTIONAL_LIGHTS_COUNT];
uniform vec3 u_lightPosition[POINT_LIGHTS_COUNT];

// PARAMETERS
uniform float u_depthDispl;
uniform float u_depthAdjust;
uniform float u_dMax;
uniform float u_time;
uniform vec4 u_color;

void main()
{
	// INITIALIZING

	vec2 dispMapUv = vec2(v_uv.x, v_uv.y + u_time);
	vec2 disp = texture2D(u_texture[2], dispMapUv).xy;

	// LIGHTS CALCULATION

	vec3 normalW = normalize(v_normalW);
	vec4 diffuseLight = vec4(0.0, 0.0, 0.0, 0.0);

	for(int i = 0; i < DIRECTIONAL_LIGHTS_COUNT; ++i)
	{
		float diffuseIntensity = max( dot(normalW, -u_lightDirection[i]), 0.0 );
		diffuseLight += u_directionalLightColor[i] * diffuseIntensity;
	}

	for(int i = 0; i < POINT_LIGHTS_COUNT; ++i)
	{
		vec3 lightDirection = normalize(v_posW - u_lightPosition[i]);

		float diffuseIntensity = max( dot(normalW, -lightDirection), 0.0 );
		diffuseLight += u_pointLightColor[i] * diffuseIntensity;
	}

	// LOWER SURFACE

	float dMaxRefraction = v_uv.x * u_depthDispl;
	float offsetRefractionX = dMaxRefraction * (2.0 * disp.x - 1.0);
	float offsetRefractionY = dMaxRefraction * (2.0 * disp.y - 1.0);

	vec2 uvBottom = v_uvTiling + vec2(offsetRefractionX, offsetRefractionY);
	vec4 bottomColor = texture2D(u_texture[0], uvBottom);

	float depthFactor = clamp(u_depthAdjust * v_uv.x, 0.0, 1.0);
	vec4 refractionColor = mix(bottomColor, u_color, depthFactor);
	refractionColor = mix(diffuseLight, u_ambientColor, u_ambientWeight) * refractionColor;

	// UPPER SURFACE

	float offsetReflectionX = u_dMax * (2.0 * disp.x - 1.0);
	float offsetReflectionY = u_dMax * (2.0 * disp.y - 1.0);
	vec2 uvNormals = v_uvTiling + vec2(offsetReflectionX, offsetReflectionY);

	vec3 normal = texture2D(u_texture[1], uvNormals).xyz;
	mat3 TBN = mat3(normalize(v_tangentW), normalize(v_bitangentW), normalW);
	vec3 waterNormalW = normalize(TBN * (2.0 * normal - 1.0));

	vec3 toEye = normalize(u_camPosition - v_posW);
	vec3 reflectDir = reflect(normalize(toEye), waterNormalW);
	vec4 reflectionColor = textureCube(u_cubeTexture, normalize(reflectDir));

	// FINAL

	float fresnel = pow( (1.0 - abs( dot( waterNormalW, toEye ) ) ), 4.0);
	gl_FragColor = vec4( mix(refractionColor, reflectionColor, fresnel).xyz, 1.0);
}
