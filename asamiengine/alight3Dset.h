#ifndef ALIGHT3DSET_H
#define ALIGHT3DSET_H

#include "aabstractlight.h"

#include <QList>

class ALight3DSet : public QList<AAbstractLight*>
{
};

#endif