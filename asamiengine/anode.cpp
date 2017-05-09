#include "anode.h"

ANode::ANode()
{
}

ANode::~ANode()
{
}

void ANode::compute( const QMatrix4x4& parentMatrix )
{
	m_computedMatrix = parentMatrix * matrix();
}

void ANode::computeRotation( const QMatrix4x4& parentRotationMatrix )
{
	m_computedRotationMatrix = parentRotationMatrix * m_rotation;
}