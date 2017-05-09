#ifndef ADIRECTIONALLIGHT_H
#define ADIRECTIONALLIGHT_H

#include "aabstractlight.h"

class ADirectionalLight : public AAbstractLight
{
public:
	ADirectionalLight();
	~ADirectionalLight();

	void setDirection( QVector3D direction );
	QVector3D direction() const { return m_direction; }

protected:
	QVector3D m_direction;
};

#endif
