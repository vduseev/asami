#include "avertexattribute.h"

AVertexAttribute::AVertexAttribute(void)
{
}

AVertexAttribute::AVertexAttribute( const QByteArray& name, GLenum type, int offset, int tupleSize, int stride )
	: m_name( name )
	, m_type( type )
	, m_offset( offset )
	, m_tupleSize( tupleSize )
	, m_stride( stride )
{
}

AVertexAttribute::~AVertexAttribute(void)
{
}
