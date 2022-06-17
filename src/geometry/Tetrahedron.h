#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include "Object.h"

class Tetrahedron : public EntityObject
{
public:
    explicit Tetrahedron(const uint& unitID_, const uint& materialID_, const QStringList& pointidList_,
                         const float& red_, const float& green_, const float& blue_);
    ~Tetrahedron() override;

public:
    void Show() override {}
    void getAllShow(QHash<QString, TRIANGLE *> &triangleHash_, QHash<QString, QUAD *> &quadHash_) override;

protected:

private:

public:

protected:

private:

};

#endif // TETRAHEDRON_H
