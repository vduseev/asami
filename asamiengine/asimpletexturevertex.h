#ifndef ASIMPLETEXTUREVERTEX_H
#define ASIMPLETEXTUREVERTEX_H

#include "aabstractvertex.h"

#include <QVector2D>
#include <qopengl.h>

class ASimpleTextureVertex : public AAbstractVertex
{
public:	
	QVector3D position;
	QVector3D normal;
	QVector2D texCoords;

	int size() { return 
		sizeof( QVector3D ) + 
		sizeof( QVector3D ) + 
		sizeof( QVector2D ); 
	}
};

#endif