#include "atexturedquad.h"

#include "amaterial.h"
#include "ageometry.h"
#include "avertexattribute.h"

#include <QString>

ATexturedQuad::ATexturedQuad(
	QSize textureCoordinates )
	: AObject3D( false )
{
	prepareGeometry( textureCoordinates );
	prepareMaterial( 
		"textures/basic/cubeside.png",
		"shaders/basic/textured_quad.vert",
		"shaders/basic/textured_quad.frag" );
}

ATexturedQuad::ATexturedQuad(
	const QString& textureFileName,
	QSize textureCoordinates )
	: AObject3D( false )
{
	prepareGeometry( textureCoordinates );
	prepareMaterial( 
		textureFileName,
		"shaders/basic/textured_quad.vert",
		"shaders/basic/textured_quad.frag" );
}

ATexturedQuad::ATexturedQuad(
	const QString& textureFileName,
	const QString& vertexShader, 
	const QString& fragmentShader,
	QSize textureCoordinates )
	: AObject3D( false )
{
	prepareGeometry( textureCoordinates );
	prepareMaterial( 
		textureFileName,
		vertexShader,
		fragmentShader );
}

ATexturedQuad::~ATexturedQuad()
{
}

void ATexturedQuad::prepareMaterial( 
	const QString& textureFileName,
	const QString& vertexShader, 
	const QString& fragmentShader )
{
	AMaterial* material = new AMaterial();
	material->setShaders( vertexShader, fragmentShader );

	ASampler* sampler = new ASampler();
    sampler->create();
    sampler->setMinificationFilter( GL_LINEAR_MIPMAP_LINEAR );
    sampler->setSamplerParameterF( GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f );
    sampler->setMagnificationFilter( GL_LINEAR );
	sampler->setWrapMode( ASampler::DirectionS, GL_REPEAT );
    sampler->setWrapMode( ASampler::DirectionT, GL_REPEAT );

	QImage image( textureFileName );
    ATexture* texture = new ATexture();
    texture->create();
    texture->bind();
    texture->setImage( image );
    texture->generateMipMaps();
    material->setTextureUnit( 0, texture, sampler, QByteArrayLiteral( "texture0" ) );

	material->Properties.ShiningIntensity = 0.5f;
	material->Properties.ShiningPower = 10.0f;

	setMaterial( material );
}

void ATexturedQuad::prepareGeometry( QSize textureCoordinates )
{
	AGeometry* geometry = new AGeometry();
	geometry->setUsagePattern( QOpenGLBuffer::StaticDraw, QOpenGLBuffer::VertexBuffer );
	geometry->setUsagePattern( QOpenGLBuffer::StaticDraw, QOpenGLBuffer::IndexBuffer );
	
	Vertex* vertices = new Vertex[ 4 ];
	vertices[ 0 ].pos = QVector3D( -1.0f, 1.0f, 0.0f );
	vertices[ 1 ].pos = QVector3D( 1.0f, 1.0f, 0.0f );
	vertices[ 2 ].pos = QVector3D( 1.0f, -1.0f, 0.0f );
	vertices[ 3 ].pos = QVector3D( -1.0f, -1.0f, 0.0f );
	int x = textureCoordinates.width(),
		y = textureCoordinates.height();
	vertices[ 0 ].tex = QVector2D( 0.0f, y );
	vertices[ 1 ].tex = QVector2D( x, y );
	vertices[ 2 ].tex = QVector2D( x, 0.0f );
	vertices[ 3 ].tex = QVector2D( 0.0f, 0.0f );
	
	GLuint* indices = new GLuint[ 6 ];
	indices[ 0 ]	= 0;
	indices[ 1 ]	= 2;
	indices[ 2 ]	= 1;
	indices[ 3 ]	= 0;
	indices[ 4 ]	= 3;
	indices[ 5 ]	= 2;

	for ( int i = 0; i < 6; i += 3 )
	{
		int index0 = indices[ i ],
			index1 = indices[ i + 1 ],
			index2 = indices[ i + 2 ];

		QVector3D v1 = vertices[ index1 ].pos - vertices[ index0 ].pos;
		QVector3D v2 = vertices[ index2 ].pos - vertices[ index0 ].pos;

		QVector3D normal = QVector3D::normal( v2, v1 );

		vertices[ index0 ].norm += normal;
		vertices[ index1 ].norm += normal;
		vertices[ index2 ].norm += normal;
	}

	for ( int i = 0; i < 4; i++ )
	{
		vertices[ i ].norm.normalize();
	}

	int size = sizeof( QVector3D ) + sizeof( QVector3D ) + sizeof( QVector2D );
	geometry->setVertices( vertices, 4, size );
	geometry->setIndices( indices, 6 );

	AVertexAttribute* positionAttribute = new AVertexAttribute(
		QByteArrayLiteral( "v_pos" ), 
		GL_FLOAT, 0, 
		3, size );

	AVertexAttribute* normalAttribute = new AVertexAttribute(
		QByteArrayLiteral( "v_norm" ), 
		GL_FLOAT, sizeof( QVector3D ), 
		3, size );

	AVertexAttribute* textureAttribute = new AVertexAttribute(
		QByteArrayLiteral( "v_texCoords" ), 
		GL_FLOAT, sizeof( QVector3D ) + sizeof( QVector3D ), 
		3, size );

	geometry->setVertexAttribute( positionAttribute );
	geometry->setVertexAttribute( normalAttribute );
	geometry->setVertexAttribute( textureAttribute );

	setGeometry( geometry );
}
