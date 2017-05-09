#include "asampler.h"

ASampler::ASampler()
{
	initializeOpenGLFunctions();
}

void ASampler::create()
{
    glGenSamplers( 1, &m_samplerId );
}

void ASampler::destroy()
{
    if ( m_samplerId )
    {
        glDeleteSamplers( 1, &m_samplerId );
        m_samplerId = 0;
    }
}

void ASampler::bind( GLuint unit )
{
    glBindSampler( unit, m_samplerId );
}

void ASampler::release( GLuint unit )
{
    glBindSampler( unit, 0 );
}

void ASampler::setWrapMode( CoordinateDirection direction, GLenum wrapMode )
{
    glSamplerParameteri( m_samplerId, direction, wrapMode );
}

void ASampler::setMinificationFilter( GLenum filter )
{
    glSamplerParameteri( m_samplerId, GL_TEXTURE_MIN_FILTER, filter );
}

void ASampler::setMagnificationFilter( GLenum filter )
{
    glSamplerParameteri( m_samplerId, GL_TEXTURE_MAG_FILTER, filter );
}

void ASampler::setSamplerParameterF( GLenum parameterName, GLfloat param )
{
	glSamplerParameterf( m_samplerId, parameterName, param );
}