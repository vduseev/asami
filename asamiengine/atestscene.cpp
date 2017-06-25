#include "atestscene.h"

#include "atexturedquad.h"
#include "acamera.h"
#include "anode.h"
#include "adirectionallight.h"

#include <qdebug.h>

ATestScene::ATestScene()
    : m_time( 0.0f )
    , m_metersToUnits( 0.05f )
{
}

ATestScene::~ATestScene()
{
}

void ATestScene::initialize()
{
    m_camera = new ACamera( this );
    m_v = QVector3D();
    m_viewCenterFixed = false;
    m_panAngle = 0.0f;
    m_tiltAngle = 0.0f;
    m_cameraSpeed = m(3);

    // Initialize the camera position and orientation
    m_camera->setPosition( QVector3D( m(6), m(1.9f), m(0) ) );
    m_camera->setViewCenter( QVector3D( m(0), m(1.8f), m(0) ) );
    m_camera->setUpVector( QVector3D( 0.0f, 1.0f, 0.0f ) );
    m_camera->setClipSpace( m(-500), m(500), m(1.8f), m(1000), m(-500), m(500) );

    ATexturedQuad* scenePlane = new ATexturedQuad(
        "textures/basic/grid.png",
        QSize( 700, 700 ) );
    scenePlane->scale( m(1000) );
    scenePlane->rotate( -90, 1, 0, 0 );
    AAbstractScene::addObject3D( scenePlane );

    ATexturedQuad* asamiBillboardFront = new ATexturedQuad( "textures/asami/asami_stay.png" );
    float aspect = 500.0f / 646.0f;
    asamiBillboardFront->scale( m(1)*aspect, m(1), 0 );
    m_banner = asamiBillboardFront;
    AAbstractScene::addObject3D( asamiBillboardFront );

    ATexturedQuad* asamiBillboardBack = new ATexturedQuad( "textures/basic/jupiter2.jpg" );
    asamiBillboardBack->scale( m(1)*aspect, m(1), 0 );
    asamiBillboardBack->rotate( 180, 0, 1, 0 );
    m_bannerBack = asamiBillboardBack;
    AAbstractScene::addObject3D( asamiBillboardBack );

    m_asamiNode = new ANode();
    m_asamiNode->translate( m(0), m(1.5f), m(0) );
    AAbstractScene::addNode( m_asamiNode );

    asamiBillboardFront->associate( m_asamiNode );
    asamiBillboardBack->associate( m_asamiNode );

    ADirectionalLight* light = new ADirectionalLight();
    light->setColor( QVector3D( 1, 1, 1 ) );
    light->setAmbientIntensity( 0.1f );
    light->setDiffuseIntensity( 0.35f );
    light->setDirection( QVector3D( -1, 0, 0 ) );
    AAbstractScene::addLight3D( light );

    m_leftButtonPressed = false;
}

void ATestScene::update( float time )
{
    const float dt = time - m_time;
    m_time = time;

    // Update the camera position and orientation
    ACamera::CameraTranslationOption option = m_viewCenterFixed
                                           ? ACamera::DontTranslateViewCenter
                                           : ACamera::TranslateViewCenter;
    m_camera->translate( m_v * dt, option );

    if ( !qFuzzyIsNull( m_panAngle ) )
    {
        m_camera->pan( m_panAngle, QVector3D( 0.0f, 1.0f, 0.0f ) );
        m_panAngle = 0.0f;
    }

    if ( !qFuzzyIsNull( m_tiltAngle ) )
    {
        m_camera->tilt( m_tiltAngle );
        m_tiltAngle = 0.0f;
    }
    //m_camera->clip();

    //m_asamiNode->rotate( 50.0f * dt, 0, 1, 0 );
    m_banner->rotate( 50.0f * dt, 0, 1, 0 );
    m_bannerBack->rotate( 50.0f * dt, 0, 1, 0 );

    AAbstractScene::update( time );
}

void ATestScene::render()
{
    // Pass in the usual transformation matrices
    AAbstractScene::setCameraPosition( m_camera->position() );
    AAbstractScene::setCameraViewMatrix( m_camera->viewMatrix() );
    AAbstractScene::setCameraProjectionMatrix( m_camera->projectionMatrix() );
    AAbstractScene::render();
}

void ATestScene::resize( int width, int height )
{
    float aspect = static_cast<float>( width ) / static_cast<float>( height );
    m_camera->setPerspectiveProjection( 45.0f, aspect, 0.01f, 3000.0f );
}

void ATestScene::keyPressEvent( Qt::Key key )
{
    switch ( key )
    {
        case Qt::Key_D:
            setSideSpeed( 1 );
            break;

        case Qt::Key_A:
            setSideSpeed( -1 );
            break;

        case Qt::Key_W:
            setForwardSpeed( 1 );
            break;

        case Qt::Key_S:
            setForwardSpeed( -1 );
            break;

        case Qt::Key_PageUp:
            setVerticalSpeed( 1 );
            break;

        case Qt::Key_PageDown:
            setVerticalSpeed( -1 );
            break;

        case Qt::Key_Shift:
            setViewCenterFixed( true );
            break;
    }
}

void ATestScene::keyReleaseEvent( Qt::Key key )
{
    switch ( key )
    {
        case Qt::Key_D:
        case Qt::Key_A:
            setSideSpeed( 0.0f );
            break;

        case Qt::Key_W:
        case Qt::Key_S:
            setForwardSpeed( 0.0f );
            break;

        case Qt::Key_PageUp:
        case Qt::Key_PageDown:
            setVerticalSpeed( 0.0f );
            break;

        case Qt::Key_Shift:
            setViewCenterFixed( false );
            break;
    }
}

void ATestScene::mousePressEvent( QMouseEvent* e )
{
    if ( e->button() == Qt::LeftButton )
    {
        m_leftButtonPressed = true;
        m_pos = m_prevPos = e->pos();
    }
}

void ATestScene::mouseReleaseEvent( QMouseEvent* e )
{
    if ( e->button() == Qt::LeftButton )
        m_leftButtonPressed = false;
}

void ATestScene::mouseMoveEvent( QMouseEvent* e )
{
    if ( m_leftButtonPressed )
    {
        m_pos = e->pos();
        float dx = 0.2f * ( m_pos.x() - m_prevPos.x() );
        float dy = -0.2f * ( m_pos.y() - m_prevPos.y() );
        m_prevPos = m_pos;

        pan( dx );
        tilt( dy );
    }
}

float ATestScene::m( float distance )
{
    return m_metersToUnits * distance;
}
