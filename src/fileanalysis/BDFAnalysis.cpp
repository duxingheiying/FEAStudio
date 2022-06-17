#include "BDFAnalysis.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtMath>
#include <QTimer>
#include <QTime>
#include <QColor>

#include <set>

#include "Point.h"
#include "Line.h"
#include "Triangle.h"
#include "Quadrangle.h"
#include "Tetrahedron.h"
#include "Pyramid.h"
#include "TriangularPrism.h"
#include "Hexahedron.h"

using namespace std;

BDFFile::BDFFile(AnalysisFile* parent)
    : AnalysisFile(parent)
{
    qDebug()<<tr("*******************************************************************");
    qDebug()<<tr(" sizeof (Point)           : ")<<sizeof (Point);
    qDebug()<<tr(" sizeof (Line)            : ")<<sizeof (Line);
    qDebug()<<tr(" sizeof (Triangle)        : ")<<sizeof (Triangle);
    qDebug()<<tr(" sizeof (Quadrangle)      : ")<<sizeof (Quadrangle);
    qDebug()<<tr(" sizeof (Tetrahedron)     : ")<<sizeof (Tetrahedron);
    qDebug()<<tr(" sizeof (Pyramid)         : ")<<sizeof (Pyramid);
    qDebug()<<tr(" sizeof (TriangularPrism) : ")<<sizeof (TriangularPrism);
    qDebug()<<tr(" sizeof (Hexahedron)      : ")<<sizeof (Hexahedron);
    qDebug()<<tr(" sizeof (TRIANGLE)        : ")<<sizeof (TRIANGLE);
    qDebug()<<tr(" sizeof (QUAD)            : ")<<sizeof (QUAD);

    qDebug()<<tr(" sizeof (string)          : ")<<sizeof (string);
    qDebug()<<tr(" sizeof (QString)         : ")<<sizeof (QString);
    qDebug()<<tr(" sizeof (uint)            : ")<<sizeof (uint);
    qDebug()<<tr(" sizeof (float)           : ")<<sizeof (float);
    qDebug()<<tr("*******************************************************************")<<'\n'<<'\n';
}

BDFFile::~BDFFile()
{
    qDebug()<<tr("Call BDFFile::~BDFFile()");
    clearAllData();
}

