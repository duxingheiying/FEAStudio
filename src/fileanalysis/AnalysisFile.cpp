#include "AnalysisFile.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <set>
#include <QTime>

#include "Point.h"
#include "Line.h"
#include "Triangle.h"
#include "Quadrangle.h"
#include "Tetrahedron.h"
#include "TriangularPrism.h"
#include "Pyramid.h"
#include "Hexahedron.h"

using std::set;

AnalysisFile::AnalysisFile(QObject *parent)
    : QObject(parent)
{
    m_vVertexs          = new QVector<float>;   // all points vertexs
    m_vVertexsColor     = new QVector<float>;   // all points color r g b
    m_vVertexsIndex     = new QVector<uint>;    // all points index

    m_vLineVertexs      = new QVector<float>;   // all lines points
    m_vLineNormal       = new QVector<float>;   // all lines points normal
    m_vLineColor        = new QVector<float>;   // all lines points color
    m_vLineIndex        = new QVector<uint>;    // all lines points index

    m_vTrianglesVertexs = new QVector<float>;   // all Triangles
    m_vTrianglesNormal  = new QVector<float>;   // all Triangles points normal
    m_vTrianglesColor   = new QVector<float>;   // all triangles points color
    m_vTriangleIndex    = new QVector<uint>;    // all triangles points index

    m_vQuadsVertexs     = new QVector<float>;   // all Quads points
    m_vQuadsNormal      = new QVector<float>;   // all Quads points Normals
    m_vQuadsColor       = new QVector<float>;   // all Quads points color
    m_vQuadsIndex       = new QVector<uint>;    // all Quads points index
}

AnalysisFile::~AnalysisFile()
{
    qDebug()<<tr("Call AnalysisFile::~AnalysisFile()");

    // delete all the momery
    if (m_vVertexs != nullptr) {
        delete m_vVertexs;
        m_vVertexs = nullptr;
    }

    if (m_vVertexsColor != nullptr) {
        delete m_vVertexsColor;
        m_vVertexsColor = nullptr;
    }
    if (m_vVertexsIndex != nullptr) {
        delete m_vVertexsIndex;
        m_vVertexsIndex = nullptr;
    }

    if (m_vLineVertexs != nullptr) {
        delete m_vLineVertexs;
        m_vLineVertexs = nullptr;
    }
    if (m_vLineNormal != nullptr) {
        delete m_vLineNormal;
        m_vLineNormal = nullptr;
    }
    if (m_vLineColor != nullptr){
        delete m_vLineColor;
        m_vLineColor = nullptr;
    }
    if (m_vLineIndex != nullptr) {
        delete m_vLineIndex;
        m_vLineIndex = nullptr;
    }

    if (m_vTrianglesVertexs != nullptr){
        delete m_vTrianglesVertexs;
        m_vTrianglesVertexs = nullptr;
    }
    if (m_vTrianglesNormal != nullptr){
        delete m_vTrianglesNormal;
        m_vTrianglesNormal = nullptr;
    }
    if (m_vTrianglesColor != nullptr){
        delete m_vTrianglesColor;
        m_vTrianglesColor = nullptr;
    }
    if (m_vTriangleIndex != nullptr){
        delete m_vTriangleIndex;
        m_vTriangleIndex = nullptr;
    }

    if (m_vQuadsVertexs != nullptr){
        delete m_vQuadsVertexs;
        m_vQuadsVertexs = nullptr;
    }
    if (m_vQuadsNormal != nullptr){
        delete m_vQuadsNormal;
        m_vQuadsNormal = nullptr;
    }
    if (m_vQuadsColor != nullptr){
        delete m_vQuadsColor;
        m_vQuadsColor = nullptr;
    }
    if (m_vQuadsIndex != nullptr){
        delete m_vQuadsIndex;
        m_vQuadsIndex = nullptr;
    }
}

// analysis the data of string for bdf
QString AnalysisFile::stdNumberString(QString str_)
{
    str_ = str_.trimmed();
    if (str_.lastIndexOf("-") != 0) { // if the '-' doesn't at the begain of the string, it's scientific number
        str_.replace(str_.lastIndexOf("-"), 1, "e-");
    }
    else if(str_.lastIndexOf("+") != 0) { // if the '+' doesn't at the begain of the string, it's scientific number
        str_.replace(str_.lastIndexOf("+"), 1, "e+");
    }
    return str_;
}

bool AnalysisFile::CreatePoint(float const &firstPoint_, float const &secondPoint_, float const &thirdPoint_,
                               uint &PointID_,QMap<uint, uint> &indexMap_, uint count_)
{
    // store all vertex
    m_vVertexs->push_back(firstPoint_);
    m_vVertexs->push_back(secondPoint_);
    m_vVertexs->push_back(thirdPoint_);

    // set the colors
    m_vVertexsColor->push_back(0.4f);  // point red
    m_vVertexsColor->push_back(0.1f);  // point blud
    m_vVertexsColor->push_back(0.4f);  // point blue

    //translate real ID to virtual ID
    m_vVertexsIndex->push_back(count_);
    indexMap_.insert(PointID_, count_); // the first is key, the value is count

    return true;
}

