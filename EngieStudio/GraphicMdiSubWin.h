#ifndef GRAPHICMDISUBWIN_H
#define GRAPHICMDISUBWIN_H

#include <QMainWindow>

class GLWidget;

class GraphicMdiSubWin : public QMainWindow
{
    Q_OBJECT
public:
    explicit GraphicMdiSubWin(QWidget *parent = nullptr);
    virtual ~GraphicMdiSubWin() override;

public:

protected:

private:

public:
    GLWidget* m_pGLWidget;

protected:

private:

signals:

public slots:
};

#endif // GRAPHICMDISUBWIN_H