bool BDFFile::ReadFile(const QString &FilePath)
{
    QFile _file;
    _file.setFileName(FilePath);

    if (!_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    m_vCenter.setX(0);
    m_vCenter.setY(0);
    m_vCenter.setZ(0);

    float _maxX = 0;
    float _maxY = 0;
    float _maxZ = 0;
    float _minX = 0;
    float _minY = 0;
    float _minZ = 0;

    QTextStream _in(&_file);
    QMap<uint, uint> _indexMap;
    uint _count = 0;
    uint _set = 0;
    QColor _setColor = QColor(0, 76, 228);
    float _red;
    float _greed;
    float _blue;

    QTime _time;
    _time.restart();  // start timekeeping

    while (!_in.atEnd())
    {
        QString _line = _in.readLine();
        if (_line.startsWith("GRID*")) { // if start with "GRID*". it's large format
            uint _VertexID = _line.mid(8, 16).toUInt(); // first field
            float _x = _line.mid(40, 16).toFloat();
            float _y = _line.mid(56, 16).toFloat();
            _line = _in.readLine(); // second field
            float _z = _line.mid(8, 16).toFloat();

            if (_count == 0) {
                _minX = _maxX = _x;
                _minY = _maxY = _y;
                _minZ = _maxZ = _z;
            } else {
                _maxX = _maxX > _x ? _maxX : _x;
                _maxY = _maxY > _y ? _maxY : _y;
                _maxZ = _maxZ > _z ? _maxZ : _z;
                _minX = _minX < _x ? _minX : _x;
                _minY = _minY < _y ? _minY : _y;
                _minZ = _minZ < _z ? _minZ : _z;
            }

            // create point
            Point *_point = new Point(_x, _y, _z, _VertexID);
            m_allPointMap[_VertexID] = _point;

            // add point to the point list and calculate the point index for OpenGL
            CreatePoint(_x, _y, _z, _VertexID, _indexMap, _count);
//            CREATEPOINT(_x, _y, _z, _VertexID, _indexMap, _count);

            _count++;
            continue;
        } else if (_line.startsWith("GRID")) { // if start with "GRID". it present the vertex
            uint _VertexID = _line.mid(8, 8).toUInt();
            float _x = stdNumberString(_line.mid(24, 8)).toFloat();
            float _y = stdNumberString(_line.mid(32, 8)).toFloat();
            float _z = stdNumberString(_line.mid(40, 8)).toFloat();

            if (_count == 0) {
                _minX = _maxX = _x;
                _minY = _maxY = _y;
                _minZ = _maxZ = _z;
            } else {
                _maxX = _maxX > _x ? _maxX : _x;
                _maxY = _maxY > _y ? _maxY : _y;
                _maxZ = _maxZ > _z ? _maxZ : _z;
                _minX = _minX < _x ? _minX : _x;
                _minY = _minY < _y ? _minY : _y;
                _minZ = _minZ < _z ? _minZ : _z;
            }

            Point *_point = new Point(_x, _y, _z, _VertexID);
            m_allPointMap[_VertexID] = _point;

            // add point to the point list and calculate the point index for OpenGL
            CreatePoint(_x, _y, _z, _VertexID, _indexMap, _count);
//            CREATEPOINT(_x, _y, _z, _VertexID, _indexMap, _count);

            _count++;
            continue;
        } else if ( _line.startsWith("CTRIA3") ) {
            QStringList _stringlist;
            for (int var = 24; var < _line.size(); var += 8 ) {  // only need the point id
                if ( !_line.mid(var, 8).startsWith("+EA") ) {
                    _stringlist.push_back(_line.mid(var, 8));
                }
            }

            uint _triangelID     = _line.mid(8, 8).toUInt();
            uint _materialID     = _line.mid(16, 8).toUInt();

            // judgement the color is exist
            if ( _set != _materialID ) {
                QMap<uint, QColor>::iterator _itor = m_allSetColor.find(_materialID);
                if ( _itor != m_allSetColor.end() ){
                    _setColor = _itor.value();
                } else {
                    // create color
                    _setColor = QColor(rand()%255, rand()%255, rand()%255);
                    m_allSetColor.insert(_materialID, _setColor);
                }
                _red = static_cast<float>(_setColor.redF());
                _greed = static_cast<float>(_setColor.greenF());
                _blue = static_cast<float>(_setColor.blueF());
                _set = _materialID;
            }

            // if it's a face,it need not to test delete
            Triangle*_triangle = new Triangle(_triangelID,
                                              _materialID,
                                              _stringlist,
                                              _red,
                                              _greed,
                                              _blue);
            m_allTrianglesMap.insert(_triangelID, _triangle);

            continue;
        } else if ( _line.startsWith("CTRIA6") ) {
            QStringList _stringlist;
            for (int var = 24; var < _line.size(); var += 8 ) {  // only need the point id
                if ( !_line.mid(var, 8).startsWith("+EA") ) {
                    _stringlist.push_back(_line.mid(var, 8));
                }
            }

            uint _triangelID     = _line.mid(8, 8).toUInt();
            uint _materialID     = _line.mid(16, 8).toUInt();

            // judgement the color is exist
            if ( _set != _materialID ) {
                QMap<uint, QColor>::iterator _itor = m_allSetColor.find(_materialID);
                if ( _itor != m_allSetColor.end() ){
                    _setColor = _itor.value();
                } else {
                    // create color
                    _setColor = QColor(rand()%255, rand()%255, rand()%255);
                    m_allSetColor.insert(_materialID, _setColor);
                }
                _red = static_cast<float>(_setColor.redF());
                _greed = static_cast<float>(_setColor.greenF());
                _blue = static_cast<float>(_setColor.blueF());
                _set = _materialID;
            }

            // if it's a face,it need not to test delete
            Triangle*_triangle = new Triangle(_triangelID,
                                              _materialID,
                                              _stringlist,
                                              _red,
                                              _greed,
                                              _blue);
            m_allTrianglesMap.insert(_triangelID, _triangle);

            continue;
        } else if (_line.startsWith("CTRIAR")) {
            QStringList _stringlist;
            for (int var = 24; var < _line.size(); var += 8 ) {  // only need the point id
                if ( !_line.mid(var, 8).startsWith("+EA") ) {
                    _stringlist.push_back(_line.mid(var, 8));
                }
            }
            uint _triangelID     = _line.mid(8, 8).toUInt();
            uint _materialID     = _line.mid(16, 8).toUInt();

            // judgement the color is exist
            if ( _set != _materialID ) {
                QMap<uint, QColor>::iterator _itor = m_allSetColor.find(_materialID);
                if ( _itor != m_allSetColor.end() ) {
                    _setColor = _itor.value();
                } else {
                    // create color
                    _setColor = QColor(rand()%255, rand()%255, rand()%255);
                    m_allSetColor.insert(_materialID, _setColor);
                }
                _red = static_cast<float>(_setColor.redF());
                _greed = static_cast<float>(_setColor.greenF());
                _blue = static_cast<float>(_setColor.blueF());
                _set = _materialID;
            }

            // create triangle
            Triangle*_triangle = new Triangle(_triangelID,
                                              _materialID,
                                              _stringlist,
                                              _red,
                                              _greed,
                                              _blue);
            m_allTrianglesMap.insert(_triangelID, _triangle);

            continue;
        } else if (_line.startsWith("CQUAD4")) {  // this keyword will be analysis as Quad
            QStringList _stringlist;
            for (int var = 24; var < _line.size(); var += 8 ) {  // only need the point id
                if ( !_line.mid(var, 8).startsWith("+EA") ) {
                    _stringlist.push_back(_line.mid(var, 8));
                }
            }

            uint _QuadID = _line.mid(8, 8).toUInt();
            uint _materialID = _line.mid(16, 8).toUInt();

            // judgement the color is exist
            if ( _set != _materialID ) {
                QMap<uint, QColor>::iterator _itor = m_allSetColor.find(_materialID);
                if ( _itor != m_allSetColor.end() ) {
                    _setColor = _itor.value();
                } else {
                    // create color
                    _setColor = QColor(rand()%255, rand()%255, rand()%255);
                    m_allSetColor.insert(_materialID, _setColor);
                }
                _red = static_cast<float>(_setColor.redF());
                _greed = static_cast<float>(_setColor.greenF());
                _blue = static_cast<float>(_setColor.blueF());
                _set = _materialID;
            }

            // create Quadrangle
            Quadrangle*_quadrangle = new Quadrangle(_QuadID,
                                                    _materialID,
                                                    _stringlist,
                                                    _red,
                                                    _greed,
                                                    _blue);
            m_allQuadMap.insert(_QuadID, _quadrangle);

            continue;
        } else if (_line.startsWith("CQUAD8")) {  // this keyword will be analysis as Quad
            QStringList _stringlist;
            for (int var = 24; var < _line.size(); var += 8 ) {  // only need the point id
                if ( !_line.mid(var, 8).startsWith("+EA") ) {
                    _stringlist.push_back(_line.mid(var, 8));
                }
            }

            uint _QuadID = _line.mid(8, 8).toUInt();
            uint _materialID = _line.mid(16, 8).toUInt();

            // judgement the color is exist
            if ( _set != _materialID ) {
                QMap<uint, QColor>::iterator _itor = m_allSetColor.find(_materialID);
                if ( _itor != m_allSetColor.end() ) {
                    _setColor = _itor.value();
                } else {
                    // create color
                    _setColor = QColor(rand()%255, rand()%255, rand()%255);
                    m_allSetColor.insert(_materialID, _setColor);
                }
                _red = static_cast<float>(_setColor.redF());
                _greed = static_cast<float>(_setColor.greenF());
                _blue = static_cast<float>(_setColor.blueF());
                _set = _materialID;
            }

            // create Quadrangle
            Quadrangle*_quadrangle = new Quadrangle(_QuadID,
                                                    _materialID,
                                                    _stringlist,
                                                    _red,
                                                    _greed,
                                                    _blue);
            m_allQuadMap.insert(_QuadID, _quadrangle);

            continue;
        } else if (_line.startsWith("CTETRA")) { // this is a tetrahedron
            QStringList _stringlist;
            if (_line.contains("+")) {
                _line += _in.readLine();
            } else if (_line.size()>58) { // judement the long type
                _line += _in.readLine().remove(0, 8);
            }
            for (int var = 24; var < _line.size(); var += 8 ) {  // only need the point id
                if ( !_line.mid(var, 8).startsWith("+") ) {
                    _stringlist.push_back(_line.mid(var, 8));
                }
            }

            uint _ctetraID = _line.mid(8, 8).toUInt();
            uint _materialID = _line.mid(16, 8).toUInt();

            // judgement the color is exist
            if ( _set != _materialID ) {
                QMap<uint, QColor>::iterator _itor = m_allSetColor.find(_materialID);
                if ( _itor != m_allSetColor.end() ) {
                    _setColor = _itor.value();
                } else {
                    // create color
                    _setColor = QColor(rand()%255, rand()%255, rand()%255);
                    m_allSetColor.insert(_materialID, _setColor);
                }
                _red = static_cast<float>(_setColor.redF());
                _greed = static_cast<float>(_setColor.greenF());
                _blue = static_cast<float>(_setColor.blueF());
                _set = _materialID;
            }

            Tetrahedron* _tetrahedron = new Tetrahedron(_ctetraID ,
                                                        _materialID,
                                                        _stringlist,
                                                        _red,
                                                        _greed,
                                                        _blue);
            m_allTetrahedronMap.insert(_ctetraID, _tetrahedron);
        } else if (_line.startsWith("CHEXA")) { // this is a  hexahedron
            QStringList _stringlist;
            if (_line.contains("+")) {
                _line += _in.readLine();
            }
            for (int var = 24; var < _line.size(); var += 8 ) {  // only need the point id
                if ( !_line.mid(var, 8).startsWith("+EA") && !_line.mid(var, 8).startsWith("+")) {
                    _stringlist.push_back(_line.mid(var, 8));
                }
            }

            uint _QuadID = _line.mid(8, 8).toUInt();
            uint _materialID = _line.mid(16, 8).toUInt();

            // judgement the color is exist
            if ( _set != _materialID ) {
                QMap<uint, QColor>::iterator _itor = m_allSetColor.find(_materialID);
                if ( _itor != m_allSetColor.end() ) {
                    _setColor = _itor.value();
                } else {
                    // create color
                    _setColor = QColor(rand()%255, rand()%255, rand()%255);
                    m_allSetColor.insert(_materialID, _setColor);
                }
                _red = static_cast<float>(_setColor.redF());
                _greed = static_cast<float>(_setColor.greenF());
                _blue = static_cast<float>(_setColor.blueF());
                _set = _materialID;
            }

            Hexahedron* _hexahedron = new Hexahedron(_QuadID,
                                                     _materialID,
                                                     _stringlist,
                                                     _red,
                                                     _greed,
                                                     _blue);
            m_allHexahedronMap.insert(_QuadID, _hexahedron);

            continue;
        } else if (_line.startsWith("CPENTA")) {
            QStringList _stringlist;
            for (int var = 24; var < _line.size(); var += 8) {  // only need the point id
                _stringlist.push_back(_line.mid(var, 8));
            }

            uint _FaceID = _line.mid(8, 8).toUInt();
            uint _materialID = _line.mid(16, 8).toUInt();

            // judgement the color is exist
            if ( _set != _materialID ) {
                QMap<uint, QColor>::iterator _itor = m_allSetColor.find(_materialID);
                if ( _itor != m_allSetColor.end() ) {
                    _setColor = _itor.value();
                } else {
                    // create color
                    _setColor = QColor(rand()%255, rand()%255, rand()%255);
                    m_allSetColor.insert(_materialID, _setColor);
                }
                _red = static_cast<float>(_setColor.redF());
                _greed = static_cast<float>(_setColor.greenF());
                _blue = static_cast<float>(_setColor.blueF());
                _set = _materialID;
            }

            TriangularPrism* _triangularPrism = new TriangularPrism(_FaceID,
                                                                    _materialID,
                                                                    _stringlist,
                                                                    _red,
                                                                    _greed,
                                                                    _blue);
            m_allTriangularPrismMap.insert(_FaceID, _triangularPrism);
            continue;
        } else if (_line.startsWith("$")) {
            continue;
        } else {
            qWarning()<<_line;
//            showMessage(_line);
        }
    }

//    showMessage(tr("**************************************************************"));
//    showMessage(tr("********************Analysis BDFFiles*************************"));
//    showMessage(tr("           Point Number: ").arg(m_allPointMap.size()));
//    showMessage(tr("            Line Number: ").arg(m_allLinesMap.size()));
//    showMessage(tr("        Triangle Number: ").arg(m_allTrianglesMap.size()));
//    showMessage(tr("      Quadrangle Number: ").arg(m_allQuadMap.size()));
//    showMessage(tr("     Tetrahedron Number: ").arg(m_allTetrahedronMap.size()));
//    showMessage(tr("      Hexahedron Number: ").arg(m_allHexahedronMap.size()));
//    showMessage(tr(" TriangularPrism Number: ").arg(m_allTriangularPrismMap.size()));
//    showMessage(tr("       read file Number: ").arg(_time.elapsed()));
//    showMessage(tr("**************************************************************")+'\n'+'\n');

    qDebug()<<tr("**************************************************************");
    qDebug()<<tr("********************Analysis BDFFiles*************************");
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

//    calculatAllShow();

    calculatShow();

    emit ReadFileFinished();

    return true;
}
