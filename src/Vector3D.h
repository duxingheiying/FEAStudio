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

#ifndef Vector3D_H
#define Vector3D_H

#include <QtCore/qpoint.h>
#include <QtCore/qmetatype.h>

#include <QMatrix4x4>

QT_BEGIN_NAMESPACE

class QMatrix4x4;
class QVector2D;
class QVector4D;
class QVector3D;

#ifndef QT_NO_VECTOR3D

class Vector3D
{
public:
    Vector3D();
    Vector3D(double xpos, double ypos, double zpos) : xp(xpos), yp(ypos), zp(zpos) {}

    explicit Vector3D(const QPoint& point);
    explicit Vector3D(const QPointF& point);
    #ifndef QT_NO_VECTOR2D
        Vector3D(const QVector2D& vector);
        Vector3D(const QVector2D& vector, double zpos);
    #endif
    #ifndef QT_NO_VECTOR4D
        explicit Vector3D(const QVector4D& vector);
    #endif

    bool isNull() const;

    double x() const;
    double y() const;
    double z() const;

    void setX(double x);
    void setY(double y);
    void setZ(double z);

    double &operator[](int i);
    double operator[](int i) const;

    double length() const;
    double lengthSquared() const;

    Vector3D normalized() const;
    void normalize();

    Vector3D &operator+=(const Vector3D &vector);
    Vector3D &operator-=(const Vector3D &vector);
    Vector3D &operator*=(double factor);
    Vector3D &operator*=(const Vector3D& vector);
    Vector3D &operator/=(double divisor);
    Vector3D &operator=(const Vector3D& vector);

    static double dotProduct(const Vector3D& v1, const Vector3D& v2); //In Qt 6 convert to inline and constexpr
    static Vector3D crossProduct(const Vector3D& v1, const Vector3D& v2); //in Qt 6 convert to inline and constexpr
    Vector3D crossProduct(const Vector3D& v1); //in Qt 6 convert to inline and constexpr

    static Vector3D normal(const Vector3D& v1, const Vector3D& v2);
    static Vector3D normal
    (const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);

    double distanceToPoint(const Vector3D& point) const;
    double distanceToPlane(const Vector3D& plane, const Vector3D& normal) const;
    double distanceToPlane(const Vector3D& plane1, const Vector3D& plane2, const Vector3D& plane3) const;
    double distanceToLine(const Vector3D& point, const Vector3D& direction) const;

    friend inline bool operator==(const Vector3D &v1, const Vector3D &v2);
    friend inline bool operator!=(const Vector3D &v1, const Vector3D &v2);
    friend inline const Vector3D operator+(const Vector3D &v1, const Vector3D &v2);
    friend inline const Vector3D operator-(const Vector3D &v1, const Vector3D &v2);
    friend inline const Vector3D operator*(double factor, const Vector3D &vector);
    friend inline const Vector3D operator*(const Vector3D &vector, double factor);
    friend const Vector3D operator*(const Vector3D &v1, const Vector3D& v2);
    friend inline const Vector3D operator-(const Vector3D &vector);
    friend inline const Vector3D operator/(const Vector3D &vector, double divisor);

    inline const Vector3D rotate(const double &angle, const double &x, const double &y, const double &z);
    inline const Vector3D rotate(const double &angle, const Vector3D & axis);

    friend inline bool qFuzzyCompare(const Vector3D& v1, const Vector3D& v2);

#ifndef QT_NO_VECTOR2D
    QVector2D toVector2D() const;
#endif
#ifndef QT_NO_VECTOR4D
    QVector4D toVector4D() const;
#endif

    QPoint toPoint() const;
    QPointF toPointF() const;

    operator QVariant() const;

    double xp, yp, zp;

    friend class QVector2D;
    friend class QVector4D;
#ifndef QT_NO_MATRIX4X4
    Vector3D operator*(const QMatrix4x4& matrix);
    friend Vector3D operator*(const QMatrix4x4& matrix, const Vector3D& vector);
#endif
};

Q_DECLARE_TYPEINFO(Vector3D, Q_MOVABLE_TYPE);

inline Vector3D::Vector3D() : xp(0.0f), yp(0.0f), zp(0.0f) {}

inline Vector3D::Vector3D(const QPoint& point) : xp(point.x()), yp(point.y()), zp(0.0f) {}

