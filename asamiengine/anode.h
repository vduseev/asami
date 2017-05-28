#ifndef ANODE_H
#define ANODE_H

#include <QMatrix4x4>
#include <QQuaternion>

// TODO: change parameter isChanged when matrix is changed

class ANode {
public:
    ANode();
    ~ANode();

    QMatrix4x4& computedMatrix()            { return m_computedMatrix; }
    QMatrix4x4& computedRotationMatrix()    { return m_computedRotationMatrix; }
    QMatrix4x4& matrix()                    { return m_translation * m_rotation * m_scale; }

    void compute( const QMatrix4x4& parentMatrix );
    void computeRotation( const QMatrix4x4& parentRotationMatrix );

    void scale( float x, float y, float z )     { m_scale.scale( x, y, z ); }
    void scale( const QVector3D& vector )       { m_scale.scale( vector ); }
    void scale( float factor )                  { m_scale.scale( factor ); }

    void rotate( float angle, float x, float y, float z )   { m_rotation.rotate( angle, x, y, z ); }
    void rotate( float angle, const QVector3D& vector )     { m_rotation.rotate( angle, vector ); }
    void rotate( const QQuaternion& quaternion )            { m_rotation.rotate( quaternion ); }

    void translate( float x, float y, float z )     { m_translation.translate( x, y, z ); }
    void translate( const QVector3D& vector )       { m_translation.translate( vector ); }

private:
    QMatrix4x4 m_scale;
    QMatrix4x4 m_rotation;
    QMatrix4x4 m_translation;

    QMatrix4x4 m_computedMatrix;
    QMatrix4x4 m_computedRotationMatrix;
};

#endif