bool AnalysisFile::CreateTriangle(uint const &FirstID_, uint const &SecondID_, uint const &ThirdID_,
                                  uint &TriangleIndex_, QMap<uint, uint> &indexMap_)
{
    // triangle color
    float _Triangle_r = 0.0f;
    float _Triangle_g = 0.3f;
    float _Triangle_b = 0.9f;

    // translate id to index id
    QMap<uint, uint>::iterator _it = indexMap_.find(FirstID_);

    QVector3D _firstVector;
    QVector3D _secondVector;
    QVector3D _thirdVector;
    int       _Position;
    // translate the first vertexID
    if(_it != indexMap_.end()) {
        _Position = static_cast<int>(_it.value()) * 3;

        _firstVector.setX(m_vVertexs->at(_Position));
        m_vTrianglesVertexs->push_back(m_vVertexs->at(_Position++));

        _firstVector.setY(m_vVertexs->at(_Position));
        m_vTrianglesVertexs->push_back(m_vVertexs->at(_Position++));

        _firstVector.setZ(m_vVertexs->at(_Position));
        m_vTrianglesVertexs->push_back(m_vVertexs->at(_Position));

        m_vTrianglesColor->push_back(_Triangle_r);
        m_vTrianglesColor->push_back(_Triangle_g);
        m_vTrianglesColor->push_back(_Triangle_b);
    } else {
        qDebug()<<"Triange first Point ID Err"<<FirstID_;
        return false;
    }

    // translate the second vertexID
    _it = indexMap_.find(SecondID_);
    if(_it != indexMap_.end()) {
        _Position = static_cast<int>(_it.value()) * 3;

        _secondVector.setX(m_vVertexs->at(_Position));
        m_vTrianglesVertexs->push_back(m_vVertexs->at(_Position++));

        _secondVector.setY(m_vVertexs->at(_Position));
        m_vTrianglesVertexs->push_back(m_vVertexs->at(_Position++));

        _secondVector.setZ(m_vVertexs->at(_Position));
        m_vTrianglesVertexs->push_back(m_vVertexs->at(_Position));

        m_vTrianglesColor->push_back(_Triangle_r);
        m_vTrianglesColor->push_back(_Triangle_g);
        m_vTrianglesColor->push_back(_Triangle_b);
    } else {
        qDebug()<<"Triange second Point ID Err"<<SecondID_;
        return false;
    }

    // translate the third vertexID
    _it = indexMap_.find(ThirdID_);
    if(_it != indexMap_.end()) {
        _Position = static_cast<int>(_it.value()) * 3;

        _thirdVector.setX(m_vVertexs->at(_Position));
        m_vTrianglesVertexs->push_back(m_vVertexs->at(_Position++));

        _thirdVector.setY(m_vVertexs->at(_Position));
        m_vTrianglesVertexs->push_back(m_vVertexs->at(_Position++));

        _thirdVector.setZ(m_vVertexs->at(_Position));
        m_vTrianglesVertexs->push_back(m_vVertexs->at(_Position));

        m_vTrianglesColor->push_back(_Triangle_r);
        m_vTrianglesColor->push_back(_Triangle_g);
        m_vTrianglesColor->push_back(_Triangle_b);
    } else {
        qDebug()<<"Triange third Point ID Err"<<ThirdID_;
        return false;
    }

    // set the Triangle face normal
    QVector3D _normal = QVector3D::crossProduct(_secondVector - _firstVector, _thirdVector - _firstVector);
    for (int i = 0; i < 3; i++) {
        m_vTrianglesNormal->push_back(_normal.x());
        m_vTrianglesNormal->push_back(_normal.y());
        m_vTrianglesNormal->push_back(_normal.z());

        // all triangles index
        m_vTriangleIndex->push_back(TriangleIndex_++);
    }
    return true;
}

bool AnalysisFile::CreateTriangle(const uint firstPointID_, const uint secondPointID_,const uint thirdPointID_,
                                  const float &red_, const float &green_, const float &blue_)
{
//    QString _sjudgeMentName;
//    set<QString> _set;
//    _set.insert(firstPointID_);  // the triangle first point id
//    _set.insert(secondPointID_);  // the triangle second point id
//    _set.insert(thirdPointID_);  // the triangle third point id
//    set<QString>::iterator _itor = _set.begin();
//    _sjudgeMentName = (*_itor)+tr(" ")+(*_itor++)+tr(" ")+(*_itor++);
//    _sjudgeMentName = _sjudgeMentName.trimmed();
//    QHash<QString, TRIANGLE*>::iterator _itors = triangleHash_.find(_sjudgeMentName);
//    if ( _itors != triangleHash_.end() ) {
//        delete _itors.value();
//        _itors.value() = nullptr;
//        triangleHash_.erase(_itors);
//    } else {
//        TRIANGLE* _triangle = new TRIANGLE(firstPointID_.toUInt(), secondPointID_.toUInt(), thirdPointID_.toUInt(), red_, green_, blue_);
//        triangleHash_.insert(_sjudgeMentName, _triangle);
//    }

    return true;
}

// the point id use QString
bool AnalysisFile::CreateTriangle( const QString firstPointID_, const QString secondPointID_, const QString thirdPointID_,
                                   const uint triangleID_, const uint materialID_)
{
//    Q_UNUSED(triangleID_)
//    Q_UNUSED(materialID_)
//    TRIANGLE* _triangle;
//    QHash<QString, TRIANGLE*>::iterator _itor;
//    QString _idlist;
//    set<QString> _set;
//    _set.insert(firstPointID_);
//    _set.insert(secondPointID_);
//    _set.insert(thirdPointID_);
//    foreach(const QString _value, _set) {
//        _idlist += _value + tr(" ");
//    }
//    _itor = m_allTempTriangleHash.find(_idlist);
//    if ( _itor != m_allTempTriangleHash.end() ) {
//        delete _itor.value();
//        _itor.value() = nullptr;
//        m_allTempTriangleHash.erase(_itor);
//    } else {
//        _triangle = new TRIANGLE(firstPointID_.toUInt(),
//                                 secondPointID_.toUInt(),
//                                 thirdPointID_.toUInt(),
//                                 QColor(255, 255, 255));
//        m_allTempTriangleHash.insert(_idlist, _triangle);
//    }
    return true;
}

