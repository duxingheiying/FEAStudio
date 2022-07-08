#ifndef PENTAGONALPYRAMID_H
#define PENTAGONALPYRAMID_H

#include "Object.h"

class PentagonalPyramid : public EntityObject
{
public:
    explicit PentagonalPyramid(const uint &unitID_,
                               const uint &materialID_,
                               const QStringList &pointidList_);
    ~PentagonalPyramid();
};

#endif // PENTAGONALPYRAMID_H
