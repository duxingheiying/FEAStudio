/******************************************************************************************************
 *
 *
 *
 * *****************************************************************************************************/

#ifndef PYRAMID_H
#define PYRAMID_H

#include "Object.h"

class Pyramid : public EntityObject
{
public:
    explicit Pyramid(const uint& unitID_,
                     const uint& materialID_,
                     const QStringList& pointidList_);
    ~Pyramid();
};

#endif // PYRAMID_H
