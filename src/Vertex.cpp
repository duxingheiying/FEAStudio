#include "Vertex.h"

Vertex::Vertex(const float x_, const float y_, const float z_)
{
//    m_eType  = Object_PT;

    m_fX = x_;
    m_fY = y_;
    m_fZ = z_;
}
//Vertex::Vertex(QVector<float> vector_)
//{
//    m_eType  = Object_PT;
//    m_vVertexVector->swap(vector_);
//}

Vertex::~Vertex()
{
}

void Vertex::setX(const float x_)
{
    m_fX = x_;
}

void Vertex::setY(const float y_)
{
    m_fY = y_;
}

void Vertex::setZ(const float z_)
{
    m_fZ = z_;
}

float Vertex::getX() const
{
    return m_fX;
}

float Vertex::getY() const
{
    return m_fY;
}

float Vertex::getZ() const
{
    return m_fZ;
}

void Vertex::setColor(const int r_, const int g_, const int b_, const int apha_)
{
    m_fRed = r_/static_cast<float>(255);
    m_fGreen = g_/static_cast<float>(255);
    m_fBlue = b_/static_cast<float>(255);
    m_fAlpha = apha_/static_cast<float>(255);
}
void Vertex::setColor(const float r_, const float g_, const float b_, const float apha_)
{
    m_fRed = r_;
    m_fGreen = g_;
    m_fBlue = b_;
    m_fAlpha = apha_;
}

void  Vertex::getColor(float &r_, float &g_, float &b_, float &apha_ )
{
    r_   = m_fRed;
    g_   = m_fGreen;
    b_   = m_fBlue;
    apha_= m_fAlpha;
}

inline void Vertex::setR(const float r_)
{
    m_fRed = r_;
}

inline void Vertex::setG(const float g_)
{
    m_fGreen = g_;
}

inline void Vertex::setB(const float b_)
{
    m_fBlue = b_;
}

inline void Vertex::setA(const float a_)
{
    m_fAlpha = a_;
}

inline float Vertex::getR() const
{
    return m_fRed;
}

inline float Vertex::getG() const
{
    return m_fGreen;
}

inline float Vertex::getB() const
{
    return m_fBlue;
}

inline float Vertex::getA() const
{
    return m_fAlpha;
}
