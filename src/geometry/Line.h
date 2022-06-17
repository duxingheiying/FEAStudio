/********************************************************************************************
 * this class is for draw a line
 *
 * ******************************************************************************************/


#ifndef LINE_H
#define LINE_H

#include "Object.h"

class Line : public EntityObject
{
public:
    explicit Line(const uint& unitID_ = 0, const uint& materalID_ = 0,
                  const QStringList& pointidList_ = QStringList("0"));
    ~Line();
};

#endif // LINE_H
