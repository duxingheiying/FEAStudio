#ifndef BDFANALYSIS_H
#define BDFANALYSIS_H

#include "AnalysisFile.h"


class BDFFile : public AnalysisFile
{
public:
    explicit BDFFile(AnalysisFile* parent = nullptr);
    virtual ~BDFFile() override;

public:

protected:

private:

public:

protected:

private:

signals:

public slots:
    virtual bool ReadFile(const QString &FilePath) override;
};

#endif // BDFANALYSIS_H
