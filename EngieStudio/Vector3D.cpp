/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia. For licensing terms and
** conditions see http://qt.digia.com/licensing. For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "Vector3D.h"
#include "qvector2d.h"
#include "qvector4d.h"
#include <QtCore/qdatastream.h>
#include <QtCore/qmath.h>
#include <QtCore/qvariant.h>
#include <QtCore/qdebug.h>
#include <iostream>

QT_BEGIN_NAMESPACE

#ifndef QT_NO_VECTOR3D

/*!
    \class Vector3D
    \brief The Vector3D class represents a vector or vertex in 3D space.
    \since 4.6
    \ingroup painting-3D
    \inmodule QtGui

    Vectors are one of the main building blocks of 3D representation and
    drawing.  They consist of three coordinates, traditionally called
    x, y, and z.

    The Vector3D class can also be used to represent vertices in 3D space.
    We therefore do not need to provide a separate vertex class.

    \sa QVector2D, QVector4D, QQuaternion
*/

/*!
    \fn Vector3D::Vector3D()

    Constructs a null vector, i.e. with coordinates (0, 0, 0).
*/

/*!
    \fn Vector3D::Vector3D(double xpos, double ypos, double zpos)

    Constructs a vector with coordinates (\a xpos, \a ypos, \a zpos).
*/

/*!
    \fn Vector3D::Vector3D(const QPoint& point)

    Constructs a vector with x and y coordinates from a 2D \a point, and a
    z coordinate of 0.
*/

/*!
    \fn Vector3D::Vector3D(const QPointF& point)

    Constructs a vector with x and y coordinates from a 2D \a point, and a
    z coordinate of 0.
*/

#ifndef QT_NO_VECTOR2D

/*!
    Constructs a 3D vector from the specified 2D \a vector.  The z
    coordinate is set to zero.

    \sa toVector2D()
*/
//Vector3D::Vector3D(const QVector2D& vector)
//{
//    xp = vector.xp;
//    yp = vector.yp;
//    zp = 0.0f;
//}

/*!
    Constructs a 3D vector from the specified 2D \a vector.  The z
    coordinate is set to \a zpos.

    \sa toVector2D()
*/
//Vector3D::Vector3D(const QVector2D& vector, double zpos)
//{
//    xp = vector.xp;
//    yp = vector.yp;
//    zp = zpos;
//}

#endif

#ifndef QT_NO_VECTOR4D

/*!
    Constructs a 3D vector from the specified 4D \a vector.  The w
    coordinate is dropped.

    \sa toVector4D()
*/
//Vector3D::Vector3D(const QVector4D& vector)
//{
//    xp = vector.xp;
//    yp = vector.yp;
//    zp = vector.zp;
//}

#endif

/*!
    \fn bool Vector3D::isNull() const

    Returns \c true if the x, y, and z coordinates are set to 0.0,
    otherwise returns \c false.
*/

/*!
    \fn double Vector3D::x() const

    Returns the x coordinate of this point.

    \sa setX(), y(), z()
*/

/*!
    \fn double Vector3D::y() const

    Returns the y coordinate of this point.

    \sa setY(), x(), z()
*/

/*!
    \fn double Vector3D::z() const

    Returns the z coordinate of this point.

    \sa setZ(), x(), y()
*/

/*!
    \fn void Vector3D::setX(double x)

    Sets the x coordinate of this point to the given \a x coordinate.

    \sa x(), setY(), setZ()
*/

/*!
    \fn void Vector3D::setY(double y)

    Sets the y coordinate of this point to the given \a y coordinate.

    \sa y(), setX(), setZ()
*/

/*!
    \fn void Vector3D::setZ(double z)

    Sets the z coordinate of this point to the given \a z coordinate.

    \sa z(), setX(), setY()
*/

/*! \fn double &Vector3D::operator[](int i)
    \since 5.2

    Returns the component of the vector at index position \a i
    as a modifiable reference.

    \a i must be a valid index position in the vector (i.e., 0 <= \a i
    < 3).
*/

/*! \fn double Vector3D::operator[](int i) const
    \since 5.2

    Returns the component of the vector at index position \a i.

    \a i must be a valid index position in the vector (i.e., 0 <= \a i
    < 3).
*/

