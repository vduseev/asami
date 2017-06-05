#ifndef ALOADINGSCREEN_H
#define ALOADINGSCREEN_H

#include "aabstractscene.h"

class ACamera;
class ANode;

class ALoadingScreen : public AAbstractScene
{
public:
    ALoadingScreen();
    ~ALoadingScreen();

    void initialize();
    void update( float time );
    void render();
    void resize( int width, int height );

private:
    float m_time;

    ANode* m_node;

    ACamera*    m_camera;
    QVector3D   m_v;
    bool        m_viewCenterFixed;
    float       m_panAngle;
    float       m_tiltAngle;
    const float m_metersToUnits;
    const float m_cameraSpeed;
};

#endif
