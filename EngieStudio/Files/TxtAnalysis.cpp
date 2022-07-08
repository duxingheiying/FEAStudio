#include "TxtAnalysis.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <math.h>
#include <QTime>

#include "Point.h"
#include "Line.h"
#include "Triangle.h"
#include "Quadrangle.h"
#include "Tetrahedron.h"
#include "Pyramid.h"
#include "TriangularPrism.h"
#include "Hexahedron.h"
#include "ColorGenerator.h"

TxtFile::TxtFile(QObject *parent) :
    AnalysisFile(parent)
{
    QVector<QVector3D> _colorVector;
    _colorVector.push_back( QVector3D(   0,   0, 255 ) / 255 );
    _colorVector.push_back( QVector3D(   0, 178, 255 ) / 255 );
    _colorVector.push_back( QVector3D(   0, 255, 255 ) / 255 );
    _colorVector.push_back( QVector3D(   0, 255, 178 ) / 255 );
    _colorVector.push_back( QVector3D(   0, 255,   0 ) / 255 );
    _colorVector.push_back( QVector3D( 178, 255,   0 ) / 255 );
    _colorVector.push_back( QVector3D( 255, 255,   0 ) / 255 );
    _colorVector.push_back( QVector3D( 255, 178,   0 ) / 255 );
    _colorVector.push_back( QVector3D( 255,   0,   0 ) / 255 );

    m_pColorGenerator = new ColorGenerator( 1.0f, 0.0f, _colorVector);
}

TxtFile::~TxtFile()
{
}