/*!
    Returns the normalized unit vector form of this vector.

    If this vector is null, then a null vector is returned.  If the length
    of the vector is very close to 1, then the vector will be returned as-is.
    Otherwise the normalized form of the vector of length 1 will be returned.

    \sa length(), normalize()
*/
Vector3D Vector3D::normalized() const
{
    // Need some extra precision if the length is very small.
    double len = double(xp) * double(xp) +
                 double(yp) * double(yp) +
                 double(zp) * double(zp);
    if (qFuzzyIsNull(len - 1.0f))
    {
        return *this;
    } else if (!qFuzzyIsNull(len))
    {
        double sqrtLen = sqrt(len);
        return Vector3D(double(double(xp) / sqrtLen),
                         double(double(yp) / sqrtLen),
                         double(double(zp) / sqrtLen));
    }
    else
    {
        return Vector3D();
    }
}

/*!
    Normalizes the currect vector in place.  Nothing happens if this
    vector is a null vector or the length of the vector is very close to 1.

    \sa length(), normalized()
*/
void Vector3D::normalize()
{
    // Need some extra precision if the length is very small.
    double len = double(xp) * double(xp) +
                 double(yp) * double(yp) +
                 double(zp) * double(zp);
    if (qFuzzyIsNull(len - 1.0f) || qFuzzyIsNull(len))
        return;

    len = sqrt(len);

    xp = double(double(xp) / len);
    yp = double(double(yp) / len);
    zp = double(double(zp) / len);
}

/*!
    \fn Vector3D &Vector3D::operator+=(const Vector3D &vector)

    Adds the given \a vector to this vector and returns a reference to
    this vector.

    \sa operator-=()
*/

/*!
    \fn Vector3D &Vector3D::operator-=(const Vector3D &vector)

    Subtracts the given \a vector from this vector and returns a reference to
    this vector.

    \sa operator+=()
*/

/*!
    \fn Vector3D &Vector3D::operator*=(double factor)

    Multiplies this vector's coordinates by the given \a factor, and
    returns a reference to this vector.

    \sa operator/=()
*/

/*!
    \fn Vector3D &Vector3D::operator*=(const Vector3D& vector)
    \overload

    Multiplies the components of this vector by the corresponding
    components in \a vector.

    Note: this is not the same as the crossProduct() of this
    vector and \a vector.

    \sa crossProduct()
*/

/*!
    \fn Vector3D &Vector3D::operator/=(double divisor)

    Divides this vector's coordinates by the given \a divisor, and
    returns a reference to this vector.

    \sa operator*=()
*/

/*!
    Returns the dot product of \a v1 and \a v2.
*/
double Vector3D::dotProduct(const Vector3D& v1, const Vector3D& v2)
{
    return v1.xp * v2.xp + v1.yp * v2.yp + v1.zp * v2.zp;
}

/*!
    Returns the cross-product of vectors \a v1 and \a v2, which corresponds
    to the normal vector of a plane defined by \a v1 and \a v2.

    \sa normal()
*/
Vector3D Vector3D::crossProduct(const Vector3D& v1, const Vector3D& v2)
{
    return Vector3D(v1.yp * v2.zp - v1.zp * v2.yp,
                     v1.zp * v2.xp - v1.xp * v2.zp,
                     v1.xp * v2.yp - v1.yp * v2.xp);
}

Vector3D Vector3D::crossProduct(const Vector3D& v2)
{
    return Vector3D(this->yp * v2.zp - this->zp * v2.yp,
                     this->zp * v2.xp - this->xp * v2.zp,
                     this->xp * v2.yp - this->yp * v2.xp);
}

/*!
    Returns the normal vector of a plane defined by vectors \a v1 and \a v2,
    normalized to be a unit vector.

    Use crossProduct() to compute the cross-product of \a v1 and \a v2 if you
    do not need the result to be normalized to a unit vector.

    \sa crossProduct(), distanceToPlane()
*/
Vector3D Vector3D::normal(const Vector3D& v1, const Vector3D& v2)
{
    return crossProduct(v1, v2).normalized();
}

/*!
    \overload

    Returns the normal vector of a plane defined by vectors
    \a v2 - \a v1 and \a v3 - \a v1, normalized to be a unit vector.

    Use crossProduct() to compute the cross-product of \a v2 - \a v1 and
    \a v3 - \a v1 if you do not need the result to be normalized to a
    unit vector.

    \sa crossProduct(), distanceToPlane()
*/
Vector3D Vector3D::normal
        (const Vector3D& v1, const Vector3D& v2, const Vector3D& v3)
{
    return crossProduct((v2 - v1), (v3 - v1)).normalized();
}

/*!
    \since 5.1

    Returns the distance from this vertex to a point defined by
    the vertex \a point.

    \sa distanceToPlane(), distanceToLine()
*/
double Vector3D::distanceToPoint(const Vector3D& point) const
{
    return (*this - point).length();
}