bool AnalysisFile::CreateQuad(uint const &FirstID_, uint const &SecondID_,
                              uint const &ThirdID_, uint const &FourthID_,
                              uint &QuadIndex_, QMap<uint, uint> &indexMap_)
{
    float _Quads_r = 0.0f;
    float _Quads_g = 0.3f;
    float _Quads_b = 0.9f;

    // Quad id to index id
    QMap<uint, uint>::iterator _it = indexMap_.find(FirstID_);

    QVector3D _firstVector;
    QVector3D _secondVector;
    QVector3D _thirdVector;
    int _Position;
    // translate the first vertexID
    if(_it != indexMap_.end()) {
        _Position = static_cast<int>(_it.value()) * 3;

        _firstVector.setX(m_vVertexs->at(_Position));
        m_vQuadsVertexs->push_back(m_vVertexs->at(_Position++));

        _firstVector.setY(m_vVertexs->at(_Position));
        m_vQuadsVertexs->push_back(m_vVertexs->at(_Position++));

        _firstVector.setZ(m_vVertexs->at(_Position));
        m_vQuadsVertexs->push_back(m_vVertexs->at(_Position));

        m_vQuadsColor->push_back(_Quads_r);
        m_vQuadsColor->push_back(_Quads_g);
        m_vQuadsColor->push_back(_Quads_b);
    } else {
        qDebug()<<"Quad first Point ID Err"<<FirstID_;
        return true;
    }

    // translate the second vertexID
    _it = indexMap_.find(SecondID_);
    if(_it != indexMap_.end()) {
        _Position = static_cast<int>(_it.value()) * 3;

        _secondVector.setX(m_vVertexs->at(_Position));
        m_vQuadsVertexs->push_back(m_vVertexs->at(_Position++));

        _secondVector.setY(m_vVertexs->at(_Position));
        m_vQuadsVertexs->push_back(m_vVertexs->at(_Position++));

        _secondVector.setZ(m_vVertexs->at(_Position));
        m_vQuadsVertexs->push_back(m_vVertexs->at(_Position));

        m_vQuadsColor->push_back(_Quads_r);
        m_vQuadsColor->push_back(_Quads_g);
        m_vQuadsColor->push_back(_Quads_b);
    } else {
        qDebug()<<"Quad second Point ID Err"<<SecondID_;
        return true;
    }

    // translate the third vertexID
    _it = indexMap_.find(ThirdID_);
    if(_it != indexMap_.end()) {
        _Position = static_cast<int>(_it.value()) * 3;

        _thirdVector.setX(m_vVertexs->at(_Position));
        m_vQuadsVertexs->push_back(m_vVertexs->at(_Position++));

        _thirdVector.setY(m_vVertexs->at(_Position));
        m_vQuadsVertexs->push_back(m_vVertexs->at(_Position++));

        _thirdVector.setZ(m_vVertexs->at(_Position));
        m_vQuadsVertexs->push_back(m_vVertexs->at(_Position));

        m_vQuadsColor->push_back(_Quads_r);
        m_vQuadsColor->push_back(_Quads_g);
        m_vQuadsColor->push_back(_Quads_b);
    } else {
        qDebug()<<"Quad third Point ID Err"<<ThirdID_;
        return true;
    }

    // tranlaste the fourth vertexID
    _it = indexMap_.find(FourthID_);
    if(_it != indexMap_.end()) {
        _Position = static_cast<int>(_it.value()) * 3;

        m_vQuadsVertexs->push_back(m_vVertexs->at(_Position++));
        m_vQuadsVertexs->push_back(m_vVertexs->at(_Position++));
        m_vQuadsVertexs->push_back(m_vVertexs->at(_Position));

        m_vQuadsColor->push_back(_Quads_r);
        m_vQuadsColor->push_back(_Quads_g);
        m_vQuadsColor->push_back(_Quads_b);
    } else {
        qDebug()<<"Quad fourth Point ID Err"<<FourthID_;
        return true;
    }

    // set the Quads face normal
    QVector3D _normal = QVector3D::crossProduct(_secondVector - _firstVector, _thirdVector - _firstVector);
    for (int i = 0; i < 4; i++) {
        m_vQuadsNormal->push_back(_normal.x());
        m_vQuadsNormal->push_back(_normal.y());
        m_vQuadsNormal->push_back(_normal.z());

        // all quads index
        m_vQuadsIndex->push_back(QuadIndex_++);
    }
    return true;
}

bool AnalysisFile::CreateQuad(const uint firstPointID_, const uint secondPointID_,
                              const uint thirdPointID_, const uint fourthPointID_,
                              const QString &idList_, const uint _QuadID, const uint matrialID_)
{
//    Q_UNUSED(_QuadID)
//    Q_UNUSED(matrialID_)
//    QUAD* _quadrangle;
//    QHash<QString, QUAD*>::iterator _itor;
//    _itor = m_allTempQuadHash.find(idList_);
//    if ( _itor != m_allTempQuadHash.end() ) {
//        delete _itor.value();
//        _itor.value() = nullptr;
//        m_allTempQuadHash.erase(_itor);
//    } else {
//        _quadrangle = new QUAD(firstPointID_,
//                               secondPointID_,
//                               thirdPointID_,
//                               fourthPointID_,
//                               QColor(255,255,255));
//        m_allTempQuadHash.insert(idList_, _quadrangle);
//    }
    return true;
}

bool AnalysisFile::CreateQuad( const QString firstPointID_, const QString secondPointID_,
                               const QString thirdPointID_, const QString fourthPointID_,
                               const uint QuadID_, const uint matrialID_)
{
//    Q_UNUSED(QuadID_)
//    Q_UNUSED(matrialID_)
//    QString _idlist;
//    set<QString> _set;
//    QHash<QString, QUAD*>::iterator _itor;
//    QUAD* _quadrangle;
//    _set.insert(firstPointID_);
//    _set.insert(secondPointID_);
//    _set.insert(thirdPointID_);
//    _set.insert(fourthPointID_);
//    foreach(const QString _value, _set) {
//        _idlist += _value + tr(" ");
//    }
//    _itor = m_allTempQuadHash.find(_idlist);
//    if ( _itor != m_allTempQuadHash.end() ) {
//        delete _itor.value();
//        _itor.value() = nullptr;
//        m_allTempQuadHash.erase(_itor);
//    } else {
//        _quadrangle = new QUAD(firstPointID_.toUInt(),
//                               secondPointID_.toUInt(),
//                               thirdPointID_.toUInt(),
//                               fourthPointID_.toUInt(),
//                               QColor(255,255,255));
//        m_allTempQuadHash.insert(_idlist, _quadrangle);
//    }
    return true;
}

