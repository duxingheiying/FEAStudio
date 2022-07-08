/********************************************************************************
 *                            color generator
 *
 * this object is used to generator color.
 * it doesn't limited by the kinds of color.
 * the user give the colors what can be set into the genertor.
 *                                                design by guweicao
 *                                                tiem : 2019-12-20
 * ******************************************************************************/

#ifndef COLORGENERATOR_H
#define COLORGENERATOR_H

#include <QObject>
#include <QVector3D>
#include <QVector>

class ColorGenerator : public QObject
{
    Q_OBJECT
public:
    explicit ColorGenerator(const float& max_,
                            const float& min_,
                            QVector<QVector3D>& colorVector_,
                            QObject *parent = nullptr);
    ~ColorGenerator();

public:
    const QVector3D generatorColor(const float& value_) const;
    bool setMaxValue(const float& max_);
    bool setMinValue(const float& min_);
    bool setMinMaxValue(const float& min_, const float& max_);
    bool setColorVector(QVector<QVector3D>& colorVector_);

protected:

private:
    void calculatePreData();

public:

protected:

private:
    float m_fMaxValue; // the max value
    float m_fMinValue; // the min value
    QVector<QVector3D> m_vecColorList;  // color value list
    float m_fStep; // the step color to color

signals:

public slots:

protected slots:

private slots:

};

#endif // COLORGENERATOR_H
