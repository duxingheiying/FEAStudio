#include "Point.h"

Point::Point(const float &x_,
             const float &y_,
             const float &z_,
             const uint &pintID_)
{
    m_fX = x_;
    m_fY = y_;
    m_fZ = z_;
    m_uObjectID = pintID_;
}

void Point::setPoint(const float x_, const float y_, const float z_)
{
    m_fX = x_;
    m_fY = y_;
    m_fZ = z_;
}

void Point::setColor(const int r_,  const int g_, const int b_, const int alpha_)
{
    m_fRed = r_/255.0f;
    m_fGreen = g_/255.0f;
    m_fBlue = b_/255.0f;
    m_fAlpha = alpha_/255.0f;
}

void Point::setColor(const float r_,
                     const float g_,
                     const float b_,
                     const float alpha_)
{
    m_fRed = r_;
    m_fGreen = g_;
    m_fBlue = b_;
    m_fAlpha = alpha_;
}

void Point::getColor(float &r_, float &g_, float &b_, float &alpha_ )
{
    r_ = m_fRed;
    g_ = m_fGreen;
    b_ = m_fBlue;
    alpha_ = m_fAlpha;
}

void Point::Show()
{
}

Point::~Point()
{
    m_aPointArrID.clear(); // the position of point in array for change color and position
    m_aPointaddList.clear(); // point address for change the postion
    m_aPColorList.clear(); // the normal list
}
