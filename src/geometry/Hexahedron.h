#ifndef HEXAHEDRON_H
#define HEXAHEDRON_H

#include "Object.h"

class Hexahedron : public EntityObject
{
public:
    explicit Hexahedron(const uint& unitID_ , const uint& materialID_ , const QStringList& pointidList_,
                        const float &red_, const float &green_, const float &blue);
    ~Hexahedron() override;

public:
    void Show()override { }
    void getAllShow(QHash<QString, TRIANGLE *> &triangleHash_, QHash<QString, QUAD *> &quadHash_) override;

protected:

private:

public:

protected:

private:

};

#endif // HEXAHEDRON_H
