#include "Arrow.h"

#include <qmath.h>

Arrow::Arrow(Vector3D Position_,
             Vector3D XAxis_,
             Vector3D YAxis_,
             Vector3D ZAxis_,
             double Length_)
{
    m_fLength = Length_;
    m_vPosition = Position_;
    m_vXAxis = XAxis_.normalized();   // 单位化向量
    m_vYAxis = YAxis_.normalized();   // 单位化向量
    m_vZAxis = ZAxis_.normalized();   // 单位化向量

    m_listName = glGenLists(1);

    m_dNumber = 50;

    // 设置各个面颜色
    setCircleColor(255, 0, 0, 200);        // 圆的颜色
    setCylinderColor(200, 200, 200, 200);      // 圆柱体的颜色
    setHollowCircleColor(200, 200, 200, 200);  // 圆环颜色
    setConeColor(255, 0, 0, 200);          // 椎面颜色

    m_nInsideRadius = m_fLength / 20;  // 计算内圆半径
    m_nCylinderHeight = m_fLength / 10 * 7;  // 计算圆柱高度
    m_nOutsideRadius = m_fLength / 10;  // 计算外圆的大小
    CalculatePoint();
}

void Arrow::setCircleColor(int red_, int green_, int blue_, int arpha_)
{
    m_cCircleColor = QColor(red_, green_, blue_, arpha_);        // 圆的颜色

    std::vector<GLdouble>::iterator _itor = m_vCircleColorList.begin();
    int _i = 0;
    while (_itor != m_vCircleColorList.end() ) {
        int _current = _i % 4;
        switch ( _current ) {
        case 0:
            (*_itor) = red_;
            break;

        case 1:
            (*_itor) = green_;
            break;

        case 2:
            (*_itor) = blue_;
            break;

        case 3:
            (*_itor) = arpha_;
            break;

        default:
            break;
        }

        _i++;
        _itor++;
    }
}

void Arrow::setCylinderColor(int red_, int green_, int blue_, int arpha_)
{
    m_cCylinderColor = QColor(red_, green_, blue_, arpha_);      // 圆柱体的颜色

    std::vector<GLdouble>::iterator _itor = m_vCylinderColorList.begin();
    int _i = 0;
    while (_itor != m_vCylinderColorList.end() ) {
        int _current = _i % 4;
        switch ( _current ) {
        case 0:
            (*_itor) = red_;
            break;

        case 1:
            (*_itor) = green_;
            break;

        case 2:
            (*_itor) = blue_;
            break;

        case 3:
            (*_itor) = arpha_;
            break;

        default:
            break;
        }
        _i++;
        _itor++;
    }
}

void Arrow::setHollowCircleColor(int red_, int green_, int blue_, int arpha_)
{
    m_cHollowCircleColor = QColor(red_, green_, blue_, arpha_);  // 圆环颜色

    std::vector<GLdouble>::iterator _itor = m_vHollowCircleColorList.begin();
    int _i = 0;
    while (_itor != m_vHollowCircleColorList.end() ) {
        int _current = _i % 4;
        switch ( _current ) {
        case 0:
            (*_itor) = red_;
            break;

        case 1:
            (*_itor) = green_;
            break;

        case 2:
            (*_itor) = blue_;
            break;

        case 3:
            (*_itor) = arpha_;
            break;

        default:
            break;
        }
        _i++;
        _itor++;
    }
}

void Arrow::setConeColor(int red_, int green_, int blue_, int arpha_)
{
    m_cConeColor = QColor(red_, green_, blue_, arpha_);          // 椎面颜色

    std::vector<GLdouble>::iterator _itor = m_vConeColorList.begin();
    int _i = 0;
    while (_itor != m_vConeColorList.end() ) {
        int _current = _i % 4;
        switch ( _current ) {
        case 0:
            (*_itor) = red_;
            break;

        case 1:
            (*_itor) = green_;
            break;

        case 2:
            (*_itor) = blue_;
            break;

        case 3:
            (*_itor) = arpha_;
            break;

        default:
            break;
        }
        _i++;
        _itor++;
    }
}


