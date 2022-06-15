#include "Shader.h"
//#include "glwidget.h"

Shader::Shader(const GLchar* vertexPath,
               const GLchar* fragmentPath, QWidget* parent) :
    GLWidget (parent)
{
    // get the vertex shader and frag shader from the file
    std::string   vertexCode;
    std::string   fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // confirm the throwout error from the fstream
    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);
    try
    {
        // Open File
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read the file into the temp buffer
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file
        vShaderFile.close();
        fShaderFile.close();
        // change the stream into GLchar*
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // complite the shader
    GLuint vertex, fragment;
    GLint success;
    char infoLog[512];

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    // if it has error print out the error
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // the frag shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    // if has error print it
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMEN::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // shader program
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    glLinkProgram(this->Program);
    // print the error if have
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->Program, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // delete all the shader it has link to our program
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::Shader(const QString vertexPath,
               const QString fragmentPath, QWidget *parent) :
    GLWidget (parent)
{
    std::string   vertexCode;
    std::string   fragmentCode;

    QFile _vShaderFile;
    QFile _fShaderFile;

    _vShaderFile.setFileName(vertexPath);
    _fShaderFile.setFileName(fragmentPath);

    if (_vShaderFile.open(QIODevice::ReadOnly|QIODevice::Text) &&
            _vShaderFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream _vShaderStream(&_vShaderFile);
        QTextStream _fShaderStream(&_fShaderFile);

        QString _vShaderString = _vShaderStream.readAll();
        QString _fShaderString = _fShaderStream.readAll();

        vertexCode = _vShaderString.toStdString();
        fragmentCode = _fShaderString.toStdString();
    }

    // get the vertex shader and frag shader from the file
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // complite the shader
    GLuint vertex, fragment;
    GLint success;
    char infoLog[512];

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    // if it has error print out the error
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // the frag shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    // if it has error print out the error
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMEN::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // complite the shader
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    glLinkProgram(this->Program);
    // if it has error print out the error
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->Program, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // delete all the shader it has link to our program
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::setFloat(const char* fragmentPath,
                      const GLfloat offset)
{
    // update Uniform color
    GLint vertexOffsetLocation = glGetUniformLocation(Program, fragmentPath);
    glUniform1f(vertexOffsetLocation, offset);
}

void Shader::Use()
{
    glUseProgram(this->Program);
}

Shader::~Shader()
{
}
