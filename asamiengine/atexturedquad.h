#ifndef ATEXTUREDQUAD_H
#define ATEXTUREDQUAD_H

#include "aobject3D.h"

#include <QString>
#include <QVector2D>
#include <QVector3D>

class ATexturedQuad : public AObject3D
{
public:
	ATexturedQuad( QSize textureCoordinates = QSize( 1, 1 ) );
	ATexturedQuad(
		const QString& textureFileName,
		QSize textureCoordinates = QSize( 1, 1 ) );
	ATexturedQuad(
		const QString& textureFileName,
		const QString& vertexShader, 
		const QString& fragmentShader,
		QSize textureCoordinates = QSize( 1, 1 ) );
	~ATexturedQuad();

	class Vertex
	{
	public:
		QVector3D pos;
		QVector3D norm;
		QVector2D tex;
	};

private:
	void prepareGeometry( QSize textureCoordinates );
	void prepareMaterial( 
		const QString& textureFileName,
		const QString& vertexShader, 
		const QString& fragmentShader );
};

#endif

