#ifndef ANALYSISFILE_H
#define ANALYSISFILE_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <QHash>
#include <QVector3D>
#include <QColor>
#include <QFont>

class Point;
class Line;
class Triangle;
class Quadrangle;
class Tetrahedron;
class TriangularPrism;
class Pyramid;
class Hexahedron;

class TRIANGLE;
class QUAD;

//#include <unordered_map>

//using namespace std;

class AnalysisFile : public QObject
{
    Q_OBJECT

public:
    explicit AnalysisFile(QObject *parent = nullptr);
    virtual ~AnalysisFile() override;

public:
//    virtual bool ReadFile(const QString &FilePath_) = 0;

    // clear all the data
    virtual bool clearAllData();

    // clear all temp data
    virtual bool clearAllTempData();

    // switch the buffur
    virtual bool swapData(QVector3D      &vCenter_,
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
                          QVector<float> &vQuadsNormal_,
                          QVector<float> &vQuadsColor_,
                          QVector<uint>  &vQuadIndex_);

//    // create Line
//    virtual bool CreateLine() = 0;

protected:
    // translate the cae number string to standart number string
    virtual QString stdNumberString(QString str_);

    //    // create Point
    //    virtual bool CreatePoint() = 0;
#define CREATEPOINT(firstPoint_, secondPoint_, thirdPoint_, PointID_, indexMap_, count_)\
    {\
    m_vVertexs->push_back(firstPoint_);\
    m_vVertexs->push_back(secondPoint_);\
    m_vVertexs->push_back(thirdPoint_);\
    \
    m_vVertexsColor->push_back(0.4f);\
    m_vVertexsColor->push_back(0.1f);\
    m_vVertexsColor->push_back(0.4f);\
    \
    m_vVertexsIndex->push_back(count_);\
    indexMap_.insert(PointID_, count_);\
}

    // create Point
    virtual bool CreatePoint(float const &firstPoint_, float const &secondPoint_, float const &thirdPoint_,
                                    uint &PointID_, QMap<uint, uint> &indexMap_, uint count_);

    // create Triangle
    virtual bool CreateTriangle(uint const &FirstID_, uint const &SecondID_, uint const &ThirdID_,
                                uint &TriangleIndex_, QMap<uint, uint> &indexMap_);

    virtual bool CreateTriangle(const uint firstPointID_, const uint secondPointID_, const uint thirdPointID_,
                                 const float &red_, const float &green_, const float &blue_ = 0);

    virtual bool CreateTriangle( const QString firstPointID_, const QString secondPointID_, const QString thirdPointID_,
                                 const uint triangleID_, const uint materialID_ = 0);

    // create Quad
    virtual bool CreateQuad( uint const &FirstID_, uint const &SecondID_,
                             uint const &ThirdID_, uint const &FourthID_,
                             uint &QuadIndex_, QMap<uint, uint> &indexMap_);

    virtual bool CreateQuad( const uint firstPointID_, const uint secondPointID_,
                             const uint thirdPointID_, const uint fourthPointID_,
                             const QString &idList_, const uint triangleID_, const uint matrialID_ = 0);

    virtual bool CreateQuad(const QString firstPointID_, const QString secondPointID_,
                            const QString thirdPointID_, const QString fourthPointID_,
                            const uint QuadID_, const uint matrialID_ = 0);

    virtual void calculatAllShow();
    virtual void calculatShow();

private:

public:
    QVector3D m_vCenter;                 // the Center of the model
    float   m_fRange;                    // the range of the model
    
    QVector<float> *m_vVertexs;          // all points x y z
    QVector<float> *m_vVertexsColor;     // all points color r g b
    QVector<uint>  *m_vVertexsIndex;     // all points index

    QVector<float> *m_vLineVertexs;      // all lines points
    QVector<float> *m_vLineNormal;       // all lines points normal
    QVector<float> *m_vLineColor;        // all lines points color
    QVector<uint>  *m_vLineIndex;        // all lines points index

    QVector<float> *m_vTrianglesVertexs; // all Triangles
    QVector<float> *m_vTrianglesNormal;  // all Triangles points normal
    QVector<float> *m_vTrianglesColor;   // all triangles points color
    QVector<uint>  *m_vTriangleIndex;    // all triangles points index

    QVector<float> *m_vQuadsVertexs;     // all Quads points
    QVector<float> *m_vQuadsNormal;      // all Quads points Normals
    QVector<float> *m_vQuadsColor;       // all Quads points color
    QVector<uint>  *m_vQuadsIndex;       // all Quads points index

protected:
    QMap<uint, QColor> m_allSetColor;
    // this datas will be used by children
    QMap<uint, Point*> m_allPointMap;
    QMap<uint, Line*> m_allLinesMap;
    QMap<uint, Triangle*>  m_allTrianglesMap;
    QMap<uint, Quadrangle*> m_allQuadMap;
    QMap<uint, Tetrahedron*> m_allTetrahedronMap;
    QMap<uint, Hexahedron*> m_allHexahedronMap;
    QMap<uint, TriangularPrism*>m_allTriangularPrismMap;
    QHash<QString, TRIANGLE*> m_allTempTriangleHash;
    QHash<QString, QUAD*> m_allTempQuadHash;

private:

signals:
    void ReadFileFinished();
    void showMessage(const QString& msg,
                     const QColor& color_ = Qt::blue ,
                     const QFont& font_ = QFont("Times", -1, -1, false));

public slots:
    virtual bool ReadFile(const QString &FilePath_) = 0;

};
#endif // ANALYSISFILE_H
