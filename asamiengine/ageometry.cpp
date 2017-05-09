#include "ageometry.h"

#include "asimpletexturevertex.h"

AGeometry::AGeometry()
{
	m_vertexBufferAllocatedCount = 0;
	m_indexBufferAllocatedCount = 0;
		
	m_vertexBuffer = new QOpenGLBuffer( QOpenGLBuffer::VertexBuffer );
	m_vertexBuffer->create();

	m_indexBuffer = new QOpenGLBuffer( QOpenGLBuffer::IndexBuffer );
	m_indexBuffer->create();
}

AGeometry::~AGeometry() {}

void AGeometry::setUsagePattern( QOpenGLBuffer::UsagePattern pattern, QOpenGLBuffer::Type type )
{
	if ( type == QOpenGLBuffer::VertexBuffer )
		m_vertexBuffer->setUsagePattern( pattern );
	else if (type == QOpenGLBuffer::IndexBuffer )
		m_indexBuffer->setUsagePattern( pattern );
}

void AGeometry::setVertices(const void* data, int count, int size, int offsetElements )
{
	m_vertexBuffer->bind();

	int bytes = count * size;
	int offset = offsetElements * size;
	if ( m_vertexBufferAllocatedCount < offset + bytes )
	{
		m_vertexBuffer->allocate( offset + bytes + size );
		m_vertexBuffer->write( offset, data, bytes );
		m_vertexBufferAllocatedCount = offset + bytes;
	}
	else
	{
		m_vertexBuffer->write( offset, data, bytes );
	}

	m_vertexBuffer->release();
	m_vertexCount = count;
}

void AGeometry::setIndices( GLuint* indices, int count, int offsetElements )
{
	m_indexBuffer->bind();

	int bytes = count * sizeof( GLuint );
	int offset = offsetElements * sizeof( GLuint );
	if ( m_indexBufferAllocatedCount < bytes ||
		 m_indexBufferAllocatedCount == 0 )
	{
		m_indexBuffer->allocate( indices, offset + bytes );
		m_indexBufferAllocatedCount = offset + bytes;
	}
	else
	{
		m_indexBuffer->write( offset, indices, bytes );
	}

	m_indexBuffer->release();
	m_indexCount = count;
}

void AGeometry::setVertexAttribute( AVertexAttribute* vertexAttribute )
{
	m_vertexAttributes.append( vertexAttribute );
}

void AGeometry::calculateNormals(
	ASimpleTextureVertex* vertices, int vertCount, 
	GLuint* indices, int indCount )
{
	for ( int i = 0; i < indCount; i += 3 )
	{
		int index0 = indices[ i ],
			index1 = indices[ i + 1 ],
			index2 = indices[ i + 2 ];

		QVector3D v1 = vertices[ index1 ].position - vertices[ index0 ].position;
		QVector3D v2 = vertices[ index2 ].position - vertices[ index0 ].position;

		QVector3D normal = QVector3D::normal( v2, v1 );

		vertices[ index0 ].normal += normal;
		vertices[ index1 ].normal += normal;
		vertices[ index2 ].normal += normal;
	}

	for ( int i = 0; i < vertCount; i++ )
	{
		vertices[ i ].normal.normalize();
	}
}