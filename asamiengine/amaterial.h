#ifndef AMATERIAL_H
#define AMATERIAL_H

#include "atexture.h"
#include "asampler.h"
#include "atextureunit.h"
#include "ageometry.h"
#include "avertexattribute.h"

#include <QOpenGLFunctions_4_0_Core>
#include <QOpenGLShaderProgram>
#include <QList>

class AMaterial : protected QOpenGLFunctions_4_0_Core
{
public:
    AMaterial();
	~AMaterial();

	struct {
		QVector4D	Color;
		// #intensity - does material absorb light ( 'yes' if equals 0 )
		float		ShiningIntensity;
		// #power - how powerfully it shines
		float		ShiningPower;
		
		bool		Lightable;

		bool		Textured;
	} Properties;

    void bind();
	void release();

    void setShaders( const QString& vertexShader,
                     const QString& fragmentShader );
    void setShaders( const QString& vertexShader,
                     const QString& geometryShader,
                     const QString& fragmentShader );
    void setShaders( const QString& vertexShader,
                     const QString& tessellationControlShader,
                     const QString& tessellationEvaluationShader,
                     const QString& geometryShader,
                     const QString& fragmentShader );

    void setShader( QOpenGLShaderProgram* shader );
    QOpenGLShaderProgram* shader() { return m_shader; }

    void setTextureUnit( GLuint unit, ATexture* texture, ASampler* sampler );
    void setTextureUnit( GLuint unit, ATexture* texture, ASampler* sampler, const QByteArray& uniformName );
    ATextureUnit textureUnit( GLuint unit ) const;

private:
    QOpenGLShaderProgram* m_shader;

    QMap<GLuint, ATextureUnit> m_units;
    QMap<GLuint, QByteArray> m_uniformNames;
};

#endif