// this is apply for memory space, so that the space address is static,or you can't use the color and address space address
void AnalysisFile::calculatAllShow()
{
    uint _QuadIndex = 0;
    uint _TriangleIndex = 0;
    QTime _time;
    _time.restart();

    // triangle color
    QVector3D _firstVector(0.0, 0.0, 0.0);
    QVector3D _secondVector(0.0, 0.0, 0.0);
    QVector3D _thirdVector(0.0, 0.0, 0.0);
    QVector3D _normal(0.0, 0.0, 0.0);

    // first deal with the entity
    for (QMap<uint, Tetrahedron*>::iterator _itor =  m_allTetrahedronMap.begin();
         _itor !=  m_allTetrahedronMap.end(); _itor++) {
        _itor.value()->getAllShow( m_allTempTriangleHash, m_allTempQuadHash);
    }

    for (QMap<uint, Hexahedron*>::iterator _itor =  m_allHexahedronMap.begin();
         _itor !=  m_allHexahedronMap.end(); _itor++) {
        _itor.value()->getAllShow( m_allTempTriangleHash, m_allTempQuadHash);
    }

    for (QMap<uint, TriangularPrism*>::iterator _itor =  m_allTriangularPrismMap.begin();
         _itor !=  m_allTriangularPrismMap.end(); _itor++) {
        _itor.value()->getAllShow( m_allTempTriangleHash, m_allTempQuadHash);
    }

    // second deal with the plat
    for (QMap<uint, Triangle*>::iterator _itor =  m_allTrianglesMap.begin();
         _itor !=  m_allTrianglesMap.end(); _itor++) {
        _itor.value()->getAllShow( m_allTempTriangleHash, m_allTempQuadHash);
    }

    for (QMap<uint, Quadrangle*>::iterator _itor =  m_allQuadMap.begin();
         _itor !=  m_allQuadMap.end(); _itor++) {
        _itor.value()->getAllShow( m_allTempTriangleHash, m_allTempQuadHash);
    }

    // create all triangles
    QHash<QString, TRIANGLE*>::iterator _triangle_itor = m_allTempTriangleHash.begin();
    while (_triangle_itor != m_allTempTriangleHash.end()) {
        const float& _red = _triangle_itor.value()->m_fRed;
        const float& _green = _triangle_itor.value()->m_fGreen;
        const float& _blue = _triangle_itor.value()->m_fBlue;

        QMap<uint, Point*>::iterator _point_itor = m_allPointMap.find(_triangle_itor.value()->m_uFirstPointID);
        m_vTrianglesVertexs->push_back(_point_itor.value()->m_fX);
        m_vTrianglesVertexs->push_back(_point_itor.value()->m_fY);
        m_vTrianglesVertexs->push_back(_point_itor.value()->m_fZ);

        _firstVector = QVector3D(_point_itor.value()->m_fX, _point_itor.value()->m_fY, _point_itor.value()->m_fZ);

        m_vTrianglesColor->push_back(_red);
        m_vTrianglesColor->push_back(_green);
        m_vTrianglesColor->push_back(_blue);

//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+0]));
//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+1]));
//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+2]));

//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+0]));
//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+1]));
//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+2]));

        // all triangles index
        m_vTriangleIndex->push_back(_TriangleIndex++);

        _point_itor = m_allPointMap.find(_triangle_itor.value()->m_uSecondPointID);
        m_vTrianglesVertexs->push_back(_point_itor.value()->m_fX);
        m_vTrianglesVertexs->push_back(_point_itor.value()->m_fY);
        m_vTrianglesVertexs->push_back(_point_itor.value()->m_fZ);

        _secondVector = QVector3D(_point_itor.value()->m_fX, _point_itor.value()->m_fY, _point_itor.value()->m_fZ);

        m_vTrianglesColor->push_back(_red);
        m_vTrianglesColor->push_back(_green);
        m_vTrianglesColor->push_back(_blue);

//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+0]));
//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+1]));
//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+2]));

//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+0]));
//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+1]));
//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+2]));

        // all triangles index
        m_vTriangleIndex->push_back(_TriangleIndex++);

        _point_itor = m_allPointMap.find(_triangle_itor.value()->m_uThirdPointID);
        m_vTrianglesVertexs->push_back(_point_itor.value()->m_fX);
        m_vTrianglesVertexs->push_back(_point_itor.value()->m_fY);
        m_vTrianglesVertexs->push_back(_point_itor.value()->m_fZ);

        _thirdVector = QVector3D(_point_itor.value()->m_fX, _point_itor.value()->m_fY, _point_itor.value()->m_fZ);

        m_vTrianglesColor->push_back(_red);
        m_vTrianglesColor->push_back(_green);
        m_vTrianglesColor->push_back(_blue);

//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+0]));
//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+1]));
//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+2]));

//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+0]));
//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+1]));
//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+2]));

        // all triangles index
        m_vTriangleIndex->push_back(_TriangleIndex++);

        _normal = QVector3D::crossProduct(_secondVector - _firstVector, _thirdVector - _firstVector);
        for (int i = 0; i < 3; i++) {
            m_vTrianglesNormal->push_back(_normal.x());
            m_vTrianglesNormal->push_back(_normal.y());
            m_vTrianglesNormal->push_back(_normal.z());
        }
        _triangle_itor++;
    }

    // create all quads
    QHash<QString, QUAD*>::iterator _quads_itor = m_allTempQuadHash.begin();
    while (_quads_itor != m_allTempQuadHash.end()) {
        const float& _red = _quads_itor.value()->m_fRed;
        const float& _green = _quads_itor.value()->m_fGreen;
        const float& _blue = _quads_itor.value()->m_fBlue;

        QMap<uint, Point*>::iterator _point_itor = m_allPointMap.find(_quads_itor.value()->m_uFirstPointID);
        m_vQuadsVertexs->push_back(_point_itor.value()->m_fX);
        m_vQuadsVertexs->push_back(_point_itor.value()->m_fY);
        m_vQuadsVertexs->push_back(_point_itor.value()->m_fZ);

        _firstVector = QVector3D(_point_itor.value()->m_fX,_point_itor.value()->m_fY, _point_itor.value()->m_fZ);

        m_vQuadsColor->push_back(_red);
        m_vQuadsColor->push_back(_green);
        m_vQuadsColor->push_back(_blue);

//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+0]));
//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+1]));
//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+2]));

//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+0]));
//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+1]));
//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+2]));

        // all triangles index
        m_vQuadsIndex->push_back(_QuadIndex++);

        _point_itor = m_allPointMap.find(_quads_itor.value()->m_uSecondPointID);
        m_vQuadsVertexs->push_back(_point_itor.value()->m_fX);
        m_vQuadsVertexs->push_back(_point_itor.value()->m_fY);
        m_vQuadsVertexs->push_back(_point_itor.value()->m_fZ);

        _secondVector = QVector3D(_point_itor.value()->m_fX,_point_itor.value()->m_fY, _point_itor.value()->m_fZ);

        m_vQuadsColor->push_back(_red);
        m_vQuadsColor->push_back(_green);
        m_vQuadsColor->push_back(_blue);

//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+0]));
//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+1]));
//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+2]));

//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+0]));
//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+1]));
//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+2]));

        // all triangles index
        m_vQuadsIndex->push_back(_QuadIndex++);

        _point_itor = m_allPointMap.find(_quads_itor.value()->m_uThirdPointID);
        m_vQuadsVertexs->push_back(_point_itor.value()->m_fX);
        m_vQuadsVertexs->push_back(_point_itor.value()->m_fY);
        m_vQuadsVertexs->push_back(_point_itor.value()->m_fZ);

        _thirdVector = QVector3D(_point_itor.value()->m_fX,_point_itor.value()->m_fY, _point_itor.value()->m_fZ);

        m_vQuadsColor->push_back(_red);
        m_vQuadsColor->push_back(_green);
        m_vQuadsColor->push_back(_blue);

//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+0]));
//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+1]));
//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+2]));

//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+0]));
//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+1]));
//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+2]));

        // all triangles index
        m_vQuadsIndex->push_back(_QuadIndex++);

        _point_itor = m_allPointMap.find(_quads_itor.value()->m_uFourthPointID);
        m_vQuadsVertexs->push_back(_point_itor.value()->m_fX);
        m_vQuadsVertexs->push_back(_point_itor.value()->m_fY);
        m_vQuadsVertexs->push_back(_point_itor.value()->m_fZ);


        m_vQuadsColor->push_back(_red);
        m_vQuadsColor->push_back(_green);
        m_vQuadsColor->push_back(_blue);

//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+0]));
//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+1]));
//        _point_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+2]));

//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+0]));
//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+1]));
//        _point_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+2]));

        // all triangles index
        m_vQuadsIndex->push_back(_QuadIndex++);

        _normal = QVector3D::crossProduct(_secondVector - _firstVector, _thirdVector - _firstVector);
        for (int i = 0; i < 4; i++) {
            m_vQuadsNormal->push_back(_normal.x());
            m_vQuadsNormal->push_back(_normal.y());
            m_vQuadsNormal->push_back(_normal.z());
        }

        _quads_itor++;
    }

//    clearAllTempData();

    qDebug()<<tr("**************************************************************");
    qDebug()<<tr("***********Create All Show Triangles And QuadS****************");
    qDebug()<<tr("TempTriangleHashSize : ")<<m_allTempTriangleHash.size();
    qDebug()<<tr("    TempQuadHashSize : ")<<m_allTempQuadHash.size();
    qDebug()<<tr("create element time  : ")<<_time.elapsed();
    qDebug()<<tr("**************************************************************")<<'\n'<<'\n';
}

