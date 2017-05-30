#include "aabstractscene.h"

#include "anode.h"
#include "aobject3D.h"
#include "aabstractlight.h"

#include "anodeset.h"
#include "alight3Dset.h"
#include "aobject3Dset.h"

#include <qdebug.h>

AAbstractScene::AAbstractScene( QObject* parent )
    : QObject( parent )
    , m_time( 0 )
{
}

AAbstractScene::~AAbstractScene(void)
{
}

void AAbstractScene::update( float time )
{
    float dt = time - m_time;
    m_time = time;

    // initialize identity matrix
    QMatrix4x4 parent, parentRotation;

    // recompute all nodes
    for ( int i = 0; i < m_nodes.count(); i++ )
    {
        ANode* node = m_nodes.at( i );
        node->compute( parent );
        node->computeRotation( parentRotation );
        parent = node->computedMatrix();
        parentRotation = node->computedRotationMatrix();
    }

    // update objects
    for ( int i = 0; i < m_objects.count(); i++ )
    {
        AObject3D* object = m_objects.at( i );
        object->update( time );
    }

    float fps = 1.0f / dt;
    qDebug() << "Frames per second: " << fps;
}

void AAbstractScene::render()
{
    for ( int i = 0; i < m_objects.count(); i++ )
    {
        AObject3D* object = m_objects.at( i );
        object->draw( m_projectionMatrix, m_viewMatrix, m_cameraPosition, m_lights );
    }
}

/*-------------------------------
 * 'Add' functions
 *-------------------------------*/

void AAbstractScene::addNode( ANode* node )
{
    m_nodes.append( node );
}

void AAbstractScene::addObject3D( AObject3D* object )
{
    m_objects.append( object );
}

void AAbstractScene::addLight3D( AAbstractLight* light )
{
    m_lights.append( light );
}

/*-----------------------------------------------
 * Input events funtions must be implemented here
 * in abstract scene.
 *-----------------------------------------------*/

void AAbstractScene::keyPressEvent( Qt::Key key ) {}

void AAbstractScene::keyReleaseEvent( Qt::Key key ) {}

void AAbstractScene::mousePressEvent( QMouseEvent* e ) {}

void AAbstractScene::mouseReleaseEvent( QMouseEvent* e ) {}

void AAbstractScene::mouseMoveEvent( QMouseEvent* e ) {}
