#ifndef ASIMPLECOLORVERTEX_H
#define ASIMPLECOLORVERTEX_H

#include "aabstractvertex.h"

#include <QVector3D>
#include <qopengl.h>

class ASimpleColorVertex : public AAbstractVertex
{
public:	
	QVector3D coordinate;
	QVector3D color;
};

#endif

