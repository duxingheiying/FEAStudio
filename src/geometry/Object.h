#ifndef OBJECT_H
#define OBJECT_H

#include <QVector3D>
#include <QVector>
#include <QObject>
#include <QColor>

class Object : public QObject
{
    Q_OBJECT

public:
    explicit Object();
    virtual ~Object();

    // function
public:
    bool m_bOutSide = true;
    virtual void Show() = 0;  // show the object

protected:

private:

    // variable
public:
//    typedef enum OB_TYPE {
//        Object_NULL,
//        Object_PT,
//        Object_LINE,
//        Object_TRIANGLE,
//        Object_QUAD,
//        Object_TETRA,
//        Object_PENTRA,
//        Object_HEXA
//    } OBJECT_TYPE;
//    OBJECT_TYPE m_eType;             // the object type
    uint m_uObjectID;                      // Object ID
    float m_fRed;
    float m_fGreen;
    float m_fBlue;
    float m_fAlpha = 1.0f;

protected:

private:

};

class PointObject : public Object
{
public:
    explicit PointObject();
    ~PointObject();

public:
    // virtual void CalcualteNormal() = 0;  // calculate the all face normal
    virtual void setColor(const int r_,
                          const int g_,
                          const int b_,
                          const int apha_ = 255) = 0;

    virtual void setColor(const float r_,
                          const float g_,
                          const float b_,
                          const float apha_ = 1.0f) = 0;

    virtual void getColor(float &r_, float &g_, float &b_, float &apha_ )= 0;

public:
    float m_fX;
    float m_fY;
    float m_fZ;
};


class plateObject : public Object
{
public:
    explicit plateObject();
    ~plateObject();

public:
//    virtual QString getIDName();  // return the PointIDs has been sorted string

protected:
//    virtual void calculateIDName();

private:

public:
//    QVector<float> *m_vVertexVector;  // all the object vertex list
//    QVector<float> *m_vColorVector;   // all the point color list
//    QVector<float> *m_vNormaleVector; // all the point Normal list
//    QVector<uint>   m_vUsePointIDList;   // all used point ID list, ID doesn't sort
    QString m_sUnitPointIDList;  // unite use Point ID list ID sorted commbine into a string

protected:

private:
};

class PT : public PointObject
{
public:
    explicit PT( float x_ = 0 ,
                 float y_ = 0,
                 float z_ = 0,
                 uint pointID_ = 0);
    ~PT();

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

    void Show(){}

protected:

private:

public:
//    QVector<float>    *m_vVertexVector;     // all the object vertex list

protected:

private:
};

// Create a Line
class LINE : public plateObject
{
public:
    explicit LINE(uint firstpointID_ = 0, uint secondPointID_ = 0);
    ~LINE();

public:
    void Show(){}

protected:

private:

public:

protected:

private:
};

// Create a Triangle
class TRIANGLE : public plateObject
{
public:
    explicit TRIANGLE(const uint& firstpointID_,
                      const uint& secondpointID_,
                      const uint& thirdpointID_,
                      const float& red_,
                      const float& green_,
                      const float& blue_);
    ~TRIANGLE();

public:
    void Show(){}

protected:

private:

public:
    uint m_uFirstPointID;
    uint m_uSecondPointID;
    uint m_uThirdPointID;

protected:

private:
};

// Create a Quad
class QUAD : public plateObject
{
public:
    explicit QUAD(const uint& firstpointID_,
                  const uint& secondpointID_,
                  const uint& thirdpointID_,
                  const uint& forthpointID_,
                  const float& red_,
                  const float& green_,
                  const float& blue_);
    ~QUAD();

    // limite all the public function
public:
    void Show(){}
//    virtual inline void setColor(int r_,    int g_,    int b_,    int apha_ = 255);
//    virtual inline void setColor(float r_,  float g_,  float b_,  float apha_ = 1.0f);
//    virtual inline void getColor(float &r_, float &g_, float &b_, float &apha_);

    //  limite all the protect function
protected:

    // limite all the private function
private:
//    inline virtual void CalcualteNormal();

    // limite all the variable
public:
    uint m_uFirstPointID;
    uint m_uSecondPointID;
    uint m_uThirdPointID;
    uint m_uFourthPointID;

//    float m_fRed;
//    float m_fGreen;
//    float m_fBlue;
//    float m_alpha;

    // limite all the protect variable
protected:

    // limite all the private variable
private:
};

// four face hedron
class TETRA : public Object
{
public:
    explicit TETRA();
    ~TETRA();
};

// five face hedron
class PENTRA : public Object
{
public:
    explicit PENTRA();
    ~PENTRA();
};

// six face hedron
class HEXA : public Object
{
public:
    explicit HEXA();
    ~HEXA();
};

class EntityObject : public Object
{
public:
    explicit EntityObject();
    ~EntityObject();

public:
    virtual void getAllShow(QHash<QString, TRIANGLE*>& triangleHash_, QHash<QString, QUAD*>& quadHash_);

protected:
    // add new triangle to the triangle hashMap
    virtual void getTriangleShow(const QString& firstPointID_, const QString& secondPointID_, const QString& thirdPointID_,
                                 const float &red_, const float &green_, const float &blue_, QHash<QString, TRIANGLE*>& triangleHash_);

    // add new Quad to the quad hashMap
    virtual void getQuadrangleShow(const QString& firstPointID_, const QString& secondPointID_,
                                   const QString& thirdPointID_, const QString& fourthPointID_,
                                   const float &red_, const float &green_, const float &blue_, QHash<QString, QUAD*>& quadHash_);

public:
    uint m_uMaterialID; // material ID
    QStringList m_sUnitPointIDList;    // unite use Point ID list ID sorted commbine into a string
};

#endif // OBJECT_H
