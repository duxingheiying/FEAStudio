#ifndef TRIANGULARPRISM_H
#define TRIANGULARPRISM_H

#include "Object.h"

class TriangularPrism : public EntityObject
{
public:
    explicit TriangularPrism(const uint& unitID_,
                             const uint& materialID_,
                             const QStringList& pointidList_,
                             const float &red_, const float &green_, const float &blue_);
    ~TriangularPrism() override;

public:
    void Show() override {}
    void getAllShow(QHash<QString, TRIANGLE *> &triangleHash_, QHash<QString, QUAD *> &quadHash_) override;

protected:

private:

public:

protected:

private:

};

#endif // TRIANGULARPRISM_H
