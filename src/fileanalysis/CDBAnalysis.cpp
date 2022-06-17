#include "CDBAnalysis.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtMath>
#include <QTimer>
#include <QTime>

CBDFile::CBDFile(AnalysisFile* parent) :
    AnalysisFile (parent)
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

CBDFile::~CBDFile()
{
    clearAllData();

    delete m_vVertexs;
    m_vVertexs = nullptr;
    delete m_vVertexsColor;
    m_vVertexsColor = nullptr;
    delete m_vVertexsIndex;
    m_vVertexsIndex = nullptr;

    delete m_vLineVertexs;
    m_vLineVertexs = nullptr;
    delete m_vLineNormal;
    m_vLineNormal = nullptr;
    delete m_vLineColor;
    m_vLineColor = nullptr;
    delete m_vLineIndex;
    m_vLineIndex = nullptr;

    delete m_vTrianglesVertexs;
    m_vTrianglesVertexs = nullptr;
    delete m_vTrianglesNormal;
    m_vTrianglesNormal = nullptr;
    delete m_vTrianglesColor;
    m_vTrianglesColor = nullptr;
    delete m_vTriangleIndex;
    m_vTriangleIndex = nullptr;

    delete m_vQuadsVertexs;
    m_vQuadsVertexs = nullptr;
    delete m_vQuadsNormal;
    m_vQuadsNormal = nullptr;
    delete m_vQuadsColor;
    m_vQuadsColor = nullptr;
    delete m_vQuadsIndex;
    m_vQuadsIndex = nullptr;
}

bool CBDFile::ReadFile(const QString &FilePath)
{
    QFile _file;
    _file.setFileName(FilePath);

    if (!_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    m_vCenter.setX(0);
    m_vCenter.setY(0);
    m_vCenter.setZ(0);

    float _maxX = 0;
    float _maxY = 0;
    float _maxZ = 0;
    float _minX = 0;
    float _minY = 0;
    float _minZ = 0;

    QTextStream _in(&_file);
    QMap<uint, uint> _indexMap;
    uint _count = 0;
    uint _QuadIndex = 0;
    uint _TriangleIndex = 0;

    QTime _time;
    _time.restart();  // start timekeeping

    while (!_in.atEnd())
    {
        QString _line = _in.readLine();
    }

    return true;
}

bool CBDFile::swapData(QVector3D        &vCenter_,
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