void Arrow::CalculatePoint()
{
    // 重新申请新的空间
    Vector3D _upPosition = m_vPosition + m_nCylinderHeight * m_vZAxis;  // 计算帽檐所在高度
    Vector3D _topPosition = m_vPosition + m_fLength * m_vZAxis;   // 计算定点所在位置
    uint _pointIDIndex = 0;
    Vector3D _lastTopVertexNormal(0.0, 0.0, 0.0);

    double _rangle = M_PI / m_dNumber * 2;
    for(double _CurrentAngle = 0.0; _CurrentAngle <= 2 * M_PI; _CurrentAngle += _rangle)
    {
        Vector3D _offsetdis = m_nInsideRadius * cos(_CurrentAngle) * m_vXAxis +
                m_nInsideRadius * sin(_CurrentAngle) * m_vYAxis;

        // 计算底层圆的边界点
        Vector3D _vector = m_vPosition + _offsetdis;

        /*************************************************************************
         * 计算下圆面的所有节点位置，颜色，法向
         * ***********************************************************************/
        m_vCircleVertexList.push_back(_vector.x());
        m_vCircleVertexList.push_back(_vector.y());
        m_vCircleVertexList.push_back(_vector.z());

        // 圆的颜色
        m_vCircleColorList.push_back(m_cCircleColor.redF());
        m_vCircleColorList.push_back(m_cCircleColor.greenF());
        m_vCircleColorList.push_back(m_cCircleColor.blueF());
        m_vCircleColorList.push_back(m_cCircleColor.alphaF());

        // 圆的法向
        m_vCircleNormalList.push_back(-m_vZAxis.x());
        m_vCircleNormalList.push_back(-m_vZAxis.y());
        m_vCircleNormalList.push_back(-m_vZAxis.z());

        // 圆节点索引
        m_vCircleIndexList.push_back( static_cast<uint>(m_vCircleIndexList.size()));

        /*************************************************************************
         * 计算圆柱体的各个节点的位置
         * ***********************************************************************/
        m_vCylinderVertexList.push_back(_vector.x());
        m_vCylinderVertexList.push_back(_vector.y());
        m_vCylinderVertexList.push_back(_vector.z());
        _vector += m_nCylinderHeight * m_vZAxis;           // 将节点在局部Y上移动设定好的距离
        m_vCylinderVertexList.push_back(_vector.x());
        m_vCylinderVertexList.push_back(_vector.y());
        m_vCylinderVertexList.push_back(_vector.z());

        // 添加圆柱体节点的颜色
        m_vCylinderColorList.push_back(m_cCylinderColor.redF());
        m_vCylinderColorList.push_back(m_cCylinderColor.greenF());
        m_vCylinderColorList.push_back(m_cCylinderColor.blueF());
        m_vCylinderColorList.push_back(m_cCylinderColor.alphaF());

        m_vCylinderColorList.push_back(m_cCylinderColor.redF());
        m_vCylinderColorList.push_back(m_cCylinderColor.greenF());
        m_vCylinderColorList.push_back(m_cCylinderColor.blueF());
        m_vCylinderColorList.push_back(m_cCylinderColor.alphaF());

        // 添加节点法向
        m_vCylinderNormalList.push_back(_offsetdis.x());
        m_vCylinderNormalList.push_back(_offsetdis.y());
        m_vCylinderNormalList.push_back(_offsetdis.z());
        m_vCylinderNormalList.push_back(_offsetdis.x());
        m_vCylinderNormalList.push_back(_offsetdis.y());
        m_vCylinderNormalList.push_back(_offsetdis.z());

        m_vCylinderIndexList.push_back( static_cast<uint>(m_vCylinderIndexList.size()) );
        m_vCylinderIndexList.push_back( static_cast<uint>(m_vCylinderIndexList.size()) );

        /*************************************************************************
         * 计算圆环节点颜色, 可以直接使用上层的节点
         * ***********************************************************************/
        // 内圆周节点
        m_vHollowCircleVertexList.push_back(_vector.x());
        m_vHollowCircleVertexList.push_back(_vector.y());
        m_vHollowCircleVertexList.push_back(_vector.z());

        // 计算外圆节点
        _offsetdis = m_nOutsideRadius * cos(_CurrentAngle) * m_vXAxis +
                m_nOutsideRadius * sin(_CurrentAngle) * m_vYAxis;
        _vector = _upPosition + _offsetdis;

        m_vHollowCircleVertexList.push_back(_vector.x());
        m_vHollowCircleVertexList.push_back(_vector.y());
        m_vHollowCircleVertexList.push_back(_vector.z());

        // 添加圆柱体节点的颜色
        m_vHollowCircleColorList.push_back(m_cHollowCircleColor.redF());
        m_vHollowCircleColorList.push_back(m_cHollowCircleColor.greenF());
        m_vHollowCircleColorList.push_back(m_cHollowCircleColor.blueF());
        m_vHollowCircleColorList.push_back(m_cHollowCircleColor.alphaF());
        m_vHollowCircleColorList.push_back(m_cHollowCircleColor.redF());
        m_vHollowCircleColorList.push_back(m_cHollowCircleColor.greenF());
        m_vHollowCircleColorList.push_back(m_cHollowCircleColor.blueF());
        m_vHollowCircleColorList.push_back(m_cHollowCircleColor.alphaF());

        // 添加节点法向
        m_vHollowCircleNormalList.push_back(-m_vZAxis.x());
        m_vHollowCircleNormalList.push_back(-m_vZAxis.y());
        m_vHollowCircleNormalList.push_back(-m_vZAxis.z());
        m_vHollowCircleNormalList.push_back(-m_vZAxis.x());
        m_vHollowCircleNormalList.push_back(-m_vZAxis.y());
        m_vHollowCircleNormalList.push_back(-m_vZAxis.z());

        m_vHollowCircleIndexList.push_back( static_cast<uint>(m_vHollowCircleIndexList.size()) );
        m_vHollowCircleIndexList.push_back( static_cast<uint>(m_vHollowCircleIndexList.size()) );

        /*************************************************************************
         * 绘制圆锥体
         * ***********************************************************************/
        // 设置三角形定点
        m_vConeVertexList.push_back(_topPosition.x());
        m_vConeVertexList.push_back(_topPosition.y());
        m_vConeVertexList.push_back(_topPosition.z());

        // 设置三角形的下边点
        m_vConeVertexList.push_back(_vector.x());
        m_vConeVertexList.push_back(_vector.y());
        m_vConeVertexList.push_back(_vector.z());

        m_vConeColorList.push_back(m_cConeColor.redF());
        m_vConeColorList.push_back(m_cConeColor.greenF());
        m_vConeColorList.push_back(m_cConeColor.blueF());
        m_vConeColorList.push_back(m_cConeColor.alphaF());
        m_vConeColorList.push_back(m_cConeColor.redF());
        m_vConeColorList.push_back(m_cConeColor.greenF());
        m_vConeColorList.push_back(m_cConeColor.blueF());
        m_vConeColorList.push_back(m_cConeColor.alphaF());

        // 计算节点的法向,
        Vector3D _normal = _offsetdis.crossProduct(m_vZAxis).crossProduct(_vector - _topPosition).normalized();
        Vector3D _topNormal = _lastTopVertexNormal+_normal;
        _lastTopVertexNormal = _normal;

        m_vConeNormalList.push_back(_topNormal.x());
        m_vConeNormalList.push_back(_topNormal.y());
        m_vConeNormalList.push_back(_topNormal.z());

        m_vConeNormalList.push_back(_normal.x());
        m_vConeNormalList.push_back(_normal.y());
        m_vConeNormalList.push_back(_normal.z());

        // 表示是第一个节点
        if ( _CurrentAngle == 0.0 ) {
            m_vConeIndexList.push_back(2*_pointIDIndex+1);
            m_vConeIndexList.push_back(2*_pointIDIndex);
            _pointIDIndex++;
        }
        else {
            m_vConeIndexList.push_back(2*_pointIDIndex+1);
            m_vConeIndexList.push_back(2*_pointIDIndex+1);
            m_vConeIndexList.push_back(2*_pointIDIndex);
            _pointIDIndex++;
        }

        // 补充对应的圆柱和空心圆的最后两个连接点
        if (_CurrentAngle + _rangle > 2 * M_PI) {
            m_vCylinderIndexList.push_back( 0 );
            m_vCylinderIndexList.push_back( 1 );
            m_vHollowCircleIndexList.push_back( 0 );
            m_vHollowCircleIndexList.push_back( 1 );
            m_vConeIndexList.push_back(1);
        }
    }
}

