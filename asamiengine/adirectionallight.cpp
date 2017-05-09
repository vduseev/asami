#include "adirectionallight.h"

ADirectionalLight::ADirectionalLight()
	: AAbstractLight()
{
	m_type = Directional;
}

ADirectionalLight::~ADirectionalLight()
{
}

void ADirectionalLight::setDirection( QVector3D direction )
{
	m_direction = direction.normalized();
}
