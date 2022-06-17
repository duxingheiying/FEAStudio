#include "Pyramid.h"

Pyramid::Pyramid(const uint &unitID_, const uint &materialID_,
                 const QStringList &pointidList_)
{
    m_uObjectID = unitID_;
    m_uMaterialID = materialID_;
    m_sUnitPointIDList = pointidList_;
}

Pyramid::~Pyramid()
{
}