// this is apply for memory space prefore, so that the space address is static,or you can use the space address
void AnalysisFile::calculatShow()
{
    uint _QuadIndex = 0;
    uint _TriangleIndex = 0;
    QTime _time;
    _time.restart();

    // triangle color
    QVector3D _firstVector(0.0, 0.0, 0.0);
    QVector3D _secondVector(0.0, 0.0, 0.0);
    QVector3D _thirdVector(0.0, 0.0, 0.0);
    QVector3D _normal(0.0, 0.0, 0.0);

    // first deal with the entity
    for (QMap<uint, Tetrahedron*>::iterator _itor =  m_allTetrahedronMap.begin();
         _itor !=  m_allTetrahedronMap.end(); _itor++) {
        _itor.value()->getAllShow( m_allTempTriangleHash, m_allTempQuadHash);
    }

    for (QMap<uint, Hexahedron*>::iterator _itor =  m_allHexahedronMap.begin();
         _itor !=  m_allHexahedronMap.end(); _itor++) {
        _itor.value()->getAllShow( m_allTempTriangleHash, m_allTempQuadHash);
    }

    for (QMap<uint, TriangularPrism*>::iterator _itor =  m_allTriangularPrismMap.begin();
         _itor !=  m_allTriangularPrismMap.end(); _itor++) {
        _itor.value()->getAllShow( m_allTempTriangleHash, m_allTempQuadHash);
    }

    // second deal with the plat
    for (QMap<uint, Triangle*>::iterator _itor =  m_allTrianglesMap.begin();
         _itor !=  m_allTrianglesMap.end(); _itor++) {
        _itor.value()->getAllShow( m_allTempTriangleHash, m_allTempQuadHash);
    }

    for (QMap<uint, Quadrangle*>::iterator _itor =  m_allQuadMap.begin();
         _itor !=  m_allQuadMap.end(); _itor++) {
        _itor.value()->getAllShow( m_allTempTriangleHash, m_allTempQuadHash);
    }

    // apply fot space prefer
    if ( m_vTrianglesVertexs != nullptr ) {
        delete m_vTrianglesVertexs;
        m_vTrianglesVertexs = nullptr;
    }
    m_vTrianglesVertexs = new QVector<float>(m_allTempTriangleHash.size()*9);

    if ( m_vTrianglesColor != nullptr ) {
        delete m_vTrianglesColor;
        m_vTrianglesColor = nullptr;
    }
    m_vTrianglesColor = new QVector<float>(m_allTempTriangleHash.size()*9);

    if ( m_vTrianglesNormal != nullptr ) {
        delete m_vTrianglesNormal;
        m_vTrianglesNormal = nullptr;
    }
    m_vTrianglesNormal = new QVector<float>(m_allTempTriangleHash.size()*9);

    if ( m_vTriangleIndex != nullptr ) {
        delete m_vTriangleIndex;
        m_vTriangleIndex = nullptr;
    }
    m_vTriangleIndex = new QVector<uint>(m_allTempTriangleHash.size()*3);

    // create all triangles
    QHash<QString, TRIANGLE*>::iterator _triangle_itor = m_allTempTriangleHash.begin();
    while (_triangle_itor != m_allTempTriangleHash.end()) {
        const float& _red = _triangle_itor.value()->m_fRed;
        const float& _green = _triangle_itor.value()->m_fGreen;
        const float& _blue = _triangle_itor.value()->m_fBlue;

        QMap<uint, Point*>::iterator _firstPoint_itor = m_allPointMap.find(_triangle_itor.value()->m_uFirstPointID);
        QMap<uint, Point*>::iterator _secondPoint_itor = m_allPointMap.find(_triangle_itor.value()->m_uSecondPointID);
        QMap<uint, Point*>::iterator _thirdPoint_itor = m_allPointMap.find(_triangle_itor.value()->m_uThirdPointID);
        if ( _firstPoint_itor == m_allPointMap.end() || _secondPoint_itor == m_allPointMap.end() || _thirdPoint_itor == m_allPointMap.end() ) {
            _triangle_itor++;
            continue;
        }

        // first point itor
        (*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+0] = _firstPoint_itor.value()->m_fX;
        (*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+1] = _firstPoint_itor.value()->m_fY;
        (*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+2] = _firstPoint_itor.value()->m_fZ;
        _firstVector = QVector3D(_firstPoint_itor.value()->m_fX, _firstPoint_itor.value()->m_fY, _firstPoint_itor.value()->m_fZ);

        (*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+0] = _red;
        (*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+1] = _green;
        (*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+2] = _blue;

        _firstPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+0]));
        _firstPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+1]));
        _firstPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+2]));

        _firstPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+0]));
        _firstPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+1]));
        _firstPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+2]));

        // all triangles index
        (*m_vTriangleIndex)[static_cast<int>(_TriangleIndex)] = _TriangleIndex;
        _TriangleIndex++;

        // second point itor
        (*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+0] = _secondPoint_itor.value()->m_fX;
        (*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+1] = _secondPoint_itor.value()->m_fY;
        (*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+2] = _secondPoint_itor.value()->m_fZ;

        _secondVector = QVector3D(_secondPoint_itor.value()->m_fX, _secondPoint_itor.value()->m_fY, _secondPoint_itor.value()->m_fZ);

        (*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+0] = _red;
        (*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+1] = _green;
        (*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+2] = _blue;

        _secondPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+0]));
        _secondPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+1]));
        _secondPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+2]));

        _secondPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+0]));
        _secondPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+1]));
        _secondPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+2]));

        // all triangles index
        (*m_vTriangleIndex)[static_cast<int>(_TriangleIndex)] = _TriangleIndex;
        _TriangleIndex++;


        // third point itor
        (*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+0] = _thirdPoint_itor.value()->m_fX;
        (*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+1] = _thirdPoint_itor.value()->m_fY;
        (*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+2] = _thirdPoint_itor.value()->m_fZ;

        _thirdVector = QVector3D(_thirdPoint_itor.value()->m_fX, _thirdPoint_itor.value()->m_fY, _thirdPoint_itor.value()->m_fZ);

        (*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+0] = _red;
        (*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+1] = _green;
        (*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+2] = _blue;

        _thirdPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+0]));
        _thirdPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+1]));
        _thirdPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesVertexs)[static_cast<int>(_TriangleIndex)*3+2]));

        _thirdPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+0]));
        _thirdPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+1]));
        _thirdPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vTrianglesColor)[static_cast<int>(_TriangleIndex)*3+2]));

        // all triangles index
        (*m_vTriangleIndex)[static_cast<int>(_TriangleIndex)] = _TriangleIndex;
        _TriangleIndex++;

        _normal = QVector3D::crossProduct(_secondVector - _firstVector, _thirdVector - _firstVector);
        for (int i = 0; i < 3; i++) {
            (*m_vTrianglesNormal)[(static_cast<int>(_TriangleIndex)-3+i)*3+0] = _normal.x();
            (*m_vTrianglesNormal)[(static_cast<int>(_TriangleIndex)-3+i)*3+1] = _normal.y();
            (*m_vTrianglesNormal)[(static_cast<int>(_TriangleIndex)-3+i)*3+2] = _normal.z();
        }
        _triangle_itor++;
    }

    // apply for space for quads
    if ( m_vQuadsVertexs != nullptr ) {
        delete m_vQuadsVertexs;
        m_vQuadsVertexs = nullptr;
    }
    m_vQuadsVertexs = new QVector<float>(m_allTempQuadHash.size()*12);

    if ( m_vQuadsColor != nullptr ) {
        delete m_vQuadsColor;
        m_vQuadsColor = nullptr;
    }
    m_vQuadsColor = new QVector<float>(m_allTempQuadHash.size()*12);

    if ( m_vQuadsNormal != nullptr ) {
        delete m_vQuadsNormal;
        m_vQuadsNormal = nullptr;
    }
    m_vQuadsNormal = new QVector<float>(m_allTempQuadHash.size()*12);

    if ( m_vQuadsIndex != nullptr ) {
        delete m_vQuadsIndex;
        m_vQuadsIndex = nullptr;
    }
    m_vQuadsIndex = new QVector<uint>(m_allTempQuadHash.size()*4);

    // create all quads
    QHash<QString, QUAD*>::iterator _quads_itor = m_allTempQuadHash.begin();
    while (_quads_itor != m_allTempQuadHash.end()) {
        const float& _red = _quads_itor.value()->m_fRed;
        const float& _green = _quads_itor.value()->m_fGreen;
        const float& _blue = _quads_itor.value()->m_fBlue;

        QMap<uint, Point*>::iterator _firstPoint_itor = m_allPointMap.find(_quads_itor.value()->m_uFirstPointID);
        QMap<uint, Point*>::iterator _secondPoint_itor = m_allPointMap.find(_quads_itor.value()->m_uSecondPointID);
        QMap<uint, Point*>::iterator _thirdPoint_itor = m_allPointMap.find(_quads_itor.value()->m_uThirdPointID);
        QMap<uint, Point*>::iterator _fourthPoint_itor = m_allPointMap.find(_quads_itor.value()->m_uFourthPointID);

        if ( _firstPoint_itor == m_allPointMap.end() || _secondPoint_itor == m_allPointMap.end() ||
             _thirdPoint_itor == m_allPointMap.end() || _fourthPoint_itor == m_allPointMap.end() ) {
            _quads_itor++;
            continue;
        }

        // first point itor
        (*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+0] = _firstPoint_itor.value()->m_fX;
        (*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+1] = _firstPoint_itor.value()->m_fY;
        (*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+2] = _firstPoint_itor.value()->m_fZ;

        _firstVector = QVector3D(_firstPoint_itor.value()->m_fX,_firstPoint_itor.value()->m_fY, _firstPoint_itor.value()->m_fZ);

        (*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+0] = _red;
        (*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+1] = _green;
        (*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+2] = _blue;

        _firstPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+0]));
        _firstPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+1]));
        _firstPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+2]));

        _firstPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+0]));
        _firstPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+1]));
        _firstPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+2]));

        // all triangles index
