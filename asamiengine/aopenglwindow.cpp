#include "aopenglwindow.h"

#include "aabstractscene.h"
#include "aloadingscreen.h"
#include "atestscene.h"

#include <QCoreApplication>
#include <QKeyEvent>
#include <QOpenGLFunctions_4_0_Core>
#include <QOpenGLContext>
#include <QScreen>
#include <QTimer>

AOpenGLWindow::AOpenGLWindow(QWindow *parent)
    : QWindow(parent)
    , m_isFullscreen( false )
    , m_frame(0)
    , m_refreshRate( 60 )
    , m_leftButtonPressed( false )
    , m_isEngineInitialized( false )
{
    setSurfaceType(QWindow::OpenGLSurface);

    // Make sure we tell OpenGL about new OpenGLWindow sizes
    connect( this, SIGNAL( widthChanged( int ) ), this, SLOT( resizeEngine() ) );
    connect( this, SIGNAL( heightChanged( int ) ), this, SLOT( resizeEngine() ) );

    // Set window
    QSurfaceFormat format;
    format.setSamples( 4 );
    setFormat( format );
    resize( 1000, 750 );
    setTitle( "ASAMI render engine" );
    create();

    // Create OpenGL context
    m_context = new QOpenGLContext( this );
    m_context->setFormat( requestedFormat() );
    m_context->create();
    m_context->makeCurrent( this );

    QScreen* currentScreen = screen();
    m_refreshRate = (float)currentScreen->refreshRate();

    initializeEngine();
}

AOpenGLWindow::~AOpenGLWindow()
{
}

void AOpenGLWindow::initializeEngine()
{
    m_context->makeCurrent( this );

    initializeOpenGLFunctions();

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );

    ALoadingScreen* loadingScreen = new ALoadingScreen();
    loadingScreen->initialize();

    ATestScene* testScene = new ATestScene();
    testScene->initialize();

    m_engineScene = testScene;
    m_loadingScene = loadingScreen;

    m_currentScene = m_engineScene;

    // This QTime object counts the time
    m_time.start();

    m_isEngineInitialized = true;
    // update viewport and scene aspect ratio
    resizeEngine();

    // This timer drives the scene updates
    QTimer* timer = new QTimer( this );
    connect( timer, SIGNAL( timeout() ), this, SLOT( tick() ) );
    //timer->start( 1000 / m_refreshRate );
    timer->start( 10 );
}

Q_SLOT void AOpenGLWindow::tick()
{
    updateEngine();
    renderEngine();
}

Q_SLOT void AOpenGLWindow::resizeEngine()
{
    if ( m_isEngineInitialized )
    {
        glViewport( 0, 0, width(), height() );
        m_currentScene->resize( width(), height() );
    }
}

void AOpenGLWindow::updateEngine()
{
    float time = m_time.elapsed() / 1000.0f;

    m_currentScene->update( time );
}

void AOpenGLWindow::renderEngine()
{
    if (!isExposed()) return;

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_context->makeCurrent(this);

    m_currentScene->render();

    m_context->swapBuffers(this);
    ++m_frame;
}

//void AOpenGLWindow::initializeEngine()
//{
//    if ( !m_isEngineInitialized )
//    {
//        initializeEngine();
//
//        // test
//        m_isSceneInitialized = true;
//    }
//    else if (!m_isSceneInitialized )
//    {
//        AScene* scene = new AScene();
//        scene->initialize();
//
//        m_engineScene = scene;
//        m_currentScene = scene;
//
//        resizeOpenGL();
//        m_isSceneInitialized = true;
//    }
//}

/*--------------------------------------
 * Input events functions
 *-------------------------------------*/

void AOpenGLWindow::keyPressEvent( QKeyEvent* e )
{
    switch ( e->key() )
    {
        case Qt::Key_Escape:
            QCoreApplication::instance()->quit();
            break;

        default:
            QWindow::keyPressEvent( e );
    }

    m_currentScene->keyPressEvent( (Qt::Key)e->key() );
}

void AOpenGLWindow::keyReleaseEvent( QKeyEvent* e )
{
    switch ( e->key() )
    {
        case Qt::Key_Return:
            if ( !m_isFullscreen )
            {
                QWindow::showFullScreen();
                m_isFullscreen = true;
            }
            else
            {
                QWindow::showNormal();
                m_isFullscreen = false;
            }
            break;

        default:
            QWindow::keyReleaseEvent( e );
    }

    m_currentScene->keyReleaseEvent( (Qt::Key)e->key() );
}

void AOpenGLWindow::mousePressEvent( QMouseEvent* e )
{
    if ( e->button() == Qt::LeftButton )
    {
        m_leftButtonPressed = true;
        m_pos = m_prevPos = e->pos();
    }
    QWindow::mousePressEvent( e );

    m_currentScene->mousePressEvent( e );
}

void AOpenGLWindow::mouseReleaseEvent( QMouseEvent* e )
{
    if ( e->button() == Qt::LeftButton )
        m_leftButtonPressed = false;
    QWindow::mouseReleaseEvent( e );

    m_currentScene->mouseReleaseEvent( e );
}

void AOpenGLWindow::mouseMoveEvent( QMouseEvent* e )
{
    if ( m_leftButtonPressed )
    {
        m_pos = e->pos();
        m_prevPos = m_pos;
    }
    QWindow::mouseMoveEvent( e );

    m_currentScene->mouseMoveEvent( e );
}
