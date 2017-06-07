#include "amaterial.h"

AMaterial::AMaterial()
    : m_shader( new QOpenGLShaderProgram )
{
    Properties.Color = QVector4D( 1, 0, 0, 1 );
    Properties.ShiningIntensity = 0.1f;
    Properties.ShiningPower = 1;
    Properties.Lightable = true;
    Properties.Textured = true;
    initializeOpenGLFunctions();
}

AMaterial::~AMaterial()
{
    m_shader->release();
}

void AMaterial::bind()
{
    m_shader->bind();

    if ( Properties.Textured && m_units.count() > 0 )
    {
        foreach ( const GLuint unit, m_units.keys() )
        {
            const ATextureUnit& textureImageUnit = m_units.value( unit );

            // Bind the texture
            glActiveTexture( GL_TEXTURE0 + unit );
            textureImageUnit.texture()->bind();

            // Bind the sampler
            textureImageUnit.sampler()->bind( unit );

            // Associate with sampler uniform in shader (if we know the name)
            if ( m_uniformNames.contains( unit ) )
                m_shader->setUniformValue( m_uniformNames.value( unit ).constData(), unit );
        }
    }

    if ( Properties.Lightable )
    {
        m_shader->setUniformValue( "matShiningInten", Properties.ShiningIntensity );
        m_shader->setUniformValue( "matShiningPower", Properties.ShiningPower );
    }
}

void AMaterial::release()
{
    m_shader->release();

    if ( m_units.count() > 0 )
    {
        foreach ( const GLuint unit, m_units.keys() )
        {
            const ATextureUnit& textureImageUnit = m_units.value( unit );
            textureImageUnit.texture()->release();
            textureImageUnit.sampler()->release( unit );
        }
    }
}

void AMaterial::setShaders( const QString& vertexShader,
                           const QString& fragmentShader )
{
    // Create a shader program
    if ( !m_shader->addShaderFromSourceFile( QOpenGLShader::Vertex, vertexShader ) )
        qCritical() << QObject::tr( "Could not compile vertex shader. Log:" ) << m_shader->log();

    if ( !m_shader->addShaderFromSourceFile( QOpenGLShader::Fragment, fragmentShader ) )
        qCritical() << QObject::tr( "Could not compile fragment shader. Log:" ) << m_shader->log();

    if ( !m_shader->link() )
        qCritical() << QObject::tr( "Could not link shader program. Log:" ) << m_shader->log();
}

void AMaterial::setShaders( const QString& vertexShader,
                           const QString& geometryShader,
                           const QString& fragmentShader )
{
    // Create a shader program
    if ( !m_shader->addShaderFromSourceFile( QOpenGLShader::Vertex, vertexShader ) )
        qCritical() << QObject::tr( "Could not compile vertex shader. Log:" ) << m_shader->log();

    if ( !m_shader->addShaderFromSourceFile( QOpenGLShader::Geometry, geometryShader ) )
        qCritical() << QObject::tr( "Could not compile geometry shader. Log:" ) << m_shader->log();

    if ( !m_shader->addShaderFromSourceFile( QOpenGLShader::Fragment, fragmentShader ) )
        qCritical() << QObject::tr( "Could not compile fragment shader. Log:" ) << m_shader->log();

    if ( !m_shader->link() )
        qCritical() << QObject::tr( "Could not link shader program. Log:" ) << m_shader->log();
}

void AMaterial::setShaders( const QString& vertexShader,
                           const QString& tessellationControlShader,
                           const QString& tessellationEvaluationShader,
                           const QString& geometryShader,
                           const QString& fragmentShader )
{
    // Create a shader program
    if ( !m_shader->addShaderFromSourceFile( QOpenGLShader::Vertex, vertexShader ) )
        qCritical() << QObject::tr( "Could not compile vertex shader. Log:" ) << m_shader->log();

    if ( !m_shader->addShaderFromSourceFile( QOpenGLShader::TessellationControl, tessellationControlShader ) )
        qCritical() << QObject::tr( "Could not compile tessellation control shader. Log:" ) << m_shader->log();

    if ( !m_shader->addShaderFromSourceFile( QOpenGLShader::TessellationEvaluation, tessellationEvaluationShader ) )
        qCritical() << QObject::tr( "Could not compile tessellation evaluation shader. Log:" ) << m_shader->log();

    if ( !m_shader->addShaderFromSourceFile( QOpenGLShader::Geometry, geometryShader ) )
        qCritical() << QObject::tr( "Could not compile geometry shader. Log:" ) << m_shader->log();

    if ( !m_shader->addShaderFromSourceFile( QOpenGLShader::Fragment, fragmentShader ) )
        qCritical() << QObject::tr( "Could not compile fragment shader. Log:" ) << m_shader->log();

    if ( !m_shader->link() )
        qCritical() << QObject::tr( "Could not link shader program. Log:" ) << m_shader->log();
}

void AMaterial::setShader( QOpenGLShaderProgram* shader )
{
    m_shader = shader;
}

void AMaterial::setTextureUnit( GLuint unit, ATexture* texture, ASampler* sampler )
{
    ATextureUnit configuration( texture, sampler );
    m_units.insert( unit, configuration );
}

void AMaterial::setTextureUnit( GLuint unit, ATexture* texture, ASampler* sampler, const QByteArray& uniformName )
{
    setTextureUnit( unit, texture, sampler );
    m_uniformNames.insert( unit, uniformName );
}

ATextureUnit AMaterial::textureUnit( GLuint unit ) const
{
    return m_units.value( unit, ATextureUnit() );
}
