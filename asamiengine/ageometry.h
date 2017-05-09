#ifndef AGEOMETRY_H
#define AGEOMETRY_H

#include "avertexattribute.h"

#include <QOpenGLBuffer>
#include <QList>

class ASimpleTextureVertex;

class AGeometry
{
public:
	AGeometry();
	~AGeometry();

	void setUsagePattern( QOpenGLBuffer::UsagePattern pattern, QOpenGLBuffer::Type bufferType );

	void setVertices( const void* data, int count, int size, int offsetElements = 0 );
	void setIndices( GLuint* indices, int count, int offsetElements = 0 );
	void setVertexAttribute( const QByteArray& name, int offset, int tupleSize, int stride = 0 );

	void setVetexBuffer( QOpenGLBuffer* vertexBuffer ) { m_vertexBuffer = vertexBuffer; }
	QOpenGLBuffer* vertexBuffer() { return m_vertexBuffer; }

	void setIndexBuffer( QOpenGLBuffer* indexBuffer ) { m_indexBuffer = indexBuffer; }
	QOpenGLBuffer* indexBuffer() { return m_indexBuffer; }

	void setVertexAttribute( AVertexAttribute* vertexAttribute );
	QList<AVertexAttribute*> vertexAttributes() { return m_vertexAttributes; }

	int vertexCount() const { return m_vertexCount; }
	int indexCount() const { return m_indexCount; }

	static void calculateNormals( 
		ASimpleTextureVertex* vertices, int vertexCount, 
		GLuint* indices, int indexCount );

private:
	QOpenGLBuffer* m_vertexBuffer;
	QOpenGLBuffer* m_indexBuffer;

	QList<AVertexAttribute*> m_vertexAttributes;

	int m_vertexBufferAllocatedCount;
	int m_indexBufferAllocatedCount;
	
	int m_vertexCount;
	int m_indexCount;
};

#endif

