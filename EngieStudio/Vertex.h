#ifndef VERTEX_H
#define VERTEX_H

#include "Object.h"

class PointObject;

class Vertex : public PointObject
{
public:
    explicit Vertex(const float x_ = 0, const float y_ = 0, const float z_ = 0);
//    explicit Vertex(QVector<float>);
    ~Vertex();

public:
    virtual void  setColor(const int r_, const int g_, const int b_, const int apha_ = 255);
    virtual void  setColor(const float r_, const float g_, const float b_, const float apha_ = 1.0f);
    virtual void  getColor(float &r_, float &g_, float &b_, float &apha_ );
    inline  void  setX(const float);
    inline  void  setY(const float);
    inline  void  setZ(const float);
    inline  float getX() const;
    inline  float getY() const;
    inline  float getZ() const;
    inline  void  setR(const float);
    inline  void  setG(const float);
    inline  void  setB(const float);
    inline  void  setA(const float);
    inline  float getR() const;
    inline  float getG() const;
    inline  float getB() const;
    inline  float getA() const;

protected:

private:

public:
//    QVector<float>    *m_vVertexVector;     // all the object vertex list

protected:

private:
};

#endif // VERTEX_H
