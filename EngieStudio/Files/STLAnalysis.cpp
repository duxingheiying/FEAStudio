#include "STLAnalysis.h"

#include <iostream>
#include <math.h>

#include "parse_stl.h"

STLFile::STLFile(QObject *parent)
    : AnalysisFile{parent}
{
}

bool STLFile::ReadFile(const QString &FilePath_)
{
    auto info = stl::parse_stl(FilePath_.toStdString());
    std::vector<stl::triangle> triangles = info.triangles;
    std::cout << "STL HEADER = " << info.name << std::endl;
    std::cout << "# triangles = " << triangles.size() << std::endl;

    size_t trangel_size = info.triangles.size();

    // apply fot space prefer
    if ( m_vTrianglesVertexs != nullptr ) {
        delete m_vTrianglesVertexs;
        m_vTrianglesVertexs = nullptr;
    }
    m_vTrianglesVertexs = new QVector<float>(trangel_size*9);

    if ( m_vTrianglesColor != nullptr ) {
        delete m_vTrianglesColor;
        m_vTrianglesColor = nullptr;
    }
    m_vTrianglesColor = new QVector<float>(trangel_size*9);

    if ( m_vTrianglesNormal != nullptr ) {
        delete m_vTrianglesNormal;
        m_vTrianglesNormal = nullptr;
    }
    m_vTrianglesNormal = new QVector<float>(trangel_size*9);

    if ( m_vTriangleIndex != nullptr ) {
        delete m_vTriangleIndex;
        m_vTriangleIndex = nullptr;
    }
    m_vTriangleIndex = new QVector<uint>(trangel_size*3);

    const QColor _setColor = QColor(200, 190, 185);

    float _maxX = 0;
    float _maxY = 0;
    float _maxZ = 0;
    float _minX = 0;
    float _minY = 0;
    float _minZ = 0;

    for (size_t t = 0; t < trangel_size; t++) { // all the triangles
        if (t == 0 ){
            _minX = std::min(std::min(info.triangles[t].v1.x, info.triangles[t].v2.x), info.triangles[t].v3.x);
            _maxX = std::max(std::max(info.triangles[t].v1.x, info.triangles[t].v2.x), info.triangles[t].v3.x);
            _minY = std::min(std::min(info.triangles[t].v1.y, info.triangles[t].v2.y), info.triangles[t].v3.y);
            _maxY = std::max(std::max(info.triangles[t].v1.y, info.triangles[t].v2.y), info.triangles[t].v3.y);
            _minZ = std::min(std::min(info.triangles[t].v1.z, info.triangles[t].v2.z), info.triangles[t].v3.z);
            _maxZ = std::max(std::max(info.triangles[t].v1.z, info.triangles[t].v2.z), info.triangles[t].v3.z);
        } else {
            _minX = std::min(std::min(std::min(info.triangles[t].v1.x, info.triangles[t].v2.x), info.triangles[t].v3.x), _minX);
            _maxX = std::max(std::max(std::max(info.triangles[t].v1.x, info.triangles[t].v2.x), info.triangles[t].v3.x), _maxX);
            _minY = std::min(std::min(std::min(info.triangles[t].v1.y, info.triangles[t].v2.y), info.triangles[t].v3.y), _minY);
            _maxY = std::max(std::max(std::max(info.triangles[t].v1.y, info.triangles[t].v2.y), info.triangles[t].v3.y), _maxX);
            _minZ = std::min(std::min(std::min(info.triangles[t].v1.z, info.triangles[t].v2.z), info.triangles[t].v3.z), _minZ);
            _maxZ = std::max(std::max(std::max(info.triangles[t].v1.z, info.triangles[t].v2.z), info.triangles[t].v3.z), _maxZ);
        }

        (*m_vTrianglesVertexs)[static_cast<int>(t)*9] = info.triangles[t].v1.x;
        (*m_vTrianglesVertexs)[static_cast<int>(t)*9+1] = info.triangles[t].v1.y;
        (*m_vTrianglesVertexs)[static_cast<int>(t)*9+2] = info.triangles[t].v1.z;
        (*m_vTrianglesVertexs)[static_cast<int>(t)*9+3] = info.triangles[t].v2.x;
        (*m_vTrianglesVertexs)[static_cast<int>(t)*9+4] = info.triangles[t].v2.y;
        (*m_vTrianglesVertexs)[static_cast<int>(t)*9+5] = info.triangles[t].v2.z;
        (*m_vTrianglesVertexs)[static_cast<int>(t)*9+6] = info.triangles[t].v3.x;
        (*m_vTrianglesVertexs)[static_cast<int>(t)*9+7] = info.triangles[t].v3.y;
        (*m_vTrianglesVertexs)[static_cast<int>(t)*9+8] = info.triangles[t].v3.z;

        (*m_vTrianglesNormal)[static_cast<int>(t)*9] = (*m_vTrianglesNormal)[static_cast<int>(t)*9+3] = (*m_vTrianglesNormal)[static_cast<int>(t)*9+6] = info.triangles[t].normal.x;
        (*m_vTrianglesNormal)[static_cast<int>(t)*9+1] = (*m_vTrianglesNormal)[static_cast<int>(t)*9+4] = (*m_vTrianglesNormal)[static_cast<int>(t)*9+7] = info.triangles[t].normal.y;
        (*m_vTrianglesNormal)[static_cast<int>(t)*9+2] = (*m_vTrianglesNormal)[static_cast<int>(t)*9+5] = (*m_vTrianglesNormal)[static_cast<int>(t)*9+8] =info.triangles[t].normal.z;

        (*m_vTrianglesColor)[static_cast<int>(t)*9] = (*m_vTrianglesColor)[static_cast<int>(t)*9+3] = (*m_vTrianglesColor)[static_cast<int>(t)*9+6] = _setColor.redF();
        (*m_vTrianglesColor)[static_cast<int>(t)*9+1] = (*m_vTrianglesColor)[static_cast<int>(t)*9+4] = (*m_vTrianglesColor)[static_cast<int>(t)*9+7] = _setColor.greenF();
        (*m_vTrianglesColor)[static_cast<int>(t)*9+2] = (*m_vTrianglesColor)[static_cast<int>(t)*9+5] = (*m_vTrianglesColor)[static_cast<int>(t)*9+8] = _setColor.blueF();

        (*m_vTriangleIndex)[static_cast<int>(t)*3] = static_cast<uint>(t)*3;
        (*m_vTriangleIndex)[static_cast<int>(t)*3+1] = static_cast<uint>(t)*3+1;
        (*m_vTriangleIndex)[static_cast<int>(t)*3+2] = static_cast<uint>(t)*3+2;
    }

    m_vCenter.setX( ( _maxX + _minX ) / 2 );
    m_vCenter.setY( ( _maxY + _minY ) / 2 );
    m_vCenter.setZ( ( _maxZ + _minZ ) / 2 );

    m_fRange = static_cast<float>(sqrt(std::pow(static_cast<double>(_maxX) - static_cast<double>(_minX), 2.0)+
                                       std::pow(static_cast<double>(_maxY) - static_cast<double>(_minY), 2.0)+
                                       std::pow(static_cast<double>(_maxZ) - static_cast<double>(_minZ), 2.0)));

    emit ReadFileFinished();
    return true;
}
