#ifndef AVERTEXATTRIBUTE_H
#define AVERTEXATTRIBUTE_H

#include <QObject>
#include <qopengl.h>

class AVertexAttribute
{
public:
	AVertexAttribute(void);
	AVertexAttribute( const QByteArray& name, GLenum type, int offset, int tupleSize, int stride = 0 );
	~AVertexAttribute(void);

	void setName( const QByteArray& name ) { m_name = name; }
	const char* name() { return m_name.data(); }

	void setType( GLenum type ) { m_type = type; }
	GLenum type() const { return m_type; }

	void setOffset( int offset ) { m_offset = offset; }
	int offset() const { return m_offset; }

	void setTupleSize( int tupleSize ) { m_tupleSize = tupleSize; }
	int tupleSize() const { return m_tupleSize; }

	void setStride( int stride ) { m_stride = stride; }
	int stride() const { return m_stride; }

private:
	QByteArray m_name;
	GLenum m_type;
	int m_offset;
	int m_tupleSize;
	int m_stride;
};

#endif

