#include "Line.h"

Line::Line(const uint& unitID_, const uint& materalID_,
           const QStringList& pointidList_)
{
    m_uObjectID = unitID_;
    m_uMaterialID = materalID_;
    m_sUnitPointIDList = pointidList_;
}

Line::~Line()
{
}