//        m_vQuadsIndex->push_back(_QuadIndex++);
        (*m_vQuadsIndex)[static_cast<int>(_QuadIndex)] = _QuadIndex;
        _QuadIndex++;

        // second point itor
        (*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+0] = _secondPoint_itor.value()->m_fX;
        (*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+1] = _secondPoint_itor.value()->m_fY;
        (*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+2] = _secondPoint_itor.value()->m_fZ;
        _secondVector = QVector3D(_secondPoint_itor.value()->m_fX,_secondPoint_itor.value()->m_fY, _secondPoint_itor.value()->m_fZ);

        (*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+0] = _red;
        (*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+1] = _green;
        (*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+2] = _blue;

        _secondPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+0]));
        _secondPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+1]));
        _secondPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+2]));

        _secondPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+0]));
        _secondPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+1]));
        _secondPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+2]));

        // all triangles index
        (*m_vQuadsIndex)[static_cast<int>(_QuadIndex)] = _QuadIndex;
        _QuadIndex++;

        // third point itor
        (*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+0] = _thirdPoint_itor.value()->m_fX;
        (*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+1] = _thirdPoint_itor.value()->m_fY;
        (*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+2] = _thirdPoint_itor.value()->m_fZ;
        _thirdVector = QVector3D(_thirdPoint_itor.value()->m_fX,_thirdPoint_itor.value()->m_fY, _thirdPoint_itor.value()->m_fZ);

        (*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+0] = _red;
        (*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+1] = _green;
        (*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+2] = _blue;

        _thirdPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+0]));
        _thirdPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+1]));
        _thirdPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+2]));

        _thirdPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+0]));
        _thirdPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+1]));
        _thirdPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+2]));

        // all triangles index
        (*m_vQuadsIndex)[static_cast<int>(_QuadIndex)] = _QuadIndex;
        _QuadIndex++;

        // fourth point itor
        (*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+0] = _fourthPoint_itor.value()->m_fX;
        (*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+1] = _fourthPoint_itor.value()->m_fY;
        (*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+2] = _fourthPoint_itor.value()->m_fZ;

        (*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+0] = _red;
        (*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+1] = _green;
        (*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+2] = _blue;

        _fourthPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+0]));
        _fourthPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+1]));
        _fourthPoint_itor.value()->m_aPointaddList.push_back(reinterpret_cast<float*>(&(*m_vQuadsVertexs)[static_cast<int>(_QuadIndex)*3+2]));

        _fourthPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+0]));
        _fourthPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+1]));
        _fourthPoint_itor.value()->m_aPColorList.push_back(reinterpret_cast<float*>(&(*m_vQuadsColor)[static_cast<int>(_QuadIndex)*3+2]));

        // all triangles index
        (*m_vQuadsIndex)[static_cast<int>(_QuadIndex)] = _QuadIndex;
        _QuadIndex++;

        _normal = QVector3D::crossProduct(_secondVector - _firstVector, _thirdVector - _firstVector);
        for (int i = 0; i < 4; i++) {
            (*m_vQuadsNormal)[(static_cast<int>(_QuadIndex)-4+i)*3+0] = _normal.x();
            (*m_vQuadsNormal)[(static_cast<int>(_QuadIndex)-4+i)*3+1] = _normal.y();
            (*m_vQuadsNormal)[(static_cast<int>(_QuadIndex)-4+i)*3+2] = _normal.z();
        }

        _quads_itor++;
    }

