#include "aobject3D.h"

#include "amaterial.h"
#include "ageometry.h"
#include "aabstractlight.h"
#include "adirectionallight.h"
#include "alight3Dset.h"
#include "anode.h"

#include <qdebug.h>

AObject3D::AObject3D()
	: m_initCounter( 0 )
	, m_isAssociated( false )
{
	initializeOpenGLFunctions();
}

AObject3D::AObject3D( 
	bool physics )
	: m_initCounter( 2 )
	, m_allowPhysics( physics )
	, m_isAssociated( false )
{
	initializeOpenGLFunctions();
}

AObject3D::~AObject3D() {}

void AObject3D::update( float time ) {}

void AObject3D::draw( 
	const QMatrix4x4& projection, 
	const QMatrix4x4& view,
	const QVector3D& cameraPosition, 
	const ALight3DSet& lights )
{	    
	// If object is associated with node it gets node`s conversion matrix. Else it gets identity matrix.
	QMatrix4x4 nodeMatrix, nodeRotationMatrix;
	if ( m_isAssociated ) 
	{
		nodeMatrix			= m_associatedNode->computedMatrix();
		nodeRotationMatrix	= m_associatedNode->computedRotationMatrix();
	}
	QMatrix4x4 local	= m_localTranslation * m_localRotation * m_localScale;
	QMatrix4x4 world	= local;
	//QMatrix4x4 rotationMatrix	= nodeRotationMatrix * m_localRotation;
	QMatrix4x4 WVP	= projection * view * local;
		
	// bind vertex buffer
	QOpenGLBuffer* vertexBuffer = m_geometry->vertexBuffer();
	vertexBuffer->bind();
	// bind index attribute
	QOpenGLBuffer* indexBuffer = m_geometry->indexBuffer();
	indexBuffer->bind();

	// bind shader, sampler units
	m_material->bind();
	
	QOpenGLShaderProgram* shader = m_material->shader();
	// associate vertex attributes defined in geometry with shader
	foreach ( AVertexAttribute* attribute, m_geometry->vertexAttributes() )
	{
		shader->setAttributeBuffer( 
			attribute->name(),
			attribute->type(),
			attribute->offset(),
			attribute->tupleSize(),
			attribute->stride() );
		shader->enableAttributeArray( attribute->name() );
	}

	shader->setUniformValue( "matW", world );
	shader->setUniformValue( "matR", m_localRotation );
	shader->setUniformValue( "matWVP", WVP );
	shader->setUniformValue( "camPosition", cameraPosition );

	// Lighting
	if ( m_material->Properties.Lightable )
	{
		for (int i = 0; i < lights.count(); i++ )
		{
			const AAbstractLight* abstractLight = lights.at( i );		
			// Process directional lights
			if ( abstractLight->type() == AAbstractLight::Directional )
			{
				/*QString name( "lights[" + QString::number( i ) + "]" );
				const char* color		= (const char*)QString(name + ".color").constData();
				const char* direction	= (const char*)QString(name + ".direction").constData();
				const char* ambient		= (const char*)QString(name + ".ambient").constData();
				const char* diffuse		= (const char*)QString(name + ".diffuse").constData();*/

				/*ADirectionalLight* light = (ADirectionalLight*)( abstractLight );
				shader->setUniformValue( color, light->color() );
				shader->setUniformValue( direction, light->direction() );
				shader->setUniformValue( ambient, light->ambientIntensity() );
				shader->setUniformValue( diffuse, light->diffuseIntensity() );*/

				ADirectionalLight* light = (ADirectionalLight*)( abstractLight );
				shader->setUniformValue( "light.color", light->color() );
				shader->setUniformValue( "light.direction", light->direction() );
				shader->setUniformValue( "light.ambient", light->ambientIntensity() );
				shader->setUniformValue( "light.diffuse", light->diffuseIntensity() );
			}
		}
	}

	int indexCount = m_geometry->indexCount();
	glDrawElements( GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0 );

	m_material->release();
	foreach ( AVertexAttribute* attribute, m_geometry->vertexAttributes() )
	{
		shader->disableAttributeArray( attribute->name() );
	}
}

void AObject3D::setMaterial( AMaterial* material )
{
	m_material = material;
}

void AObject3D::setGeometry( AGeometry* geometry )
{
	m_geometry = geometry;
}