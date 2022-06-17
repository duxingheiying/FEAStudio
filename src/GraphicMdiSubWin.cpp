#include "GraphicMdiSubWin.h"

#include "GLWidget.h"

GraphicMdiSubWin::GraphicMdiSubWin(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowTitle(tr(" Graphic "));
    setWindowIcon(QIcon(":/Icon/Actions/ios.png"));
    m_pGLWidget = new GLWidget(this);
    this->setCentralWidget(m_pGLWidget);
}

GraphicMdiSubWin::~GraphicMdiSubWin()
{
}
