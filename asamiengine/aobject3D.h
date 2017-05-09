#ifndef AOBJECT3D_H
#define AOBJECT3D_H

#include <QOpenGLFunctions_4_0_Core>
#include <QMatrix4x4>

class ANode;
class ALight3DSet;

class AMaterial;
class AGeometry;

class AObject3D : protected QOpenGLFunctions_4_0_Core
{
public:
	AObject3D();
	AObject3D( 
		bool allowPhysics );
	~AObject3D();
		
	// Called in AAbstractScene in 'update' funtion
	virtual void update( float time );
	
	void draw(  
		const QMatrix4x4& projectionMatrix, 
		const QMatrix4x4& viewMatrix,
		const QVector3D& cameraPosition,
		const ALight3DSet& lights );

	void scale( float x, float y, float z )	{ m_localScale.scale( x, y, z ); }
	void scale( const QVector3D& vector )	{ m_localScale.scale( vector ); }
	void scale( float factor )				{ m_localScale.scale( factor ); }

	void rotate( float angle, float x, float y, float z )	{ m_localRotation.rotate( angle, x, y, z ); }
	void rotate( float angle, const QVector3D& vector )		{ m_localRotation.rotate( angle, vector ); }
	void rotate( const QQuaternion& quaternion )			{ m_localRotation.rotate( quaternion ); }

	void translate( float x, float y, float z )	{ m_localTranslation.translate( x, y, z ); }
	void translate( const QVector3D& vector )	{ m_localTranslation.translate( vector ); }

	void allowPhysics()		{ m_allowPhysics = true;  if ( m_initCounter < 2 ) m_initCounter++; }
	void ignorePhysics()	{ m_allowPhysics = false; if ( m_initCounter < 2 ) m_initCounter++; }

	void associate( ANode* node )	{ m_associatedNode = node; m_isAssociated = true; }

protected:
	void setMaterial( AMaterial* material );
	void setGeometry( AGeometry* geometry );

private:    
	ANode*		m_associatedNode;	
	QMatrix4x4	m_localScale;
	QMatrix4x4	m_localRotation;
	QMatrix4x4	m_localTranslation;

	AMaterial* m_material;
	AGeometry* m_geometry;

	bool	m_isAssociated;
	
	// basic parameters
	bool	m_allowPhysics;
	int		m_initCounter;
};

#endif