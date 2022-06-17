#ifndef QUADRANGLE_H
#define QUADRANGLE_H

#include <QHash>

#include "Object.h"

class TRIANGLE;

class Quadrangle : public EntityObject
{
public:
    explicit Quadrangle(const uint& quadID_,
                        const uint& materialID_,
                        const QStringList& stringList_,
                        const float& red_,
                        const float& green_,
                        const float& blue_);
    ~Quadrangle() override;

public:
    virtual void Show() override;
    void getAllShow(QHash<QString, TRIANGLE *> &triangleHash_, QHash<QString, QUAD *> &quadHash_) override;

protected:
    void calculateIDName();

private:

public:
    QString m_sjudgeMentName; // it's used for judge the unit is exist

protected:


private:
    void getTriangleShow(const QString& firstPointID_, const QString& secondPointID_, const QString& thirdPointID_,
                         const float &red_, const float &green_, const float &blue_,  QHash<QString, TRIANGLE*>& triangleHash_) override;

    void getQuadrangleShow(const QString& firstPointID_, const QString& secondPointID_, const QString& thirdPointID_, const QString& fourthPointID_,
                           const float &red_, const float &green_, const float &blue_, QHash<QString, QUAD*>& quadHash_) override;

};

#endif // QUADRANGLE_H