//    clearAllTempData();

//    qDebug()<<tr(" you have calculate all unit point ");
//    QMap<uint, Point*>::iterator _point_itor = m_allPointMap.begin();
//    while ( _point_itor != m_allPointMap.end() ) {
//        int _colorsize = _point_itor.value()->m_aPColorList.size();
//        qDebug()<<tr(" point %1 color add size : %2").arg(_point_itor.key()).arg(_colorsize);
//        for (int _i = 0; _i < _colorsize; _i++ ) {
//            switch (_i%3) {
//            case 0:
//                qDebug()<<*(_point_itor.value()->m_aPColorList.at(_i));
//                break;

//            case 1:
//                qDebug()<<*(_point_itor.value()->m_aPColorList.at(_i));
//                break;

//            case 2:
//                qDebug()<<*(_point_itor.value()->m_aPColorList.at(_i));
//                break;
//            default:
//                break;
//            }
//        }
//        _point_itor++;
//    }

    qDebug()<<tr("**************************************************************");
    qDebug()<<tr("***********Create All Show Triangles And QuadS****************");
    qDebug()<<tr("TempTriangleHashSize : ")<<m_allTempTriangleHash.size();
    qDebug()<<tr("    TempQuadHashSize : ")<<m_allTempQuadHash.size();
    qDebug()<<tr("create element time  : ")<<_time.elapsed();
    qDebug()<<tr("**************************************************************")<<'\n'<<'\n';
}

bool AnalysisFile::swapData(QVector3D      &vCenter_,
                            float          &Rand_,
                            QVector<float> &vVertexs_,
                            QVector<float> &vVertexsColor_,
                            QVector<uint>  &vVertexsIndex_,
                            QVector<float> &vLineVertexs_,
                            QVector<float> &vLineNormal_,
                            QVector<float> &vLineColor_,
                            QVector<uint>  &vLineIndex_,
                            QVector<float> &vTrianglesVertexs_,
                            QVector<float> &vTrianglesNormal_,
                            QVector<float> &vTrianglesColor_,
                            QVector<uint>  &vTriangleIndex_,
                            QVector<float> &vQuadsVertexs_,
                            QVector<float> &vQuadsColor_,
                            QVector<float> &vQuadsNormal_,
                            QVector<uint>  &vQuadIndex_)
{
    vCenter_ = m_vCenter;
    Rand_    = m_fRange;
    m_vVertexs->swap(vVertexs_);
    m_vVertexsColor->swap(vVertexsColor_);
    m_vVertexsIndex->swap(vVertexsIndex_);

    m_vLineVertexs->swap(vLineVertexs_);
    m_vLineNormal->swap(vLineNormal_);
    m_vLineColor->swap(vLineColor_);
    m_vLineIndex->swap(vLineIndex_);

    m_vTrianglesVertexs->swap(vTrianglesVertexs_);
    m_vTrianglesColor->swap(vTrianglesColor_);
    m_vTrianglesNormal->swap(vTrianglesNormal_);
    m_vTriangleIndex->swap(vTriangleIndex_);

    m_vQuadsVertexs->swap(vQuadsVertexs_);
    m_vQuadsColor->swap(vQuadsColor_);
    m_vQuadsNormal->swap(vQuadsNormal_);
    m_vQuadsIndex->swap(vQuadIndex_);
    return true;
}

