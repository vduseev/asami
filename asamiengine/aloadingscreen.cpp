#include "aloadingscreen.h"

#include "anode.h"
#include "aabstractlight.h"
#include "atexturedquad.h"
#include "acamera.h"

#include <QList>

ALoadingScreen::ALoadingScreen()
	: m_metersToUnits( 0.05f )
	, m_cameraSpeed( 300.0f )
{
}

ALoadingScreen::~ALoadingScreen(void)
{
}

void ALoadingScreen::initialize()
{		
	m_camera = new ACamera( this );
	m_v = QVector3D();
    m_viewCenterFixed = false;
    m_panAngle = 0.0f;
    m_tiltAngle = 0.0f;

	// Initialize the camera position and orientation
    m_camera->setPosition( QVector3D( 0.0f, 0.0f, 10.0f ) );
    m_camera->setViewCenter( QVector3D( 0.0f, 0.0f, 0.0f ) );
    m_camera->setUpVector( QVector3D( 0.0f, 1.0f, 0.0f ) );

	ATexturedQuad* testquadFront = new ATexturedQuad( "textures/asami/asami_electro.png" );
	AAbstractScene::addObject3D( testquadFront );

	ATexturedQuad* testquadBack = new ATexturedQuad( "textures/asami/black.png" );
	testquadBack->rotate( 180.0f, 0, 1, 0 );
	AAbstractScene::addObject3D( testquadBack );

	m_node = new ANode();
	AAbstractScene::addNode( m_node );

	testquadFront->associate( m_node );
	testquadBack->associate( m_node );
}

void ALoadingScreen::update( float time )
{
	const float dt = time - m_time;
	m_time = time;

	m_node->rotate( dt * 50, 0, 1, 0 );

	AAbstractScene::setCameraPosition( m_camera->position() );
	AAbstractScene::setCameraViewMatrix( m_camera->viewMatrix() );
	AAbstractScene::setCameraProjectionMatrix( m_camera->projectionMatrix() );
	AAbstractScene::update( time );
}

void ALoadingScreen::render()
{
	AAbstractScene::render();
}

void ALoadingScreen::resize( int width, int height )
{
	float aspect = static_cast<float>( width ) / static_cast<float>( height );
    m_camera->setPerspectiveProjection( 45.0f, aspect, 0.01f, 3000.0f );
}