bool TxtFile::ReadFile(const QString &FilePath_)
{
    if ( FilePath_.isEmpty() ) {
        return false;
    }
    QFile _file(FilePath_);
    if ( !_file.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        return false;
    }

    m_pointIDValueMap.clear();
    m_vCenter.setX(0);
    m_vCenter.setY(0);
    m_vCenter.setZ(0);

    uint _triangleID = 1;
    uint _QuadrangleID = 1;
    float _maxX = 0;
    float _maxY = 0;
    float _maxZ = 0;
    float _minX = 0;
    float _minY = 0;
    float _minZ = 0;

    QMap<uint, uint> _indexMap;  // first is point id the second is position
    uint _count = 0;
    uint _set = 0;
    QColor _setColor = QColor(0, 76, 228);
    float _red = 0.0f;
    float _greed = 0.298f;
    float _blue = 0.894f;

    float _maxValue = 0;
    float _minValue = 0;

    QTextStream _in(&_file);

    QTime _time;
    _time.restart();

    while(!_in.atEnd()) {
        QString _line = _in.readLine();
        QStringList _stringList = _line.split(",");
        if ( _line.startsWith("Point") ) {
            if ( _stringList.size() >= 6 ) {
                uint _pointID = _stringList.at(1).toUInt();
                float _x = _stringList.at(2).toFloat();
                float _y = _stringList.at(3).toFloat();
                float _z = _stringList.at(4).toFloat();
                float _value = _stringList.at(5).toFloat();

                if (_count == 0) {
                    _minX = _maxX = _x;
                    _minY = _maxY = _y;
                    _minZ = _maxZ = _z;

                    _maxValue = _minValue = _value;
                } else {
                    _maxX = _maxX > _x ? _maxX : _x;
                    _maxY = _maxY > _y ? _maxY : _y;
                    _maxZ = _maxZ > _z ? _maxZ : _z;
                    _minX = _minX < _x ? _minX : _x;
                    _minY = _minY < _y ? _minY : _y;
                    _minZ = _minZ < _z ? _minZ : _z;

                    _maxValue = _maxValue > _value ? _maxValue : _value;  // get the max value
                    _minValue = _minValue < _value ? _minValue : _value;  // get the min value
                }

                Point* _point = new Point(_x, _y, _z, _pointID);
                m_allPointMap[_pointID] = _point;

                m_pointIDValueMap[_pointID] = _value;
                CreatePoint(_x, _y, _z, _pointID, _indexMap, _count);
                _count++;
                continue;
            } else {
                continue;
            }
        }  else if ( _line.startsWith("Triangle") ) {
            if ( _stringList.size() >= 4 ) {
                QStringList _idList;
                for (int _i = 1; _i <= 3; _i++) {
                    _idList<<_stringList.at(_i);
                }
                Triangle*_triangle = new Triangle(_triangleID,
                                                  1,
                                                  _idList,
                                                  _red,
                                                  _greed,
                                                  _blue);
                m_allTrianglesMap.insert(_triangleID, _triangle);
                _triangleID++;
                continue;
            } else {
                continue;
            }
        } else if ( _line.startsWith("Quadrangle") ) {
            if ( _stringList.size() >= 5 ) {
                QStringList _idList;
                for ( int _i = 1; _i <=4; _i++ ) {
                    _idList<<_stringList.at(_i);
                }
                // create Quadrangle
                Quadrangle*_quadrangle = new Quadrangle(_QuadrangleID,
                                                        1,
                                                        _idList,
                                                        _red,
                                                        _greed,
                                                        _blue);
                m_allQuadMap.insert(_QuadrangleID, _quadrangle);
                _QuadrangleID++;
                continue;
            } else {
                continue;
            }
        } else {
            qDebug()<<tr("this graphic has not analysis!");
        }
    }
    _file.close();

    qDebug()<<tr("**************************************************************");
    qDebug()<<tr("********************Analysis TxtFiles*************************");
    qDebug()<<tr("          Point Number:")<<m_allPointMap.size();
    qDebug()<<tr("           Line Number:")<<m_allLinesMap.size();
    qDebug()<<tr("       Triangle Number:")<<m_allTrianglesMap.size();
    qDebug()<<tr("     Quadrangle Number:")<<m_allQuadMap.size();
    qDebug()<<tr("    Tetrahedron Number:")<<m_allTetrahedronMap.size();
    qDebug()<<tr("     Hexahedron Number:")<<m_allHexahedronMap.size();
    qDebug()<<tr("TriangularPrism Number:")<<m_allTriangularPrismMap.size();
    qDebug()<<tr("  m_allSetColor Number:")<<m_allSetColor.size();
    qDebug()<<tr("     read file elapsed:")<<_time.elapsed();
    qDebug()<<tr("**************************************************************")<<'\n'<<'\n';

    m_vCenter.setX( ( _maxX + _minX ) / 2 );
    m_vCenter.setY( ( _maxY + _minY ) / 2 );
    m_vCenter.setZ( ( _maxZ + _minZ ) / 2 );

    m_fRange = static_cast<float>(sqrt(pow(static_cast<double>(_maxX) - static_cast<double>(_minX), 2.0)+
                                       pow(static_cast<double>(_maxY) - static_cast<double>(_minY), 2.0)+
                                       pow(static_cast<double>(_maxZ) - static_cast<double>(_minZ), 2.0)));

    m_pColorGenerator->setMinMaxValue(_minValue, _maxValue);

    qDebug()<<tr("**************************************************************");
    qDebug()<<tr("********************Analysis BDFFiles*************************");
    qDebug()<<tr("m_vCenter :")<<m_vCenter;
    qDebug()<<tr(" m_fRange :")<<m_fRange;
    qDebug()<<tr("**************************************************************")<<'\n'<<'\n';

    calculatShow();
    updatePointColor();
    emit ReadFileFinished();

    return true;
}

void TxtFile::updatePointColor()
{
    QMap<uint, Point*>::iterator _point_itor = m_allPointMap.begin();
    while ( _point_itor != m_allPointMap.end() ) {

        QMap<uint, float>::iterator _valueItor = m_pointIDValueMap.find(_point_itor.key());
        if ( _valueItor == m_pointIDValueMap.end() ) {
            continue;
        }
        const QVector3D _color = m_pColorGenerator->generatorColor(_valueItor.value());
        int _colorsize = _point_itor.value()->m_aPColorList.size();
        for (int _i = 0; _i < _colorsize; _i++ ) {
            switch ( _i % 3 ) {
            case 0:
                (*(_point_itor.value()->m_aPColorList.at(_i))) = _color.x();
                break;
            case 1:
                (*(_point_itor.value()->m_aPColorList.at(_i))) = _color.y();
                break;
            case 2:
                (*(_point_itor.value()->m_aPColorList.at(_i))) = _color.z();
                break;
            default:
                break;
            }
        }
        _point_itor++;
    }
}

void TxtFile::updateColor()
{
}
