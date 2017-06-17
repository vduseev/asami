#ifndef ASAMPLER_H
#define ASAMPLER_H

#include <QOpenGLFunctions_4_0_Core>

class ASampler : protected QOpenGLFunctions_4_0_Core
{
public:
    ASampler(void);

    void create();
    void destroy();
    GLuint samplerId() const { return m_samplerId; }
    void bind( GLuint unit );
    void release( GLuint unit );

    enum CoordinateDirection
    {
        DirectionS = GL_TEXTURE_WRAP_S,
        DirectionT = GL_TEXTURE_WRAP_T,
        DirectionR = GL_TEXTURE_WRAP_R
    };

    void setWrapMode( CoordinateDirection direction, GLenum wrapMode );

    void setMinificationFilter( GLenum filter );
    void setMagnificationFilter( GLenum filter );

    void setSamplerParameterF( GLenum parameterName, GLfloat param );

private:
    GLuint m_samplerId;
};

#endif
