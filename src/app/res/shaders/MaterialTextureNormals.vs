#version 330 core

layout (location = 0) in vec3 a_posL;
layout (location = 1) in vec2 a_uv;
layout (location = 2) in vec3 a_normL;
layout (location = 3) in vec3 a_bitangentL;
layout (location = 4) in vec3 a_tangentL;

out vec2 v_uv;
out vec3 v_posW;
out vec3 v_normW;
out vec3 v_tangentW;
out vec3 v_bitangentW;

uniform mat4 u_W;
uniform mat4 u_WVP;

void main()
{
	gl_Position = u_WVP * vec4(a_posL, 1.0);

	v_uv = a_uv;
	v_posW = vec3(u_W * vec4(a_posL, 1.0));

	v_normW = normalize( (u_W * vec4(a_normL, 0.0)).xyz );
	v_tangentW = normalize( (u_W * vec4(a_tangentL, 0.0)).xyz );
	v_bitangentW = normalize( (u_W * vec4(a_bitangentL, 0.0)).xyz );
}
