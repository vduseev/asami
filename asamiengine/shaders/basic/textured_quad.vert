// Input
attribute	highp	vec3 v_pos;
attribute	highp	vec3 v_norm;
attribute	highp	vec2 v_texCoords;

// Output
varying lowp vec3 f_norm;
varying lowp vec3 f_wpos;
varying lowp vec2 f_texCoords;

// Uniform input
uniform highp mat4 matW;
uniform highp mat4 matR;
uniform highp mat4 matWVP;

void main() {
	
	vec4 normal	= vec4( v_norm.xyz, 1.0 ) * matR;	
	vec4 pos	= vec4( v_pos.xyz, 1.0 );

	f_wpos		= matW * pos;
	f_norm		= normal.xyz;
	f_texCoords = v_texCoords;

	gl_Position = matWVP * pos;
}