inline Vector3D::Vector3D(const QPointF& point) : xp(point.x()), yp(point.y()), zp(0.0f) {}

inline bool Vector3D::isNull() const
{
    return qIsNull(xp) && qIsNull(yp) && qIsNull(zp);
}

inline double Vector3D::x() const { return xp; }
inline double Vector3D::y() const { return yp; }
inline double Vector3D::z() const { return zp; }

inline void Vector3D::setX(double aX) { xp = aX; }
inline void Vector3D::setY(double aY) { yp = aY; }
inline void Vector3D::setZ(double aZ) { zp = aZ; }

inline double &Vector3D::operator[](int i)
{
    Q_ASSERT(uint(i) < 3u);
    return *(&xp + i);
}

inline double Vector3D::operator[](int i) const
{
    Q_ASSERT(uint(i) < 3u);
    return *(&xp + i);
}

inline Vector3D &Vector3D::operator+=(const Vector3D &vector)
{
    xp += vector.xp;
    yp += vector.yp;
    zp += vector.zp;
    return *this;
}

inline Vector3D &Vector3D::operator-=(const Vector3D &vector)
{
    xp -= vector.xp;
    yp -= vector.yp;
    zp -= vector.zp;
    return *this;
}

inline Vector3D &Vector3D::operator*=(double factor)
{
    xp *= factor;
    yp *= factor;
    zp *= factor;
    return *this;
}

inline Vector3D &Vector3D::operator*=(const Vector3D& vector)
{
    xp *= vector.xp;
    yp *= vector.yp;
    zp *= vector.zp;
    return *this;
}

inline Vector3D &Vector3D::operator/=(double divisor)
{
    xp /= divisor;
    yp /= divisor;
    zp /= divisor;
    return *this;
}

inline Vector3D &Vector3D::operator=(const Vector3D& vector)
{
    xp = vector.x();
    yp = vector.y();
    zp = vector.z();
    return *this;
}

inline bool operator==(const Vector3D &v1, const Vector3D &v2)
{
    return v1.xp == v2.xp && v1.yp == v2.yp && v1.zp == v2.zp;
}

inline bool operator!=(const Vector3D &v1, const Vector3D &v2)
{
    return v1.xp != v2.xp || v1.yp != v2.yp || v1.zp != v2.zp;
}

inline const Vector3D operator+(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.xp + v2.xp, v1.yp + v2.yp, v1.zp + v2.zp);
}

inline const Vector3D operator-(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.xp - v2.xp, v1.yp - v2.yp, v1.zp - v2.zp);
}

inline const Vector3D operator*(double factor, const Vector3D &vector)
{
    return Vector3D(vector.xp * factor, vector.yp * factor, vector.zp * factor);
}

inline const Vector3D operator*(const Vector3D &vector, double factor)
{
    return Vector3D(vector.xp * factor, vector.yp * factor, vector.zp * factor);
}

inline const Vector3D operator*(const Vector3D &v1, const Vector3D& v2)
{
    return Vector3D(v1.xp * v2.xp, v1.yp * v2.yp, v1.zp * v2.zp);
}

inline const Vector3D operator-(const Vector3D &vector)
{
    return Vector3D(-vector.xp, -vector.yp, -vector.zp);
}

inline const Vector3D operator/(const Vector3D &vector, double divisor)
{
    return Vector3D(vector.xp / divisor, vector.yp / divisor, vector.zp / divisor);
}

inline bool qFuzzyCompare(const Vector3D& v1, const Vector3D& v2)
{
    return qFuzzyCompare(v1.xp, v2.xp) &&
            qFuzzyCompare(v1.yp, v2.yp) &&
            qFuzzyCompare(v1.zp, v2.zp);
}

inline QPoint Vector3D::toPoint() const
{
    return QPoint(qRound(xp), qRound(yp));
}

inline QPointF Vector3D::toPointF() const
{
    return QPointF(qreal(xp), qreal(yp));
}

#ifndef QT_NO_DEBUG_STREAM
 QDebug operator<<(QDebug dbg, const Vector3D &vector);
#endif

#ifndef QT_NO_DATASTREAM
 QDataStream &operator<<(QDataStream &, const Vector3D &);
 QDataStream &operator>>(QDataStream &, Vector3D &);
#endif

#endif

QT_END_NAMESPACE

#endif