bool AnalysisFile::clearAllTempData()
{
    // clear all the temp TRIANGLES
    QHash<QString, TRIANGLE*>::iterator _trianglehash_itor = m_allTempTriangleHash.begin();
    while (_trianglehash_itor != m_allTempTriangleHash.end()) {
        if (_trianglehash_itor.value() != nullptr) {
            delete _trianglehash_itor.value();
            _trianglehash_itor.value() = nullptr;
        }
        _trianglehash_itor++;
    }
    m_allTempTriangleHash.clear();

    // clear all the temp QUAD
    QHash<QString, QUAD*>::iterator _quadhash_itor = m_allTempQuadHash.begin();
    while (_quadhash_itor != m_allTempQuadHash.end()) {
        if (_quadhash_itor.value() != nullptr) {
            delete _quadhash_itor.value();
            _quadhash_itor.value() = nullptr;
        }
        _quadhash_itor++;
    }
    m_allTempQuadHash.clear();
    return true;
}

bool AnalysisFile::clearAllData()
{
    QMap<uint, Point*>::iterator _point_itor = m_allPointMap.begin();
    while (_point_itor != m_allPointMap.end()) {
        if (_point_itor.value() != nullptr) {
            delete _point_itor.value();
            _point_itor.value() = nullptr;
        }
        _point_itor++;
    }
    m_allPointMap.clear();

    QMap<uint, Line*>::iterator _line_itor = m_allLinesMap.begin();
    while (_line_itor != m_allLinesMap.end()) {
        if (_line_itor.value() != nullptr) {
            delete _line_itor.value();
            _line_itor.value() = nullptr;
        }
        _line_itor++;
    }
    m_allLinesMap.clear();

    QMap<uint, Triangle*>::iterator _triangle_itor = m_allTrianglesMap.begin();
    while (_triangle_itor != m_allTrianglesMap.end()) {
        if (_triangle_itor.value() != nullptr) {
            delete _triangle_itor.value();
            _triangle_itor.value() = nullptr;
        }
        _triangle_itor++;
    }
    m_allTrianglesMap.clear();

    QMap<uint, Quadrangle*>::iterator _quad_itor = m_allQuadMap.begin();
    while (_quad_itor != m_allQuadMap.end()) {
        if (_quad_itor.value() != nullptr) {
            delete _quad_itor.value();
            _quad_itor.value() = nullptr;
        }
        _quad_itor++;
    }
    m_allQuadMap.clear();

    // clear all the tetrahedron
    QMap<uint, Tetrahedron*>::iterator _tetrahedron_itor = m_allTetrahedronMap.begin();
    while (_tetrahedron_itor != m_allTetrahedronMap.end()) {
        if (_tetrahedron_itor.value() != nullptr) {
            delete _tetrahedron_itor.value();
            _tetrahedron_itor.value() = nullptr;
        }
        _tetrahedron_itor++;
    }
    m_allTetrahedronMap.clear();

    // clear all the hexahedron
    QMap<uint, Hexahedron*>::iterator _hexahedron_itor = m_allHexahedronMap.begin();
    while (_hexahedron_itor != m_allHexahedronMap.end()) {
        if (_hexahedron_itor.value() != nullptr) {
            delete _hexahedron_itor.value();
            _hexahedron_itor.value() = nullptr;
        }
        _hexahedron_itor++;
    }
    m_allHexahedronMap.clear();

    // clear all the triangularprism
    QMap<uint, TriangularPrism*>::iterator _triangularprism_itor = m_allTriangularPrismMap.begin();
    while (_triangularprism_itor != m_allTriangularPrismMap.end()) {
        if (_triangularprism_itor.value() != nullptr) {
            delete _triangularprism_itor.value();
            _triangularprism_itor.value() = nullptr;
        }
        _triangularprism_itor++;
    }
    m_allTriangularPrismMap.clear();

    clearAllTempData();   // clear all temp data

    // clear all the unused vertexs data
    m_vVertexs->clear();
    QVector<float>().swap(*m_vVertexs);
    m_vVertexsColor->clear();
    QVector<float>().swap(*m_vVertexsColor);
    m_vVertexsIndex->clear();
    QVector<uint>().swap(*m_vVertexsIndex);

    // clear all the unused line data
    m_vLineVertexs->clear();
    QVector<float>().swap(*m_vLineVertexs);
    m_vLineNormal->clear();
    QVector<float>().swap(*m_vLineNormal);
    m_vLineColor->clear();
    QVector<float>().swap(*m_vLineColor);
    m_vLineIndex->clear();
    QVector<uint>().swap(*m_vLineIndex);

    // clear all the unused triangle data
    m_vTrianglesVertexs->clear();
    QVector<float>().swap(*m_vTrianglesVertexs);
    m_vTrianglesNormal->clear();
    QVector<float>().swap(*m_vTrianglesNormal);
    m_vTrianglesColor->clear();
    QVector<float>().swap(*m_vTrianglesColor);
    m_vTriangleIndex->clear();
    QVector<uint>().swap(*m_vTriangleIndex);

    // clear all the unused Quad data
    m_vQuadsVertexs->clear();
    QVector<float>().swap(*m_vQuadsVertexs);
    m_vQuadsNormal->clear();
    QVector<float>().swap(*m_vQuadsNormal);
    m_vQuadsColor->clear();
    QVector<float>().swap(*m_vQuadsColor);
    m_vQuadsIndex->clear();
    QVector<uint>().swap(*m_vQuadsIndex);

    return true;
}
