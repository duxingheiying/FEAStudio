#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <QtOpenGL/QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLExtraFunctions>

#include "GLWidget.h"

//class GLWidget;
class Shader : GLWidget
{
public:
    explicit Shader(const GLchar* vertexPath,
                    const GLchar* fragmentPath,
                    QWidget* parent);

    explicit Shader(const QString vertexPath,
                    const QString fragmentPath,
                    QWidget *parent);
    ~Shader();

public:
    inline void setFloat(const GLchar* fragmentPath, const GLfloat offset);
    inline void Use();

public:
    GLuint Program;

private:
};