void Arrow::SetLength(double L_)
{
    m_fLength = L_;
    m_nInsideRadius = m_fLength / 20;  // 计算内圆半径
    m_nCylinderHeight = m_fLength / 10 * 7;  // 计算圆柱高度
    m_nOutsideRadius = m_fLength / 10;  // 计算外圆的大小
    this->Clear();
    CalculatePoint();
}

void Arrow::SetPosition(Vector3D Position_)
{
    m_vPosition = Position_;
    this->Clear();
    CalculatePoint();
}

void Arrow::Show()
{
    // 绘制下地面圆
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState( GL_NORMAL_ARRAY );
    if (m_vCircleVertexList.size() > 0 && m_vCircleVertexList.size() > 0 &&
            m_vCircleVertexList.size() > 0 && m_vCircleVertexList.size() > 0) {
        glVertexPointer( 3, GL_DOUBLE, 0, static_cast<GLdouble*>(&m_vCircleVertexList[0]) );
        glColorPointer( 4, GL_DOUBLE, 0, static_cast<GLdouble*>(&m_vCircleColorList[0]) );
        glNormalPointer( GL_DOUBLE, 0, static_cast<GLdouble*>(&m_vCircleNormalList[0]) );
        glDrawElements( GL_POLYGON,
                        static_cast<GLsizei>(m_vCircleIndexList.size()),
                        GL_UNSIGNED_INT,
                        static_cast<uint*>(&m_vCircleIndexList[0]));  // 开始绘制图形
    }

    // 绘制圆柱体
    if (m_vCylinderVertexList.size() > 0 && m_vCylinderColorList.size() > 0 &&
            m_vCylinderNormalList.size() > 0 && m_vCylinderIndexList.size() > 0) {
        glVertexPointer( 3, GL_DOUBLE, 0, static_cast<GLdouble*>(&m_vCylinderVertexList[0]) );
        glColorPointer( 4, GL_DOUBLE, 0, static_cast<GLdouble*>(&m_vCylinderColorList[0]) );
        glNormalPointer( GL_DOUBLE, 0, static_cast<GLdouble*>(&m_vCylinderNormalList[0]) );
        glDrawElements( GL_QUAD_STRIP,
                        static_cast<GLsizei>(m_vCylinderIndexList.size()),
                        GL_UNSIGNED_INT,
                        static_cast<uint*>(&m_vCylinderIndexList[0]));  // 开始绘制图形
    }

    // 绘制圆环
    if (m_vHollowCircleVertexList.size() > 0 && m_vHollowCircleColorList.size() > 0 &&
            m_vHollowCircleNormalList.size() > 0 && m_vHollowCircleIndexList.size() > 0) {
        glVertexPointer( 3, GL_DOUBLE, 0, static_cast<GLdouble*>(&m_vHollowCircleVertexList[0]) );
        glColorPointer( 4, GL_DOUBLE, 0, static_cast<GLdouble*>(&m_vHollowCircleColorList[0]) );
        glNormalPointer( GL_DOUBLE, 0, static_cast<GLdouble*>(&m_vHollowCircleNormalList[0]) );
        glDrawElements( GL_QUAD_STRIP,
                        static_cast<GLsizei>(m_vHollowCircleIndexList.size()),
                        GL_UNSIGNED_INT,
                        static_cast<uint*>(&m_vHollowCircleIndexList[0]));  // 开始绘制图形
    }

    // 绘制椎体
    if (m_vConeVertexList.size() > 0 && m_vConeColorList.size() > 0 &&
            m_vConeNormalList.size() > 0 && m_vConeIndexList.size() > 0) {
        glVertexPointer( 3, GL_DOUBLE, 0, static_cast<GLdouble*>(&m_vConeVertexList[0]) );
        glColorPointer( 4, GL_DOUBLE, 0, static_cast<GLdouble*>(&m_vConeColorList[0]) );
        glNormalPointer( GL_DOUBLE, 0, static_cast<GLdouble*>(&m_vConeNormalList[0]) );
        glDrawElements( GL_TRIANGLES,
                        static_cast<GLsizei>(m_vConeIndexList.size()),
                        GL_UNSIGNED_INT,
                        static_cast<uint*>(&m_vConeIndexList[0]));  // 开始绘制图形
    }
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void Arrow::Clear()
{
    // 清理所有圆的数据
    std::vector<GLdouble>().swap(m_vCircleVertexList);
    m_vCircleVertexList.clear();
    std::vector<GLdouble>().swap(m_vCircleColorList);
    m_vCircleColorList.clear();
    std::vector<GLdouble>().swap(m_vCircleNormalList);
    m_vCircleNormalList.clear();
    std::vector<uint>().swap(m_vCircleIndexList);
    m_vCircleIndexList.clear();

    // 清理所有圆柱的颜色
    std::vector<GLdouble>().swap(m_vCylinderVertexList);
    m_vCylinderVertexList.clear();
    std::vector<GLdouble>().swap(m_vCylinderColorList);
    m_vCylinderColorList.clear();
    std::vector<GLdouble>().swap(m_vCylinderNormalList);
    m_vCylinderNormalList.clear();
    std::vector<uint>().swap(m_vCylinderIndexList);
    m_vCylinderIndexList.clear();

    // 清理掉所有空心圆的颜色
    std::vector<GLdouble>().swap(m_vHollowCircleVertexList);
    m_vHollowCircleVertexList.clear();
    std::vector<GLdouble>().swap(m_vHollowCircleColorList);
    m_vHollowCircleColorList.clear();
    std::vector<GLdouble>().swap(m_vHollowCircleNormalList);
    m_vHollowCircleNormalList.clear();
    std::vector<uint>().swap(m_vHollowCircleIndexList);
    m_vHollowCircleIndexList.clear();

    // 清理所有圆锥的颜色
    std::vector<GLdouble>().swap(m_vConeVertexList);
    m_vConeVertexList.clear();
    std::vector<GLdouble>().swap(m_vConeColorList);
    m_vConeColorList.clear();
    std::vector<GLdouble>().swap(m_vConeNormalList);
    m_vConeNormalList.clear();
    std::vector<uint>().swap(m_vConeIndexList);
    m_vConeIndexList.clear();
}

Arrow::~Arrow()
{
    this->Clear();
}
