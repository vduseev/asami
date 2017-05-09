// Input
varying lowp vec3 f_norm;
varying lowp vec3 f_wpos;
varying lowp vec2 f_texCoords;

// Uniform input
uniform sampler2D texture0;

struct SDirectLight
{
	vec3 color;
	vec3 direction;
	float ambient;
	float diffuse;
};

uniform highp vec3	camPosition;
uniform highp float matShiningInten;
uniform highp float matShiningPower;
uniform highp SDirectLight light;

void main() {

	vec4 textureColor0	= texture( texture0, f_texCoords );
	vec3 textureColor	= textureColor0.xyz;
	vec3 ambientColor	= light.color * light.ambient;
	vec3 diffuseColor	= vec3( 0, 0, 0 );
	vec3 specularColor	= vec3( 0, 0, 0 );
	
	float diffuseFactor = dot( f_norm, -light.direction );
	if ( diffuseFactor > 0 ) 
	{
		diffuseColor = light.color * diffuseFactor * light.diffuse;
	}

	vec3 vertexToEye	= normalize( camPosition - f_wpos );
	vec3 lightReflect	= normalize( reflect( light.direction, f_norm ) );
	float specularFactor = pow( dot( vertexToEye, lightReflect ), matShiningPower );
	if ( specularFactor > 0 ) 
	{
		specularColor = light.color * specularFactor * matShiningInten;
	}
	
	vec3 frag = textureColor * ( ambientColor + diffuseColor + specularColor );
	gl_FragColor = vec4( frag, 1.0 );
}