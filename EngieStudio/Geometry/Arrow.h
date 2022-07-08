#ifndef ARROW_H
#define ARROW_H

#include <QColor>

#include <Windows.h>
#include "Vector3D.h"
#include "GL/gl.h"

#include <iostream>
using namespace std;

/*****************************************************
 * 箭头是由一个锥面，一个柱面，一个圆面，一个空心圆面组成
 * 第一个参数表示的是表示箭头的位置
 * 然后接着三个参数表示的是X轴/Y轴/Z轴方向
 * 第四个参数表示的是箭头的长度
 * ***************************************************/

class Arrow
{
public:
    explicit Arrow(Vector3D Position_,
                   Vector3D XAxis_,
                   Vector3D YAxis_,
                   Vector3D ZAxis_,
                   double   Length_);
    virtual ~Arrow();

public:
    void SetLength(double L_);
    void SetPosition(Vector3D Position_);
    void Clear();
    void Show();
    void setCircleColor(int, int, int, int = 255);
    void setCylinderColor(int, int, int, int = 255);
    void setHollowCircleColor(int, int, int, int = 255);
    void setConeColor(int,int, int, int = 255);

private:
    void CalculatePoint();  // 计算节点

private:
    double        m_fLength;
    Vector3D      m_vPosition;
    Vector3D      m_vXAxis;
    Vector3D      m_vYAxis;
    Vector3D      m_vZAxis;

    uint m_listName;
    bool   m_bDealde;

    // point count
    int m_dNumber;
    double m_nInsideRadius;        // 内圆半径
    double m_nOutsideRadius;       // 外援半径
    double m_nCylinderHeight;      // 圆柱高度
    double m_nConeHeight;          // 圆锥高度

    QColor m_cCircleColor;        // 圆的颜色
    QColor m_cCylinderColor;      // 圆柱体的颜色
    QColor m_cHollowCircleColor;  // 圆环颜色
    QColor m_cConeColor;          // 椎面颜色

    // circle data
    std::vector<GLdouble> m_vCircleVertexList;
    std::vector<GLdouble> m_vCircleColorList;
    std::vector<GLdouble> m_vCircleNormalList;
    std::vector<uint> m_vCircleIndexList;

    // Cylinder data
    std::vector<GLdouble> m_vCylinderVertexList;
    std::vector<GLdouble> m_vCylinderColorList;
    std::vector<GLdouble> m_vCylinderNormalList;
    std::vector<uint> m_vCylinderIndexList;

    // HollowCircle data
    std::vector<GLdouble> m_vHollowCircleVertexList;
    std::vector<GLdouble> m_vHollowCircleColorList;
    std::vector<GLdouble> m_vHollowCircleNormalList;
    std::vector<uint> m_vHollowCircleIndexList;

    // Cone data
    std::vector<GLdouble> m_vConeVertexList;
    std::vector<GLdouble> m_vConeColorList;
    std::vector<GLdouble> m_vConeNormalList;
    std::vector<uint> m_vConeIndexList;
};

#endif // ARROW_H
