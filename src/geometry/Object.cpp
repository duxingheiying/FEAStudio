#include "Object.h"
#include <set>
#include <QDebug>

using namespace std;

Object::Object()
{
//    m_eType = Object_NULL;
    QString m_sComponent;  // this object is
}

Object::~Object()
{
}

PointObject::PointObject()
{
}

PointObject::~PointObject()
{
}

plateObject::plateObject()
{
}

plateObject::~plateObject()
{
}

//void plateObject::calculateIDName()
//{
//    set<uint> _set;
//    foreach (const uint _value, m_vUsePointIDList) {
//        _set.insert(_value);
//    }
//    foreach(const uint _value, _set) {
//        m_sUnitPointIDList += QString::number(_value) + tr(" ");
//    }
//    m_sUnitPointIDList = m_sUnitPointIDList.trimmed();
//}

//QString plateObject::getIDName()
//{
//    return m_sUnitPointIDList;
//}

EntityObject::EntityObject()
{
}

EntityObject::~EntityObject()
{
}

PT::PT( float x_,  float y_,  float z_,  uint pointID_)
{
//    m_eType  = Object_PT;
    m_fX = x_;
    m_fY = y_;
    m_fZ = z_;

    m_uObjectID = pointID_;
}

PT::~PT()
{
}

void PT::setX(const float x_)
{
    m_fX = x_;
}

void PT::setY(const float y_)
{
    m_fY = y_;
}

void PT::setZ(const float z_)
{
    m_fZ = z_;
}

float PT::getX() const
{
    return m_fX;
}

float PT::getY() const
{
    return m_fY;
}

float PT::getZ() const
{
    return m_fZ;
}

void PT::setColor(const int r_, const int g_, const int b_, const int apha_)
{
    m_fRed = r_/static_cast<float>(255);
    m_fGreen = g_/static_cast<float>(255);
    m_fBlue = b_/static_cast<float>(255);
    m_fAlpha = apha_/static_cast<float>(255);
}
void PT::setColor(const float r_, const float g_, const float b_, const float apha_)
{
    m_fRed = r_;
    m_fGreen = g_;
    m_fBlue = b_;
    m_fAlpha = apha_;
}

void  PT::getColor(float &r_, float &g_, float &b_, float &apha_ )
{
    r_   = m_fRed;
    g_   = m_fGreen;
    b_   = m_fBlue;
    apha_= m_fAlpha;
}

inline void PT::setR(const float r_)
{
    m_fRed = r_;
}

inline void PT::setG(const float g_)
{
    m_fGreen = g_;
}

inline void PT::setB(const float b_)
{
    m_fBlue = b_;
}

inline void PT::setA(const float a_)
{
    m_fAlpha = a_;
}

inline float PT::getR() const
{
    return m_fRed;
}

inline float PT::getG() const
{
    return m_fGreen;
}

inline float PT::getB() const
{
    return m_fBlue;
}

inline float PT::getA() const
{
    return m_fAlpha;
}

LINE::LINE(uint firstpointID_, uint secondPointID_)
{
    Q_UNUSED(firstpointID_)
    Q_UNUSED(secondPointID_)
//    m_eType = Object_LINE;
//    m_vUsePointIDList.push_back(firstpointID_);
//    m_vUsePointIDList.push_back(secondPointID_);
}

LINE::~LINE()
{
}

TRIANGLE::TRIANGLE(const uint& firstpointID_,
                   const uint& secondpointID_,
                   const uint& thirdpointID_,
                   const float &red_, const float &green_, const float &blue_)
{
//    m_eType = Object_TRIANGLE;
//    m_cUnitColor = red_;
    m_uFirstPointID = firstpointID_;
    m_uSecondPointID = secondpointID_;
    m_uThirdPointID = thirdpointID_;
    m_fRed = red_;
    m_fGreen = green_;
    m_fBlue = blue_;
}

TRIANGLE::~TRIANGLE()
{
}

// initialize all the points
QUAD::QUAD(const uint &firstpointID_,
           const uint &secondpointID_,
           const uint &thirdpointID_,
           const uint &forthpointID_,
           const float &red_,
           const float &green_,
           const float &blue_)
{
//    m_eType = Object_QUAD;
    m_uFirstPointID = firstpointID_;
    m_uSecondPointID = secondpointID_;
    m_uThirdPointID = thirdpointID_;
    m_uFourthPointID = forthpointID_;
    m_fRed = red_;
    m_fGreen = green_;
    m_fBlue = blue_;
}

QUAD::~QUAD()
{
}

