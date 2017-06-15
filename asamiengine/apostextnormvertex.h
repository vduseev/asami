#ifndef APOSTEXTNORMVERTEX_H
#define APOSTEXTNORMVERTEX_H

#include "aabstractvertex.h"

#include <QVector3D>
#include <QVector2D>
#include <qopengl.h>

class APosTextNormVertex : public AAbstractVertex
{
public:
    QVector3D position;
    QVector3D normal;
    QVector2D textCoord;
};

#endif
