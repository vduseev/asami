#ifndef ATEXTURE_H
#define ATEXTURE_H

#include <QOpenGLFunctions_4_0_Core>
#include <QImage>

class ATexture : protected QOpenGLFunctions_4_0_Core
{
public:
	enum TextureType
    {
        Texture1D      = GL_TEXTURE_1D,
        Texture2D      = GL_TEXTURE_2D,
        Texture3D      = GL_TEXTURE_3D,
        TextureCubeMap = GL_TEXTURE_CUBE_MAP
    };

    ATexture( TextureType type = Texture2D );
    ~ATexture();

    TextureType type() const { return m_type; }

    void create();
    void destroy();
    GLuint textureId() const { return m_textureId; }
    void bind();
    void release();

	void activeTexture( GLenum texture );
    void initializeToEmpty( const QSize& size );
    void setImage( const QImage& image );
    void setCubeMapImage( GLenum face, const QImage& image );
    void setRawData2D( GLenum target, int mipmapLevel, GLenum internalFormat,
                       int width, int height, int borderWidth,
                       GLenum format, GLenum type, const void* data );

    void generateMipMaps();
	static QImage convertToGLFormat(const QImage& img);

private:

    TextureType m_type;
    GLuint m_textureId;
};

#endif
