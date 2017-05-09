#ifndef AABSTRACTSCENE_H
#define AABSTRACTSCENE_H

#include "anodeset.h"
#include "alight3Dset.h"
#include "aobject3Dset.h"

#include <QKeyEvent>
#include <QMouseEvent>

class ANode;
class AObject3D;
class AAbstractLight;

class AAbstractScene : public QObject
{
	Q_OBJECT

public:
	AAbstractScene( QObject* parent = 0 );
	~AAbstractScene();

	virtual void update( float time );
	virtual void render();
	virtual void resize( int width, int height )	= 0;

	virtual void keyPressEvent( Qt::Key key );
    virtual void keyReleaseEvent( Qt::Key key );
    virtual void mousePressEvent( QMouseEvent* e );
    virtual void mouseReleaseEvent( QMouseEvent* e );
    virtual void mouseMoveEvent( QMouseEvent* e );

	void addNode( ANode* node );
	void addObject3D( AObject3D* object );
	void addLight3D( AAbstractLight* light );

	void setCameraPosition( const QVector3D& position )			{ m_cameraPosition = position; }
	void setCameraViewMatrix( const QMatrix4x4& matrix )		{ m_viewMatrix = matrix; }
	void setCameraProjectionMatrix( const QMatrix4x4& matrix )	{ m_projectionMatrix = matrix; }

protected:
	float	m_time;
	bool	m_leftButtonPressed;
    QPoint	m_prevPos;
    QPoint	m_pos;

private:
	QMatrix4x4	m_projectionMatrix;
	QMatrix4x4	m_viewMatrix;
	QVector3D	m_cameraPosition;

	ANodeSet		m_nodes;
	AObject3DSet	m_objects;
	ALight3DSet		m_lights;
};

#endif