//void QUAD::CalcualteNormal()
//{
//    if (m_vVertexVector->size()>=9) {
//        QVector3D _vFristVertex = QVector3D(m_vVertexVector->at(0), m_vVertexVector->at(2), m_vVertexVector->at(3));
//        QVector3D _vSecondVertex = QVector3D(m_vVertexVector->at(4), m_vVertexVector->at(5), m_vVertexVector->at(6));
//        QVector3D _vThirdVertex = QVector3D(m_vVertexVector->at(7), m_vVertexVector->at(8), m_vVertexVector->at(9));
//        QVector3D _firstDirection  = _vSecondVertex - _vFristVertex;
//        QVector3D _secondDirection = _vThirdVertex - _vFristVertex;
//        QVector3D _vNormalVertex = QVector3D::crossProduct(_firstDirection, _secondDirection);
//        m_vNormaleVector->push_back(_vNormalVertex.x());
//        m_vNormaleVector->push_back(_vNormalVertex.y());
//        m_vNormaleVector->push_back(_vNormalVertex.z());
//    }
//    else {
//        return;
//    }
//}

//void QUAD::setColor(int r_, int g_, int b_, int apha_)
//{
//    if (m_vColorVector->size() == 16) {
//        for (int _var = 0; _var < 4; ++_var) {
//            (*m_vColorVector)[0 + 4 * _var] = r_;
//            (*m_vColorVector)[1 + 4 * _var] = g_;
//            (*m_vColorVector)[2 + 4 * _var] = b_;
//            (*m_vColorVector)[3 + 4 * _var] = apha_;
//        }
//    }
//    else {
//        QVector<float>().swap(*m_vColorVector);
//        m_vColorVector->clear();

//        for (int var = 0; var < 4; ++var) {
//            m_vColorVector->push_back(r_);
//            m_vColorVector->push_back(g_);
//            m_vColorVector->push_back(b_);
//            m_vColorVector->push_back(apha_);
//        }
//    }
//}

//void QUAD::setColor(float r_, float g_, float b_, float apha_)
//{
//    if (m_vColorVector->size() == 4) {
//        (*m_vColorVector)[0] = r_;
//        (*m_vColorVector)[1] = g_;
//        (*m_vColorVector)[2] = b_;
//        (*m_vColorVector)[3] = apha_;
//    }
//    else {
//        QVector<float>().swap(*m_vColorVector);
//        m_vColorVector->clear();
//        m_vColorVector->push_back(r_);
//        m_vColorVector->push_back(g_);
//        m_vColorVector->push_back(b_);
//        m_vColorVector->push_back(apha_);
//    }
//}

//void QUAD::getColor(float &r_, float &g_, float &b_, float &apha_)
//{
//    r_    = m_vColorVector->at(0);
//    g_    = m_vColorVector->at(1);
//    b_    = m_vColorVector->at(2);
//    apha_ = m_vColorVector->at(3);
//}

TETRA::TETRA()
{
}

TETRA::~TETRA()
{
}

PENTRA::PENTRA()
{
}

PENTRA::~PENTRA()
{
}

HEXA::HEXA()
{
}

HEXA::~HEXA()
{
}

// add all enable show element to hash map
void EntityObject::getAllShow(QHash<QString, TRIANGLE*>& triangleHash_,QHash<QString, QUAD*>& quadHash_)
{
    Q_UNUSED(triangleHash_)
    Q_UNUSED(quadHash_)
    qDebug()<<tr("you have not realized the getAllShow function");
}

void EntityObject::getTriangleShow(const QString& firstPointID_, const QString& secondPointID_, const QString& thirdPointID_,
                                   const float& red_, const float& green_, const float& blue_,   QHash<QString, TRIANGLE*>& triangleHash_)
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
    if ( _itors != triangleHash_.end() ) {
        delete _itors.value();
        _itors.value() = nullptr;
        triangleHash_.erase(_itors);
    } else {
        TRIANGLE* _triangle = new TRIANGLE(firstPointID_.toUInt(), secondPointID_.toUInt(), thirdPointID_.toUInt(), red_, green_, blue_);
        triangleHash_.insert(_sjudgeMentName, _triangle);
    }
}

void EntityObject::getQuadrangleShow(const QString& firstPointID_, const QString& secondPointID_,
                                     const QString& thirdPointID_, const QString& fourthPointID_,
                                     const float& red_, const float& green_, const float& blue_,
                                     QHash<QString, QUAD*>& quadHash_)
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
    if ( _itors != quadHash_.end() ) {
        delete _itors.value();
        _itors.value() = nullptr;
        quadHash_.erase(_itors);
    } else {
        QUAD* _triangle = new QUAD(firstPointID_.toUInt(), secondPointID_.toUInt(),
                                   thirdPointID_.toUInt(),fourthPointID_.toUInt(), red_, green_, blue_);
        quadHash_.insert(_sjudgeMentName, _triangle);
    }
}
