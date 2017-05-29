#ifndef AABSTRACTLIGHT_H
#define AABSTRACTLIGHT_H

#include <QVector3D>

class AAbstractLight
{
public:
    AAbstractLight(void);
    ~AAbstractLight(void);

    enum LightType
    {
        Ambient,
        Directional,
        Point,
        LightTube
    };

    LightType type() const { return m_type; }

    void setColor( QVector3D color ) { m_color = color; }
    QVector3D color() const { return m_color; }

    void setAmbientIntensity( float intensity ) { m_ambientIntensity = intensity; }
    float ambientIntensity() const { return m_ambientIntensity; }

    void setDiffuseIntensity( float intensity ) { m_diffuseIntensity = intensity; }
    float diffuseIntensity() const { return m_diffuseIntensity; }

    void setSpecularIntensity( float intensity ) { m_specularIntensity = intensity; }
    float specularIntensity() const { return m_specularIntensity; }

protected:
    QVector3D m_color;
    float m_ambientIntensity;
    float m_diffuseIntensity;
    float m_specularIntensity;
    LightType m_type;
};

#endif
