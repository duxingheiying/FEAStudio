#-------------------------------------------------
#
# Project created by QtCreator 2019-02-20T17:08:56
# designed by guweicao
# copyright by guweicao
#-------------------------------------------------

QT += core gui opengl xml concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EngieStudio
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_FILE = AppIcon.rc

CONFIG += c++11

# disable the warming the unused funtion
# disable the warming the unused parameter
# disable the warming the unused variable

QMAKE_CXXFLAGS_RELEASE += -Wno-unused-function
QMAKE_CXXFLAGS_RELEASE += -Wno-unused-parameter
QMAKE_CXXFLAGS_RELEASE += -Wno-unused-variable

#QMAKE_CXXFLAGS_DEBUG += -Wno-unused-function
#QMAKE_CXXFLAGS_DEBUG += -Wno-unused-parameter
#QMAKE_CXXFLAGS_DEBUG += -Wno-unused-variable

#win32|winrt|wince {
#    message("ActiveQt is a Windows Desktop-only module. Will just generate a docs target.")
#}

## debug temporarily
#win32: CONFIG(debug, debug|release):CONFIG += console
#win32: CONFIG(release):CONFIG += console

include($$PWD/Geometry/geomertryelement.pri)
include($$PWD/OpenGLWidget/OpenGLWidget.pri)
include($$PWD/Files/files.pri)
include($$PWD/MsgHandle/MsgHandler.pri)
include($$PWD/standartTools/standartTools.pri)

INCLUDEPATH += "$$PWD\..\..\..\glm\glm"

LIBS += -lopengl32 \
        -lglu32

# freetype lib
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../freetype-2.10.1/objs/x64/release/ -lfreetype
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../freetype-2.10.1/objs/x64/debug/ -lfreetype

INCLUDEPATH += $$PWD/../../freetype-2.10.1/include
DEPENDPATH += $$PWD/../../freetype-2.10.1/include

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../freetype-2.10.1/objs/Win32/release/libfreetype.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../freetype-2.10.1/objs/Win32/debug/libfreetype.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../freetype-2.10.1/objs/Win32/release/freetype.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../freetype-2.10.1/objs/Win32/debug/freetype.lib

SOURCES += \
        Color.cpp \
        CurveMdiSubWin.cpp \
        GraphicMdiSubWin.cpp \
        MainWindow.cpp \
        MessageDockWidget.cpp \
        PentagonalPyramid.cpp \
        PropertyDockWidget.cpp \
        TableMdiSubWin.cpp \
        TreeDockWidget.cpp \
        Vector3D.cpp \
        main.cpp \
        Vertex.cpp

HEADERS += \
        Color.h \
        CurveMdiSubWin.h \
        GraphicMdiSubWin.h \
        MainWindow.h \
        MessageDockWidget.h \
        PentagonalPyramid.h \
        PropertyDockWidget.h \
        TableMdiSubWin.h \
        TreeDockWidget.h \
        Vector3D.h \
        Vertex.h

FORMS += \
    MainWindow.ui

RESOURCES += \
    actions.qrc

DISTFILES += \
    AppIcon.rc

win32 {
    buildPath = $$PWD/../build
    MOC_DIR = $$buildPath/FEMStudio/moc
    RCC_DIR = $$buildPath/FEMStudio/rcc
    UI_DIR = $$buildPath/FEMStudio/ui
    OBJECTS_DIR = $$buildPath/FEMStudio/object
    QMAKEPATH = $$buildPath/FEMStudio/makefile
    CONFIG(debug, debug|release) {
        DESTDIR = $$buildPath/debug
    } else {
        DESTDIR = $$buildPath/release
    }
}

tdestdir = $$clean_path($$DESTDIR/fonts)
#   DESTDIR = $$tdestdir
   tdestdir = $$shell_quote($$tdestdir)
   RESDIR = $$shell_quote($$clean_path($$PWD/fonts))

win32{
   tdestdir = $$system_path($$tdestdir)
   RESDIR = $$system_path($$RESDIR)
}

   resourcedata.commands = $(COPY_DIR) $$RESDIR $$tdestdir
   first.depends = $(first) resourcedata
   export(first.depends)
   export(resourcedata.commands)
   QMAKE_EXTRA_TARGETS += first resourcedata

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

