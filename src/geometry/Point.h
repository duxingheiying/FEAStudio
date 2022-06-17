/*************************************************************************************
 *
 * this cloass if for drawwing a Point
 *
 *
 * ************************************************************************************/


#ifndef POINT_H
#define POINT_H

#include "Object.h"

class Point : public PointObject
{
public:
    explicit Point(const float& x_,
                   const float& y_ ,
                   const float& z_ ,
                   const uint& pintID_);
    ~Point();

public:
    virtual void setPoint(const float x_,
                          const float y_,
                          const float z_);
    virtual void setColor(const int r_,
                          const int g_,
                          const int b_,
                          const int alpha_ = 255);
    virtual void setColor(const float r_,
                          const float g_,
                          const float b_,
                          const float alpha_ = 1.0f);
    virtual void getColor(float &r_, float &g_, float &b_, float &alpha_ );
    virtual void Show();

protected:

private:

public:
    QVector<uint> m_aPointArrID; // the position of point in array for change color and position
    QVector<float*> m_aPointaddList; // point address for change the postion
    QVector<float*> m_aPColorList; // the normal list

protected:

private:

};

#endif // POINT_H
