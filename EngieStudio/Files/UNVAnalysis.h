#ifndef UNVANALYSIS_H
#define UNVANALYSIS_H

#include "AnalysisFile.h"

class UNVFile : public AnalysisFile
{
public:
    explicit UNVFile(AnalysisFile *parent = nullptr);
    virtual ~UNVFile() override;

public:
    virtual bool ReadFile(const QString &FilePath) override;
    // switch the buffur
    virtual bool swapData(QVector3D        &vCenter_,
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
                          QVector<uint>  &vQuadIndex_) override;
};

#endif // UNVANALYSIS_H
