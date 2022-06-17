#include "Tetrahedron.h"

Tetrahedron::Tetrahedron(const uint &unitID_, const uint &materialID_, const QStringList &pointidList_,
                         const float& red_, const float& green_, const float& blue_)
{
    m_uObjectID = unitID_;
    m_uMaterialID = materialID_;
    m_sUnitPointIDList = pointidList_;
    m_fRed = red_;
    m_fGreen = green_;
    m_fBlue = blue_;
//    m_cUnitColor = color_;
}

Tetrahedron::~Tetrahedron()
{
}

void Tetrahedron::getAllShow(QHash<QString, TRIANGLE *> &triangleHash_, QHash<QString, QUAD *> &quadHash_)
{
    Q_UNUSED(quadHash_)
    getTriangleShow(m_sUnitPointIDList.at(2), m_sUnitPointIDList.at(1), m_sUnitPointIDList.at(0), m_fRed, m_fGreen, m_fBlue, triangleHash_);
    getTriangleShow(m_sUnitPointIDList.at(2), m_sUnitPointIDList.at(3), m_sUnitPointIDList.at(1), m_fRed, m_fGreen, m_fBlue, triangleHash_);
    getTriangleShow(m_sUnitPointIDList.at(0), m_sUnitPointIDList.at(3), m_sUnitPointIDList.at(2), m_fRed, m_fGreen, m_fBlue, triangleHash_);
    getTriangleShow(m_sUnitPointIDList.at(1), m_sUnitPointIDList.at(3), m_sUnitPointIDList.at(0), m_fRed, m_fGreen, m_fBlue, triangleHash_);
}

