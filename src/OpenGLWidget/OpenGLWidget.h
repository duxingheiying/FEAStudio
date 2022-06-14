#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QtOpenGL/QtOpenGL>

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
public:
    explicit OpenGLWidget(QWidget* parent = nullptr);
    virtual ~OpenGLWidget() override;

protected:
private:
    virtual void initializeGL() override;
    virtual void resizeGL(const GLint width, const GLint height) override;
    virtual void paintGL() override;
};

#endif // ! OPENGLWIDGET_H
