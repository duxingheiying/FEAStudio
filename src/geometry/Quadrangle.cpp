#include "Quadrangle.h"

#include <set>

using namespace std;

Quadrangle::Quadrangle(const uint& quadID_,
                       const uint& materialID_,
                       const QStringList& stringList_,
                       const float &red_, const float &green_, const float &blue_)
{
    m_uObjectID = quadID_;
    m_uMaterialID = materialID_;
    m_sUnitPointIDList = stringList_;
    m_fRed = red_;
    m_fGreen = green_;
    m_fBlue = blue_;
//    m_cUnitColor = red_;
//    calculateIDName();
}

void Quadrangle::getAllShow(QHash<QString, TRIANGLE *> &triangleHash_, QHash<QString, QUAD *> &quadHash_)
{
    Q_UNUSED(triangleHash_)
    getQuadrangleShow(m_sUnitPointIDList.at(0),m_sUnitPointIDList.at(1), m_sUnitPointIDList.at(2),
                      m_sUnitPointIDList.at(3), m_fRed, m_fGreen, m_fBlue, quadHash_);
}

void Quadrangle::calculateIDName()
{
    set<QString> _set;
    _set.insert(m_sUnitPointIDList.at(0));
    _set.insert(m_sUnitPointIDList.at(1));
    _set.insert(m_sUnitPointIDList.at(2));
    _set.insert(m_sUnitPointIDList.at(3));
    set<QString>::iterator _itor = _set.begin();
    m_sjudgeMentName = (*_itor)+tr(" ")+(*_itor++)+tr(" ")+(*_itor++)+tr(" ")+(*_itor++);
}

void Quadrangle::Show()
{
}

void Quadrangle::getTriangleShow(const QString& firstPointID_, const QString& secondPointID_, const QString& thirdPointID_,
                                   const float& red_, const float& green_, const float& blue_,  QHash<QString, TRIANGLE*>& triangleHash_)
{
    QString _sjudgeMentName;
    set<QString> _set;
    _set.insert(firstPointID_);  // the triangle first point id
    _set.insert(secondPointID_);  // the triangle second point id
    _set.insert(thirdPointID_);  // the triangle third point id
    set<QString>::iterator _itor = _set.begin();
    _sjudgeMentName = (*_itor)+tr(" ")+(*_itor++)+tr(" ")+(*_itor++);
    _sjudgeMentName = _sjudgeMentName.trimmed();
    QHash<QString, TRIANGLE*>::iterator _itors = triangleHash_.find(_sjudgeMentName);
    if ( _itors == triangleHash_.end() ) {
        TRIANGLE* _triangle = new TRIANGLE(firstPointID_.toUInt(), secondPointID_.toUInt(), thirdPointID_.toUInt(), red_, green_, blue_);
        triangleHash_.insert(_sjudgeMentName, _triangle);
    }
}

void Quadrangle::getQuadrangleShow(const QString& firstPointID_, const QString& secondPointID_, const QString& thirdPointID_, const QString& fourthPointID_,
                                   const float& red_, const float &green_, const float &blue_, QHash<QString, QUAD*>& quadHash_)
{
    QString _sjudgeMentName;
    set<QString> _set;
    _set.insert(firstPointID_);
    _set.insert(secondPointID_);
    _set.insert(thirdPointID_);
    _set.insert(fourthPointID_);
    set<QString>::iterator _itor = _set.begin();
    _sjudgeMentName = (*_itor)+tr(" ")+(*_itor++)+tr(" ")+(*_itor++)+tr(" ")+(*_itor++);
    _sjudgeMentName = _sjudgeMentName.trimmed();
    QHash<QString, QUAD*>::iterator _itors = quadHash_.find(_sjudgeMentName);
    if ( _itors == quadHash_.end() ) {
        QUAD* _triangle = new QUAD(firstPointID_.toUInt(), secondPointID_.toUInt(),
                                   thirdPointID_.toUInt(),fourthPointID_.toUInt(), red_, green_, blue_);
        quadHash_.insert(_sjudgeMentName, _triangle);
    }
}

Quadrangle::~Quadrangle()
{
}
