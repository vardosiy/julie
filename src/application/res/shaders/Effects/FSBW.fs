precision mediump float;

varying vec2 v_uv;

uniform sampler2D u_texture2D;

void main()
{
	vec3 orig = texture2D(u_texture2D, v_uv).xyz;
	
	float val = 0.3 * orig.x + 0.59 * orig.y + 0.11 * orig.z;

	gl_FragColor = vec4(val, val, val, 1.0);
}
