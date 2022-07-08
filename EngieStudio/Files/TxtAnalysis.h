#ifndef TXTANALYSIS_H
#define TXTANALYSIS_H

#include "AnalysisFile.h"

class ColorGenerator;

class TxtFile : public AnalysisFile
{
public:
    explicit TxtFile(QObject* parent = nullptr);
    virtual ~TxtFile() override;

public:

protected:

private:
    void updatePointColor();
    void updateColor();

public:

protected:

private:
    ColorGenerator* m_pColorGenerator;
    QMap<uint, float> m_pointIDValueMap;

public slots:
    bool ReadFile(const QString &FilePath_) override;
};

#endif // TXTANALYSIS_H
