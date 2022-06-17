#ifndef STLANALYSIS_H
#define STLANALYSIS_H

#include "AnalysisFile.h"

class STLFile : public AnalysisFile
{
    Q_OBJECT
public:
    explicit STLFile(QObject *parent = nullptr);

public slots:
    virtual bool ReadFile(const QString &FilePath_) override;
};

#endif // STLANALYSIS_H
