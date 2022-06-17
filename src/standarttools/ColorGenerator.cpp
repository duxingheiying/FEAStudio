#include "ColorGenerator.h"
#include <QDebug>

ColorGenerator::ColorGenerator(const float& max_,
                               const float& min_,
                               QVector<QVector3D>& colorVector_,
                               QObject *parent) :
    QObject(parent)
{
    if ( max_ > min_ ) {
        m_fMaxValue = max_;
        m_fMinValue = min_;
    } else if ( max_ > min_ ) {
        m_fMaxValue = min_;
        m_fMinValue = max_;
    } else {
        m_fMaxValue = max_+1;
        m_fMinValue = min_;
    }
    if ( colorVector_.size() > 0 ) {
        m_vecColorList.swap( colorVector_ );
    } else {
        m_vecColorList.push_back( QVector3D(1.0f, 1.0f, 1.0f) );
    }

    calculatePreData();
}

bool ColorGenerator::setMaxValue(const float& max_)
{
    if ( max_ > m_fMinValue ) {
        m_fMaxValue = max_;
        calculatePreData();
        return true;
    } else {
        return false;
    }
}

bool ColorGenerator::setMinValue(const float& min_)
{
    if ( min_ < m_fMaxValue ) {
        m_fMinValue = min_;
        calculatePreData();
        return true;
    } else {
        return false;
    }
}

// this function must judgement the value which is bigger
bool ColorGenerator::setMinMaxValue(const float& min_, const float& max_)
{
    if ( min_ < max_ ) {
        m_fMaxValue = max_;
        m_fMinValue = min_;
    } else if ( min_ > max_ ) {
        m_fMaxValue = min_;
        m_fMinValue = max_;
    } else {
        m_fMaxValue = max_ + 1;
        m_fMinValue = min_;
    }
    calculatePreData();
    return true;
}

bool ColorGenerator::setColorVector(QVector<QVector3D>& colorVector_)
{
    if ( colorVector_.size() > 0 ) {
        m_vecColorList.swap(colorVector_);
        calculatePreData();
        return true;
    } else {
        return false;
    }
}

void ColorGenerator::calculatePreData()
{
    m_fStep = (m_fMaxValue - m_fMinValue) / m_vecColorList.size();
}

// this function design by the vector add by principle
const QVector3D ColorGenerator::generatorColor(const float& value_) const
{
    QVector3D _color;
    if ( value_ > m_fMaxValue ) {  // the value over the maxvalue
        qDebug()<<tr("the value is bigger than the max value");
        qDebug()<<value_<<"   "<<m_fMaxValue;
        _color = QVector3D(1.0, 1.0, 1.0);
    } else if ( value_ < m_fMinValue ) { // the value lower the minvalue
        qDebug()<<tr("the value is smaller than the min value");
        _color = QVector3D(0.0, 0.0, 0.0);
    } else { // calculate the color stand how many proportion
        int _position = (value_ - m_fMinValue)/m_fStep;  // calculate the value in which scale position
        if ( _position >= m_vecColorList.size() - 1) {  // forbide over fload
            _position = m_vecColorList.size() - 1;
            _color = m_vecColorList.at(_position);
        } else if ( _position <= 0 ) {
            _position = 0;
            _color = m_vecColorList.at(_position);
        } else {
            float _lowScale = ( value_ - m_fMinValue - m_fStep * _position ) / m_fStep;
            float _upScale = 1 - _lowScale;
            _color = _lowScale * m_vecColorList.at(_position) + _upScale * m_vecColorList.at(_position+1);
//            qDebug()<<m_fMinValue<<"  "<<m_fMaxValue<<"  "<<value_<<"  "<<_position<<"  "<< _lowScale<<"  "<<_color;
        }
//        _color = m_vecColorList.at(_position);
    }
    return _color;
}

ColorGenerator::~ColorGenerator()
{
}
