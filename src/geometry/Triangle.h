#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QHash>

#include "Object.h"

class Triangle : public EntityObject
{
public:
    explicit Triangle(const uint& triangleID_ ,
                      const uint& materialID_ ,
                      const QStringList& stringlist_,
                      const float& red_,
                      const float& green_,
                      const float& blue_);
    ~Triangle() override;

public:
    virtual void Show() override;
    void getAllShow(QHash<QString, TRIANGLE *> &triangleHash_, QHash<QString, QUAD *> &quadHash_) override;

protected:

private:

public:
    QString m_sjudgeMentName; // it's used for judge the unit is exist

protected:
    void calculateIDName();

private:
    void getTriangleShow(const QString& firstPointID_, const QString& secondPointID_, const QString& thirdPointID_,
                         const float& red_, const float& green_, const float& blue_,  QHash<QString, TRIANGLE*>& triangleHash_) override;

    void getQuadrangleShow(const QString& firstPointID_, const QString& secondPointID_,
                           const QString& thirdPointID_, const QString& fourthPointID_,
                           const float& red_, const float& green_, const float& blue_, QHash<QString, QUAD*>& quadHash_) override;
};

#endif // TRIANGLE_H
