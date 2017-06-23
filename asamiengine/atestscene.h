#ifndef ATESTSCENE_H
#define ATESTSCENE_H

#include "aabstractscene.h"

#include <QList>
#include <QMatrix4x4>
#include <QVector3D>
#include <QVector2D>

class ACamera;
class ANode;

class ATestScene : public AAbstractScene
{
    Q_OBJECT

public:
    ATestScene();
    ~ATestScene();

    void initialize();
    void update( float time );
    void render();
    void resize( int width, int height );

    // Camera motion control
    void setSideSpeed( float dir )        { m_v.setX( dir * m_cameraSpeed ); }
    void setVerticalSpeed( float dir )    { m_v.setY( dir * m_cameraSpeed ); }
    void setForwardSpeed( float dir )    { m_v.setZ( dir * m_cameraSpeed ); }
    void setViewCenterFixed( bool b )    { m_viewCenterFixed = b; }

    // Camera orientation control
    void pan( float angle ) { m_panAngle = angle; }
    void tilt( float angle ) { m_tiltAngle = angle; }

    void keyPressEvent( Qt::Key key );
    void keyReleaseEvent( Qt::Key key );
    void mousePressEvent( QMouseEvent* e );
    void mouseReleaseEvent( QMouseEvent* e );
    void mouseMoveEvent( QMouseEvent* e );

    float m( float distance );

private:
    ANode* m_asamiNode;
    AObject3D* m_banner;
    AObject3D* m_bannerBack;

    ACamera*    m_camera;
    QVector3D    m_v;
    bool    m_viewCenterFixed;
    float    m_panAngle;
    float    m_tiltAngle;
    float    m_cameraSpeed;

    QMatrix4x4 m_viewportMatrix;
    QVector2D m_viewportSize;

    float m_time;
    const float m_metersToUnits;
};

#endif
