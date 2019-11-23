precision mediump float;

varying vec2 v_uv;

uniform sampler2D u_texture2D;
uniform float u_limit;

void main()
{
	vec3 orig = texture2D(u_texture2D, v_uv).xyz;
	
	float brightness = 0.3 * orig.x + 0.59 * orig.y + 0.11 * orig.z;
	float val = step(u_limit, brightness);

	gl_FragColor = vec4(orig * val, 1.0);
}
