#include "UFFAnalysis.h"
#include <QFile>

UFFFile::UFFFile(AnalysisFile* parent) :
    AnalysisFile (parent)
{
}

UFFFile::~UFFFile()
{
}

bool UFFFile::ReadFile(const QString &FilePath)
{
    QFile _file;
    _file.setFileName(FilePath);

    if (!_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    return false;
}

bool UFFFile::swapData(QVector3D        &vCenter_,
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
    Rand_ = m_fRange;
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