/*!
    Returns the distance from this vertex to a plane defined by
    the vertex \a plane and a \a normal unit vector.  The \a normal
    parameter is assumed to have been normalized to a unit vector.

    The return value will be negative if the vertex is below the plane,
    or zero if it is on the plane.

    \sa normal(), distanceToLine()
*/
double Vector3D::distanceToPlane
        (const Vector3D& plane, const Vector3D& normal) const
{
    return dotProduct(*this - plane, normal);
}

/*!
    \overload

    Returns the distance from this vertex a plane defined by
    the vertices \a plane1, \a plane2 and \a plane3.

    The return value will be negative if the vertex is below the plane,
    or zero if it is on the plane.

    The two vectors that define the plane are \a plane2 - \a plane1
    and \a plane3 - \a plane1.

    \sa normal(), distanceToLine()
*/
double Vector3D::distanceToPlane
    (const Vector3D& plane1, const Vector3D& plane2, const Vector3D& plane3) const
{
    Vector3D n = normal(plane2 - plane1, plane3 - plane1);
    return dotProduct(*this - plane1, n);
}

/*!
    Returns the distance that this vertex is from a line defined
    by \a point and the unit vector \a direction.

    If \a direction is a null vector, then it does not define a line.
    In that case, the distance from \a point to this vertex is returned.

    \sa distanceToPlane()
*/
double Vector3D::distanceToLine
        (const Vector3D& point, const Vector3D& direction) const
{
    if (direction.isNull())
        return (*this - point).length();
    Vector3D p = point + dotProduct(*this - point, direction) * direction;
    return (*this - p).length();
}

/*!
    \fn bool operator==(const Vector3D &v1, const Vector3D &v2)
    \relates Vector3D

    Returns \c true if \a v1 is equal to \a v2; otherwise returns \c false.
    This operator uses an exact doubleing-point comparison.
*/

/*!
    \fn bool operator!=(const Vector3D &v1, const Vector3D &v2)
    \relates Vector3D

    Returns \c true if \a v1 is not equal to \a v2; otherwise returns \c false.
    This operator uses an exact doubleing-point comparison.
*/

/*!
    \fn const Vector3D operator+(const Vector3D &v1, const Vector3D &v2)
    \relates Vector3D

    Returns a Vector3D object that is the sum of the given vectors, \a v1
    and \a v2; each component is added separately.

    \sa Vector3D::operator+=()
*/

/*!
    \fn const Vector3D operator-(const Vector3D &v1, const Vector3D &v2)
    \relates Vector3D

    Returns a Vector3D object that is formed by subtracting \a v2 from \a v1;
    each component is subtracted separately.

    \sa Vector3D::operator-=()
*/

/*!
    \fn const Vector3D operator*(double factor, const Vector3D &vector)
    \relates Vector3D

    Returns a copy of the given \a vector,  multiplied by the given \a factor.

    \sa Vector3D::operator*=()
*/

/*!
    \fn const Vector3D operator*(const Vector3D &vector, double factor)
    \relates Vector3D

    Returns a copy of the given \a vector,  multiplied by the given \a factor.

    \sa Vector3D::operator*=()
*/

/*!
    \fn const Vector3D operator*(const Vector3D &v1, const Vector3D& v2)
    \relates Vector3D

    Multiplies the components of \a v1 by the corresponding components in \a v2.

    Note: this is not the same as the crossProduct() of \a v1 and \a v2.

    \sa Vector3D::crossProduct()
*/

/*!
    \fn const Vector3D operator-(const Vector3D &vector)
    \relates Vector3D
    \overload

    Returns a Vector3D object that is formed by changing the sign of
    all three components of the given \a vector.

    Equivalent to \c {Vector3D(0,0,0) - vector}.
*/

/*!
    \fn const Vector3D operator/(const Vector3D &vector, double divisor)
    \relates Vector3D

    Returns the Vector3D object formed by dividing all three components of
    the given \a vector by the given \a divisor.

    \sa Vector3D::operator/=()
*/

/*!
    \fn bool qFuzzyCompare(const Vector3D& v1, const Vector3D& v2)
    \relates Vector3D

    Returns \c true if \a v1 and \a v2 are equal, allowing for a small
    fuzziness factor for doubleing-point comparisons; false otherwise.
*/

#ifndef QT_NO_VECTOR2D

/*!
    Returns the 2D vector form of this 3D vector, dropping the z coordinate.

    \sa toVector4D(), toPoint()
*/
QVector2D Vector3D::toVector2D() const
{
    return QVector2D(xp, yp);
}

#endif

#ifndef QT_NO_VECTOR4D

/*!
    Returns the 4D form of this 3D vector, with the w coordinate set to zero.

    \sa toVector2D(), toPoint()
*/
QVector4D Vector3D::toVector4D() const
{
    return QVector4D(xp, yp, zp, 0.0f);
}

#endif

/*!
    \fn QPoint Vector3D::toPoint() const

    Returns the QPoint form of this 3D vector. The z coordinate
    is dropped.

    \sa toPointF(), toVector2D()
*/

/*!
    \fn QPointF Vector3D::toPointF() const

    Returns the QPointF form of this 3D vector. The z coordinate
    is dropped.

    \sa toPoint(), toVector2D()
*/

/*!
    Returns the 3D vector as a QVariant.
*/
Vector3D::operator QVariant() const
{
    return QVariant(QVariant::Vector3D, this);
}

//现在实现的方式是 Matrix * Vector3D，用于缩放旋转平移
Vector3D Vector3D::operator*( const QMatrix4x4& matrix)
{
    double _x = this->x() * matrix(0,0) + this->y() * matrix(0,1) + this->z() * matrix(0,2) + matrix(0,3);
    double _y = this->x() * matrix(1,0) + this->y() * matrix(1,1) + this->z() * matrix(1,2) + matrix(1,3);
    double _z = this->x() * matrix(2,0) + this->y() * matrix(2,1) + this->z() * matrix(2,2) + matrix(2,3);

//    double _x = this->x() * matrix.row(0).x() + this->y() * matrix.row(0).y() + this->z() * matrix.row(0).z() + matrix.row(0).w();
//    double _y = this->x() * matrix.row(1).x() + this->y() * matrix.row(1).y() + this->z() * matrix.row(1).z() + matrix.row(1).w();
//    double _z = this->x() * matrix.row(2).x() + this->y() * matrix.row(2).y() + this->z() * matrix.row(2).z() + matrix.row(2).w();

//    QVector3D _vec(this->x(), this->y(), this->z());
//    _vec = matrix * _vec;

//    double _x = _vec.x();
//    double _y = _vec.y();
//    double _z = _vec.z();

    this->setX(_x);
    this->setY(_y);
    this->setZ(_z);

    return *this;
}

const Vector3D rotate(const double &angle,
                      const double &x,
                      const double &y,
                      const double &z)
{
//    (cos(angle)+(1-cos(angle))*pow(x,2))*this->x() +
//            (1-cos(angle)*y*z + (sin(angle)*z))*this->y() +
//            (1-cos(angle)*z*x - sin(angle)*y)*this->z();

    return Vector3D(0, 0, 0);
}

const Vector3D rotate(const double &angle,
                      const Vector3D & axis)
{
    return Vector3D(0, 0, 0);
}


/*!
    Returns the length of the vector from the origin.

    \sa lengthSquared(), normalized()
*/
double Vector3D::length() const
{
    // Need some extra precision if the length is very small.
    double len = double(xp) * double(xp) +
                 double(yp) * double(yp) +
                 double(zp) * double(zp);
    return double(sqrt(len));
}

/*!
    Returns the squared length of the vector from the origin.
    This is equivalent to the dot product of the vector with itself.

    \sa length(), dotProduct()
*/
double Vector3D::lengthSquared() const
{
    return xp * xp + yp * yp + zp * zp;
}

#ifndef QT_NO_DEBUG_STREAM

QDebug operator<<(QDebug dbg, const Vector3D &vector)
{
    dbg.nospace() << "Vector3D("
        << vector.x() << ", " << vector.y() << ", " << vector.z() << ')';
    return dbg.space();
}

#endif

#ifndef QT_NO_DATASTREAM

/*!
    \fn QDataStream &operator<<(QDataStream &stream, const Vector3D &vector)
    \relates Vector3D

    Writes the given \a vector to the given \a stream and returns a
    reference to the stream.

    \sa {Serializing Qt Data Types}
*/

QDataStream &operator<<(QDataStream &stream, const Vector3D &vector)
{
    stream << vector.x() << vector.y() << vector.z();
    return stream;
}

/*!
    \fn QDataStream &operator>>(QDataStream &stream, Vector3D &vector)
    \relates Vector3D

    Reads a 3D vector from the given \a stream into the given \a vector
    and returns a reference to the stream.

    \sa {Serializing Qt Data Types}
*/

QDataStream &operator>>(QDataStream &stream, Vector3D &vector)
{
    double x, y, z;
    stream >> x;
    stream >> y;
    stream >> z;
    vector.setX(x);
    vector.setY(y);
    vector.setZ(z);
    return stream;
}

#endif // QT_NO_DATASTREAM

#endif // QT_NO_VECTOR3D

QT_END_NAMESPACE
