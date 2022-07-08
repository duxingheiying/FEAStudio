#include "GLWidget.h"
#include <iostream>
#include <GL/glu.h>

// all the cast
// reinterpret_cast
// static_cast
// dynamic_cast
// const_cast

#define CHECK( stmt, info ) \
    if ( !stmt )\
{\
    PopupError( info );\
    return;\
    }

GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget (parent)
{
    // shader pipeline range
    m_fRange = 20.0f;

    // pipeline range
    resize(800, 800);
    m_pArcBallT = new ArcBallT(800.0f, 800.0f);

    m_fScale = 1.0f;

    // Memory recovery
    // m_vVertexs.swap(QVector<GLfloat>()); clear all the infomation
//    QVector<GLfloat>().swap(m_vVertexs);

    m_bShowPoint = false;
    m_bShowLine  = false;
    m_bShowFace  = true;
    m_bShowMesh  = true;
    m_bTransparency = false;
    m_pDepthBuffer = nullptr;
    m_fOffset = 0.5f;
}

GLWidget::~GLWidget()
{
}

QString GLWidget::getStringFromUnsignedChar(const unsigned char *str)
{
    QString s;
    QString result = "";
    char* _tempChar = reinterpret_cast<char*>(const_cast<unsigned char*>(str) ); // warning unsigned char* to char*

//    size_t rev = std::strlen( _tempChar );
////    long long rev = *(&str + 1) - str;
////    size_t rev = sizeof (*str) / sizeof (str[0]);
//    // Print String in Reverse order....
//    for ( size_t i = 0; i < rev; i++) {
//        s = QString("%1").arg(str[i],0,16);
//        if(s == "0") {
//            s="00";
//        }
//        result.append(s);
//    }

    result = QString::fromUtf8(_tempChar);
    return result;
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
//    m_pFunction = context()->extraFunctions();
    m_pFunction = context()->versionFunctions<QOpenGLFunctions_4_5_Core>();

    // basic information
    const GLubyte * name = glGetString(GL_VENDOR);
    const GLubyte * biaoshifu = glGetString(GL_RENDERER);
    const GLubyte * OpenGLVersion = glGetString(GL_VERSION);
    const GLubyte * gluVersion = gluGetString(GLU_VERSION);
    qDebug()<<QStringLiteral("OpenGL实现厂商的名字:")<<getStringFromUnsignedChar(name);
    qDebug()<<QStringLiteral("渲染器标识符：       ")<<getStringFromUnsignedChar(biaoshifu);
    qDebug()<<QStringLiteral("OpenGL实现的版本号： ")<<getStringFromUnsignedChar(OpenGLVersion);
    qDebug()<<QStringLiteral("GLU工具库版本：      ")<<getStringFromUnsignedChar(gluVersion);

    // Clear the colorbuffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor( 0.2f, 0.3f, 0.3f, 0.0f);
    glShadeModel(GL_SMOOTH);
//    glEnable( GL_DEPTH_TEST );
    glDisable( GL_DEPTH_TEST );
//    glDepthMask(GL_FALSE);   // set depbuffur only read
    glDepthFunc(GL_LESS);
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
//    glEnable(GL_POINT_SMOOTH);
//    glEnable(GL_LINE_SMOOTH);
//    glEnable(GL_POLYGON_SMOOTH);

//    glDisable(GL_LIGHTING);
//    glEnable(GL_COLOR_MATERIAL);
//    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,
//                  GL_SEPARATE_SPECULAR_COLOR);
//    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
//    glFrontFace( GL_CCW );
//    glEnable( GL_CULL_FACE );  // cut of the  back face

    /* ****************************************************************************
     * GL_BLEND and GL_POLYGON_SMOOTH don't be used at the same time, if you do
     * that, the black line will appear on the quad face. I don't find the reason
     *  now! sover the text.
     * ****************************************************************************/
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glBlendColor(0.0f,0.5f, 0.7f, 1.0f);
//    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glBlendEquation(GL_FUNC_ADD);
//    glDisable(GL_DEPTH_TEST);   // if you use GL_BLEND you need to disable Depth test

    initializeProgram();
    initialTextTexture();
    initializeOIT();
    initializeContralMatrix();

    qDebug()<<tr("has initialGL");
}

void GLWidget::initializeProgram()
{
    // this is Qt QString function
    m_uiVertexsShader = CreateProgram(QString(":/Shader/Shader/VertexsVertexShader.vsh"),
                                      QString(":/Shader/Shader/LinesFragShader.frag"));

    m_iVertexCcoLoc = glGetUniformLocation(m_uiVertexsShader, "objectColor");
    m_iVertexLightColorLoc  = glGetUniformLocation(m_uiVertexsShader, "lightColor");
    m_iVertexLightPosLoc    = glGetUniformLocation(m_uiVertexsShader, "lightPos");
    m_iVertexViewPosLoc     = glGetUniformLocation(m_uiVertexsShader, "viewPos");

    // get the locale of the value from the shader
    m_iVertexsModel_Loc = glGetUniformLocation(m_uiVertexsShader, "model");
    m_iVertexsView_Loc = glGetUniformLocation(m_uiVertexsShader, "view");
    m_iVertexsProject_Loc = glGetUniformLocation(m_uiVertexsShader, "projection");


    m_uiLinesShader = CreateProgram(QString(":/Shader/Shader/LinesVertexShader.vsh"),
                                    QString(":/Shader/Shader/LinesFragShader.frag"));

    m_iLineCcoLoc = glGetUniformLocation(m_uiLinesShader, "objectColor");
    m_iLineLightColorLoc  = glGetUniformLocation(m_uiLinesShader, "lightColor");
    m_iLineLightPosLoc    = glGetUniformLocation(m_uiLinesShader, "lightPos");
    m_iLineViewPosLoc     = glGetUniformLocation(m_uiLinesShader, "viewPos");

    // get the locale of the value from the shader
    m_iLineModel_Loc = glGetUniformLocation(m_uiLinesShader, "model");
    m_iLineView_Loc = glGetUniformLocation(m_uiLinesShader, "view");
    m_iLineProject_Loc = glGetUniformLocation(m_uiLinesShader, "projection");


    m_uiFacesShader = CreateProgram(QString(":/Shader/Shader/FacesVertexShader.vsh"),
                                      QString (":/Shader/Shader/FacesFragShader.frag"));

    m_uiTextsShader = CreateProgram(QString(":/Shader/Shader/text.vsh"),
                                    QString(":/Shader/Shader/text.frag"));

    m_uiBackgroundShader = CreateProgram(QString(":/Shader/Shader/BackgroundVertex.vsh"),
                                         QString(":/Shader/Shader/BackgroundFrag.frag"));

    // if it doesn't hava mesh,it will not need offset
    m_iBackColor = glGetUniformLocation(m_uiBackgroundShader, "objectColor");
    m_iBackLightColor = glGetUniformLocation(m_uiBackgroundShader, "lightColor");
    m_iBackLightPos = glGetUniformLocation(m_uiBackgroundShader, "lightPos");
    m_iBackViewPos = glGetUniformLocation(m_uiBackgroundShader, "viewPos");

    // get the locale of the value from the shader
    m_iBackMode_loc = glGetUniformLocation(m_uiBackgroundShader, "model");
    m_iBackView_Loc  = glGetUniformLocation(m_uiBackgroundShader, "view");
    m_iBackProject_Loc = glGetUniformLocation(m_uiBackgroundShader, "projection");

    m_uiMultiLightShader = CreateProgram(QString(":/Shader/Shader/multilighting.vsh"),
                                         QString(":/Shader/Shader/multilighting.frag"));

    m_uiMaterialLightShader = CreateProgram(QString(":/Shader/Shader/lighting.vsh"),
                                            QString(":/Shader/Shader/lighting.frag"));

    m_iFaceViewPosLoc = glGetUniformLocation(m_uiMaterialLightShader, "viewPos");
    m_iFaceLightPos = glGetUniformLocation(m_uiMaterialLightShader, "light.position");
    m_iFaceLightambinet = glGetUniformLocation(m_uiMaterialLightShader, "light.ambient");
    m_iFaceLightdiffuse = glGetUniformLocation(m_uiMaterialLightShader, "light.diffuse");
    m_iFaceLightspecular = glGetUniformLocation(m_uiMaterialLightShader, "light.specular");

    m_iFaceMaterialambinet = glGetUniformLocation(m_uiMaterialLightShader, "material.ambient");
    m_iFaceMaterialdiffuse = glGetUniformLocation(m_uiMaterialLightShader, "material.diffuse");
    m_iFaceMaterialspecular = glGetUniformLocation(m_uiMaterialLightShader, "material.specular");
    m_iFaceMaterialshininess = glGetUniformLocation(m_uiMaterialLightShader, "material.shininess");

    // get the locale of the value from the shader
    m_iFacemodel_Loc = glGetUniformLocation(m_uiMaterialLightShader, "model");
    m_iFaceView_Loc = glGetUniformLocation(m_uiMaterialLightShader, "view");
    m_iFaceProject_Loc = glGetUniformLocation(m_uiMaterialLightShader, "projection");

    // Order Independent Transparency
    render_scene_prog = CreateProgram(QString(":/Shader/Shader/build_lists.vert"),
                                      QString(":/Shader/Shader/build_lists.frag"));

    render_scene_uniforms.model_matrix = glGetUniformLocation(render_scene_prog, "model_matrix");
    render_scene_uniforms.view_matrix = glGetUniformLocation(render_scene_prog, "view_matrix");
    render_scene_uniforms.projection_matrix = glGetUniformLocation(render_scene_prog, "projection_matrix");
    m_iRenderLightPosition = glGetUniformLocation(render_scene_prog, "light_position");

    resolve_program = CreateProgram(QString(":/Shader/Shader/resolve_lists.vert"),
                                    QString(":/Shader/Shader/resolve_lists.frag"));

    // this is C program function
    // GLchar _vertPaht[] = "D:\\Project\\EngieStudio\\textures.vsh";
    // GLchar _fragPath[] = "D:\\Project\\EngieStudio\\textures.frag";
    // CreateProgram( _vertPaht, _fragPath);
}

void GLWidget::initializeOIT()
{
    GLuint * data;
    // Create head pointer texture
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &head_pointer_texture);
    glBindTexture(GL_TEXTURE_2D, head_pointer_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32UI, MAX_FRAMEBUFFER_WIDTH, MAX_FRAMEBUFFER_HEIGHT, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
    m_pFunction->glBindImageTexture(0, head_pointer_texture, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32UI);

    // Create buffer for clearing the head pointer texture
    glGenBuffers(1, &head_pointer_clear_buffer);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, head_pointer_clear_buffer);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, MAX_FRAMEBUFFER_WIDTH * MAX_FRAMEBUFFER_HEIGHT * sizeof(GLuint), nullptr, GL_STATIC_DRAW);
    data = static_cast<GLuint *>(m_pFunction->glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY));
    memset(data, 0x00, MAX_FRAMEBUFFER_WIDTH * MAX_FRAMEBUFFER_HEIGHT * sizeof(GLuint));
    m_pFunction->glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);

    // Create the atomic counter buffer
    glGenBuffers(1, &atomic_counter_buffer);
    glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, atomic_counter_buffer);
    glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(GLuint), nullptr, GL_DYNAMIC_COPY);

    // Create the linked list storage buffer
    glGenBuffers(1, &linked_list_buffer);
    glBindBuffer(GL_TEXTURE_BUFFER, linked_list_buffer);
    glBufferData(GL_TEXTURE_BUFFER, MAX_FRAMEBUFFER_WIDTH * MAX_FRAMEBUFFER_HEIGHT * 3 * sizeof(vec4), nullptr, GL_DYNAMIC_COPY);
    glBindBuffer(GL_TEXTURE_BUFFER, 0);

    // Bind it to a texture (for use as a TBO)
    glGenTextures(1, &linked_list_texture);
    glBindTexture(GL_TEXTURE_BUFFER, linked_list_texture);
    m_pFunction->glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32UI, linked_list_buffer);
    glBindTexture(GL_TEXTURE_BUFFER, 0);

    m_pFunction->glBindImageTexture(1, linked_list_texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32UI);

    // draw map of texture
    m_pFunction->glGenVertexArrays(1, &quad_vao);
    m_pFunction->glBindVertexArray(quad_vao);
    static const GLfloat quad_verts[] =
    {
        -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
        -1.0f,  1.0f,
    };

    glGenBuffers(1, &quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_verts), quad_verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
    glClearDepth(1.0);
}

void GLWidget::Display()
{
    GLuint * data;
    m_pFunction->glDisable(GL_DEPTH_TEST);
    m_pFunction->glDisable(GL_CULL_FACE);

    // Reset atomic counter
    m_pFunction->glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, atomic_counter_buffer);
    data = static_cast<GLuint *>(m_pFunction->glMapBuffer(GL_ATOMIC_COUNTER_BUFFER, GL_WRITE_ONLY));
    data[0] = 0;

    m_pFunction->glUnmapBuffer(GL_ATOMIC_COUNTER_BUFFER);

    // Clear head-pointer image
    m_pFunction->glBindBuffer(GL_PIXEL_UNPACK_BUFFER, head_pointer_clear_buffer);
    m_pFunction->glBindTexture(GL_TEXTURE_2D, head_pointer_texture);
    m_pFunction->glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_nGLWWidth, m_nGLHeight, GL_RED_INTEGER, GL_UNSIGNED_INT, nullptr);
    m_pFunction->glBindTexture(GL_TEXTURE_2D, 0);

    // Bind head-pointer image for read-write
    m_pFunction->glBindImageTexture(0, head_pointer_texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32UI);

    // Bind linked-list buffer for write
    m_pFunction->glBindImageTexture(1, linked_list_texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32UI);

    // set program
    m_pFunction->glUseProgram(render_scene_prog);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // draw the background
    const QMatrix4x4 _BackMatrx;
    glUniformMatrix4fv(render_scene_uniforms.model_matrix, 1, GL_FALSE, _BackMatrx.data());
    glUniformMatrix4fv(render_scene_uniforms.view_matrix, 1, GL_FALSE, m_qViewMatrix.data());
    glUniformMatrix4fv(render_scene_uniforms.projection_matrix, 1, GL_FALSE, m_qProjectMatrix.data());
    glUniform3f(m_iRenderLightPosition, 30*m_fRange, 500*m_fRange, 1000*m_fRange);
    DrawBackGroundCall();

    // draw the element triangle and quad
    const QMatrix4x4 _Quadmatrx = m_qTranslateMatrix * m_qRoateMatrix * m_qModelMatrix;
    glUniformMatrix4fv(render_scene_uniforms.model_matrix, 1, GL_FALSE, _Quadmatrx.data());
    glUniformMatrix4fv(render_scene_uniforms.view_matrix, 1, GL_FALSE, m_qViewMatrix.data());
    glUniformMatrix4fv(render_scene_uniforms.projection_matrix, 1, GL_FALSE, m_qProjectMatrix.data());
    glUniform3f(m_iRenderLightPosition, 30*m_fRange, 500*m_fRange, 1000*m_fRange);
    QuadsDrawCall();
    TriangleDrawCall();

    // draw OIT face
    m_pFunction->glDisable(GL_BLEND);
    m_pFunction->glBindVertexArray(quad_vao);
    m_pFunction->glUseProgram(resolve_program);
    m_pFunction->glDrawArrays(GL_QUADS, 0, 4);

    // disbin the buffer
    m_pFunction->glBindVertexArray(0);
    m_pFunction->glUseProgram(0);
}


bool GLWidget::initializeContralMatrix()
{
    // initial  all the matrix
    m_qBackGroundMatrix.setToIdentity();
    Matrix4fSetIdentity(&m_ArcTransform);
    Matrix3fSetIdentity(&m_ArcLastRot);
    Matrix3fSetIdentity(&m_ArcThisRot);
    m_qRoateMatrix.setToIdentity();
    m_qTranslateMatrix.setToIdentity();
    m_qModelMatrix.setToIdentity();
    // translate the model to the center of GLWidget
    m_qModelMatrix.translate(-m_vCenter.x(), -m_vCenter.y(), -m_vCenter.z());
    m_qViewMatrix.setToIdentity();
    // instialize project matrix
    m_qProjectMatrix.setToIdentity();
    if (m_nGLWWidth > m_nGLHeight) {
        // translate Word coords to pixels
        m_fProportionality = static_cast<GLfloat>(m_nGLHeight) / m_fRange;
        m_dHWPropotion = double(m_nGLWWidth) / double(m_nGLHeight);
        m_qProjectMatrix.ortho(-m_fRange/2 * GLfloat ( m_dHWPropotion ), m_fRange/2 * GLfloat (m_dHWPropotion),
                               -m_fRange/2,                              m_fRange/2,
                               -m_fRange/2 * 100.0f,                     m_fRange/2 * 100.0f);
    } else {
        // translate Word coords to pixels
        m_fProportionality = static_cast<GLfloat>(m_nGLWWidth) / m_fRange;
        m_dHWPropotion = double(m_nGLHeight) / double(m_nGLWWidth);
        m_qProjectMatrix.ortho(-m_fRange/2,                              m_fRange/2,
                               -m_fRange/2 * GLfloat ( m_dHWPropotion ), m_fRange/2 * GLfloat (m_dHWPropotion),
                               -m_fRange/2 * 100.0f,                     m_fRange/2 * 100.0f);
    }
    calculateBackGroundData();
    calculateReferenceTapData();
    qDebug()<<tr("has initializeContralMatix");
    return true;
}

bool GLWidget::initialTextTexture()
{
    // FreeType
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&m_ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    // Load font as face
    if (FT_New_Face(m_ft, "fonts/arial.ttf", 0, &m_face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }

    // Set size to load glyphs as
    FT_Set_Pixel_Sizes(m_face, 0, 48);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    for (GLubyte c = 0; c < 128; c++) {
        // Load character glyph
        if (FT_Load_Char(m_face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D( GL_TEXTURE_2D,
                      0,
                      GL_RED,
                      static_cast<GLsizei>(m_face->glyph->bitmap.width) ,
                      static_cast<GLsizei>(m_face->glyph->bitmap.rows) ,
                      0,
                      GL_RED,
                      GL_UNSIGNED_BYTE,
                      m_face->glyph->bitmap.buffer );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = { texture,
                                glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
                                glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
                                static_cast<GLuint>(m_face->glyph->advance.x) };
        m_CharactersMap.insert(std::pair<GLchar, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // Destroy FreeType once we're finished
    FT_Done_Face(m_face);
    FT_Done_FreeType(m_ft);
    // Configure VAO/VBO for texture quads
    m_pFunction->glGenVertexArrays(1, &m_uTextVAO);
    m_pFunction->glGenBuffers(1, &m_uTextVBO);
    m_pFunction->glBindVertexArray(m_uTextVAO);
    m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uTextVBO);
    m_pFunction->glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    m_pFunction->glEnableVertexAttribArray(0);
    m_pFunction->glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
    m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, 0);
    m_pFunction->glBindVertexArray(0);
    return true;
}

void GLWidget::resizeGL(GLint width, GLint height)
{
    // avoid casing the wididth < 2
    if(2 >= width) {
        m_nGLWWidth = 2;
        return;
    } else {
        m_nGLWWidth = width;
    }
    if (2 >= height) {
        m_nGLHeight = 2;
        return;
    } else {
        m_nGLHeight = height;
    }

    // set ArcBall size m_nGLWWidgth and m_nGLHeight must be bigger than 2
    m_pArcBallT->setBounds(static_cast<GLfloat>(m_nGLWWidth), static_cast<GLfloat>(m_nGLHeight));

    // instialize project matrix
    m_qProjectMatrix.setToIdentity();
    if (m_nGLWWidth > m_nGLHeight) {
        // translate Word coords to pixels
        m_fProportionality = static_cast<GLfloat>(m_nGLHeight) / m_fRange;
        m_dHWPropotion = double(m_nGLWWidth) / double(m_nGLHeight);    // gl the specific value between widget and height
        m_qProjectMatrix.ortho(-m_fRange / 2 * GLfloat ( m_dHWPropotion ), m_fRange / 2 * GLfloat (m_dHWPropotion),
                               -m_fRange / 2,                              m_fRange / 2,
                               -m_fRange / 2 * 100.0f,                     m_fRange / 2 * 100.0f);
    } else {
        // translate Word coords to pixels
        m_fProportionality = static_cast<GLfloat>(m_nGLWWidth) /  m_fRange;
        m_dHWPropotion = double(m_nGLHeight) / double(m_nGLWWidth);  // // gl the specific value between height and widget
        m_qProjectMatrix.ortho(-m_fRange / 2,                              m_fRange / 2,
                               -m_fRange / 2 * GLfloat ( m_dHWPropotion ), m_fRange / 2 * GLfloat (m_dHWPropotion),
                               -m_fRange / 2 * 100.0f,                     m_fRange / 2 * 100.0f);
    }

    if(m_pDepthBuffer != nullptr) {
        delete [] m_pDepthBuffer;
        m_pDepthBuffer = nullptr;
    }
    if (width * height > 0) {
        m_pDepthBuffer = new GLfloat[width * height];
    }

    // rebuild the vertext
    calculateReferenceTapData(true, false, false, false);
    calculateBackGroundData(true, false, false, false);
    update();
}

GLuint GLWidget::CreateProgram(const QString vertexPath, const QString fragmentPath)
{
    GLuint _uiShaderProagrm;

    std::string vertexCode;
    std::string fragmentCode;
    QFile _vShaderFile;
    QFile _fShaderFile;

    _vShaderFile.setFileName(vertexPath);
    _fShaderFile.setFileName(fragmentPath);

    if (_vShaderFile.open(QIODevice::ReadOnly|QIODevice::Text) &&
            _fShaderFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream _vShaderStream(&_vShaderFile);
        QTextStream _fShaderStream(&_fShaderFile);

        QString _vShaderString = _vShaderStream.readAll();
        QString _fShaderString = _fShaderStream.readAll();

        vertexCode = _vShaderString.toStdString();
        fragmentCode = _fShaderString.toStdString();
    }

    // get Vertex shader and the frag shader from the path file
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();

    // Build and compile our shader program
    // Vertex shader
    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Check for compile time errors
    GLint success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Fragment shader
    const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Check for compile time errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Link shaders
    _uiShaderProagrm = glCreateProgram();
    glAttachShader(_uiShaderProagrm, vertexShader);
    glAttachShader(_uiShaderProagrm, fragmentShader);
    glLinkProgram(_uiShaderProagrm);

    // Check for linking errors
    glGetProgramiv(_uiShaderProagrm, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_uiShaderProagrm, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return _uiShaderProagrm;
}

GLuint GLWidget::CreateProgram(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    GLuint _uiShaderProagrm;
    // read the vertex shader and frag shader
    std::string   vertexCode;
    std::string   fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // confirm that ifstream to shrow out the error：
    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);
    try{
        // Open File
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // read the buffer to the stream
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // close the files
        vShaderFile.close();
        fShaderFile.close();

        // translate the stream to the glchar*
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();

    // Build and compile our shader program
    // Vertex shader
    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    // Check for compile time errors
    GLint success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Fragment shader
    const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    // Check for compile time errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Link shaders
    _uiShaderProagrm = glCreateProgram();
    glAttachShader(_uiShaderProagrm, vertexShader);
    glAttachShader(_uiShaderProagrm, fragmentShader);
    glLinkProgram(_uiShaderProagrm);
    // Check for linking errors
    glGetProgramiv(_uiShaderProagrm, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_uiShaderProagrm, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return _uiShaderProagrm;
}

bool GLWidget::calculateReferenceTapData(const bool&& updateVertex_ ,
                                         const bool&& updateColor_ ,
                                         const bool&& updateNormal_ ,
                                         const bool&& updateIndex_)
{
    QVector<QVector3D> _colorVector;
    _colorVector.push_back( QVector3D(   0.0f,   0.0f, 255.0f ) / 255.0f );
    _colorVector.push_back( QVector3D(   0.0f, 178.0f, 255.0f ) / 255.0f );
    _colorVector.push_back( QVector3D(   0.0f, 255.0f, 255.0f ) / 255.0f );
    _colorVector.push_back( QVector3D(   0.0f, 255.0f, 178.0f ) / 255.0f );
    _colorVector.push_back( QVector3D(   0.0f, 255.0f,   0.0f ) / 255.0f );
    _colorVector.push_back( QVector3D( 178.0f, 255.0f,   0.0f ) / 255.0f );
    _colorVector.push_back( QVector3D( 255.0f, 255.0f,   0.0f ) / 255.0f );
    _colorVector.push_back( QVector3D( 255.0f, 178.0f,   0.0f ) / 255.0f );
    _colorVector.push_back( QVector3D( 255.0f,   0.0f,   0.0f ) / 255.0f );

    float _x;
    float _y;
    float _z = 0.1f;
    float _xRemove = 0;
    int _count = _colorVector.size();

    if ( updateVertex_ ) {
        if (m_nGLWWidth > m_nGLHeight) {
            // translate Word coords to pixels
            m_dHWPropotion = double(m_nGLWWidth) / double(m_nGLHeight);    // gl the specific value between widget and height
            _x = m_fRange/2 * GLfloat ( m_dHWPropotion );
            _y = m_fRange/2;
        } else {
            // translate Word coords to pixels
            m_dHWPropotion = double(m_nGLHeight) / double(m_nGLWWidth);  // gl the specific value between height and widget
            _x = m_fRange/2;
            _y = m_fRange/2 * GLfloat ( m_dHWPropotion );
        }

        _xRemove = 0.9f * _x;
        _x *= 0.005f; // change the tap size
        _y *= 0.9f; // change the tap size

        // clear all the data
        m_vReferenceTapeVertexs.clear();
        QVector<GLfloat>().swap(m_vReferenceTapeVertexs);

        // all the position
        float _step = (2*_y)/(_count-1);
        for ( int _i = 0; _i < _count; _i++ ) {
            m_vReferenceTapeVertexs.push_back(-_x + _xRemove);
            m_vReferenceTapeVertexs.push_back(_y - _step * _i);
            m_vReferenceTapeVertexs.push_back(_z);
        }
        for ( int _i = 0; _i < _count; _i++ ) {
            m_vReferenceTapeVertexs.push_back(_x + _xRemove);
            m_vReferenceTapeVertexs.push_back((-_y) + _step * _i);
            m_vReferenceTapeVertexs.push_back(_z);
        }
    }

    if ( updateNormal_ ) {
        m_vReferenceTapeNormal.clear();
        QVector<GLfloat>().swap(m_vReferenceTapeNormal);

        // all the colors
        for ( int _i = 0; _i < _count * 2; _i++) {
            m_vReferenceTapeNormal.push_back(0.0f);
            m_vReferenceTapeNormal.push_back(0.0f);
            m_vReferenceTapeNormal.push_back(1.0f);
        }
    }

    if ( updateColor_ ) {
        m_vReferenceTapeColors.clear();
        QVector<GLfloat>().swap(m_vReferenceTapeColors);

        // calculate all the colors
        for ( int _i = 0; _i < _count * 2; _i++) {
            if ( _i < _count ) {
                m_vReferenceTapeColors.push_back(_colorVector.at(_i).x());
                m_vReferenceTapeColors.push_back(_colorVector.at(_i).y());
                m_vReferenceTapeColors.push_back(_colorVector.at(_i).z());
            } else {
                m_vReferenceTapeColors.push_back(_colorVector.at(_count * 2 - _i -1).x());
                m_vReferenceTapeColors.push_back(_colorVector.at(_count * 2 - _i -1).y());
                m_vReferenceTapeColors.push_back(_colorVector.at(_count * 2 - _i -1).z());
            }
        }
    }

    if ( updateIndex_ ) {
        m_vReferenceTapeIndex.clear();
        QVector<GLuint>().swap(m_vReferenceTapeIndex);

        // all the index
//        for ( uint _i = 0; _i < static_cast<uint>(_count*2); _i++ ) {
//            m_vReferenceTapeIndex.push_back(_i);
//        }
        uint _ucount = static_cast<uint>(_count);
        for ( uint _i = 0; _i < static_cast<uint>(_ucount-1); _i++ ) {
            m_vReferenceTapeIndex.push_back(_i);
            m_vReferenceTapeIndex.push_back(_i+1);
            m_vReferenceTapeIndex.push_back(2*_ucount - 2 - _i);
            m_vReferenceTapeIndex.push_back(2*_ucount - 1 - _i);
        }
    }
    updateReferenceTapData(false, true, false, false, false);
    return true;
}

bool GLWidget::updateReferenceTapData(const bool&& updateVAO_ ,
                                      const bool&& updateVBO_ ,
                                      const bool&& updateCBO_ ,
                                      const bool&& updateNBO_,
                                      const bool&& updateEBO_ )
{
    if (m_vReferenceTapeVertexs.size() <= 0 ||
            m_vReferenceTapeNormal.size() <= 0 ||
            m_vReferenceTapeColors.size() <= 0 ||
            m_vReferenceTapeIndex.size() <= 0 ) {
        qDebug()<<tr("Error: Back Ground data is wrong!!");
        return false;
    }

    // delete all the background VAO
    if (m_pFunction->glIsVertexArray(m_uReferenceTapVAO)) {
        if ( updateVAO_ ) {
            m_pFunction->glDeleteVertexArrays(1, &m_uReferenceTapVAO);
            // gen all the back ground VAO
            m_pFunction->glGenVertexArrays(1, &m_uReferenceTapVAO);
        }
    } else {
        // gen all the back ground VAO
        m_pFunction->glGenVertexArrays(1, &m_uReferenceTapVAO);
    }
    // bing the VAO
    m_pFunction->glBindVertexArray(m_uReferenceTapVAO);

    // delete all the background VBO
    if (m_pFunction->glIsBuffer(m_uReferenceTapVBO)) {
        if ( updateVBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uReferenceTapVBO);
            m_pFunction->glGenBuffers(1, &m_uReferenceTapVBO);
            // gen all the back ground VBO
            m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uReferenceTapVBO);
            m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                      m_vReferenceTapeVertexs.size() * static_cast<int>(sizeof (GLfloat)),
                                      reinterpret_cast<GLfloat*>(&m_vReferenceTapeVertexs[0]), GL_STATIC_DRAW);
        }
    } else {
        m_pFunction->glGenBuffers(1, &m_uReferenceTapVBO);
        // gen all the back ground VBO
        m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uReferenceTapVBO);
        m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                  m_vReferenceTapeVertexs.size() * static_cast<int>(sizeof (GLfloat)),
                                  reinterpret_cast<GLfloat*>(&m_vReferenceTapeVertexs[0]), GL_STATIC_DRAW);
    }

    // delete all the background CBO
    if (m_pFunction->glIsBuffer(m_uReferenceTapCBO)) {
        if ( updateCBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uReferenceTapCBO);
            m_pFunction->glGenBuffers(1, &m_uReferenceTapCBO);
            // gen all the back ground CBO
            m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uReferenceTapCBO);
            m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                      m_vReferenceTapeColors.size() * static_cast<int>(sizeof (GLfloat)),
                                      reinterpret_cast<GLfloat*>(&m_vReferenceTapeColors[0]), GL_STATIC_DRAW);
        }
    } else {
        m_pFunction->glGenBuffers(1, &m_uReferenceTapCBO);
        // gen all the back ground CBO
        m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uReferenceTapCBO);
        m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                  m_vReferenceTapeColors.size() * static_cast<int>(sizeof (GLfloat)),
                                  reinterpret_cast<GLfloat*>(&m_vReferenceTapeColors[0]), GL_STATIC_DRAW);
    }

    // delete all the background NBO
    if (m_pFunction->glIsBuffer(m_uReferenceTapNBO)) {
        if ( updateNBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uReferenceTapNBO);
            m_pFunction->glGenBuffers(1, &m_uReferenceTapNBO);
            // gen all the background NBO
            m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uReferenceTapNBO);
            m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                      m_vReferenceTapeNormal.size() * static_cast<int>(sizeof(GLfloat)) ,
                                      reinterpret_cast<GLfloat*>(&m_vReferenceTapeNormal[0]), GL_STATIC_DRAW);
        }
    } else {
        m_pFunction->glGenBuffers(1, &m_uReferenceTapNBO);
        // gen all the background NBO
        m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uReferenceTapNBO);
        m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                  m_vReferenceTapeNormal.size() * static_cast<int>(sizeof(GLfloat)) ,
                                  reinterpret_cast<GLfloat*>(&m_vReferenceTapeNormal[0]), GL_STATIC_DRAW);
    }

    // delete all the back ground EBO
    if (m_pFunction->glIsBuffer(m_uReferenceTapEBO)) {
        if ( updateEBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uReferenceTapEBO);
            m_pFunction->glGenBuffers(1, &m_uReferenceTapEBO);

            // gen all the background EBO
            m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uReferenceTapEBO);
            m_pFunction->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                                      m_vReferenceTapeIndex.size() * static_cast<int>(sizeof(GLuint)) ,
                                      reinterpret_cast<GLuint*>(&m_vReferenceTapeIndex[0]), GL_STATIC_DRAW);
        }
    } else {
        m_pFunction->glGenBuffers(1, &m_uReferenceTapEBO);

        // gen all the background EBO
        m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uReferenceTapEBO);
        m_pFunction->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                                  m_vReferenceTapeIndex.size() * static_cast<int>(sizeof(GLuint)) ,
                                  reinterpret_cast<GLuint*>(&m_vReferenceTapeIndex[0]), GL_STATIC_DRAW);
    }

    m_pFunction->glBindVertexArray(0);
//    qDebug()<<tr("Success: update back ground buffer OK!");
    return true;
}


bool GLWidget::calculateBackGroundData(const bool&& updateVertex_ ,
                                       const bool&& updateColor_ ,
                                       const bool&& updateNormal_ ,
                                       const bool&& updateIndex_)
{
    float _x;
    float _y;
    float _z = -m_fRange / 2 * 100.0f;

    if ( updateVertex_ ) {
        if (m_nGLWWidth > m_nGLHeight) {
            // translate Word coords to pixels
            m_dHWPropotion = double(m_nGLWWidth) / double(m_nGLHeight);    // gl the specific value between widget and height
            _x = m_fRange/2 * GLfloat ( m_dHWPropotion );
            _y = m_fRange/2;
        } else {
            // translate Word coords to pixels
            m_dHWPropotion = double(m_nGLHeight) / double(m_nGLWWidth);  // gl the specific value between height and widget
            _x = m_fRange/2;
            _y = m_fRange/2 * GLfloat ( m_dHWPropotion );
        }

        m_vBackFaceVertexs.clear();
        QVector<GLfloat>().swap(m_vBackFaceVertexs);
        // all the point
        m_vBackFaceVertexs.push_back(-_x);
        m_vBackFaceVertexs.push_back(-_y);
        m_vBackFaceVertexs.push_back(_z);

        m_vBackFaceVertexs.push_back(_x);
        m_vBackFaceVertexs.push_back(-_y);
        m_vBackFaceVertexs.push_back(_z);

        m_vBackFaceVertexs.push_back(_x);
        m_vBackFaceVertexs.push_back(_y);
        m_vBackFaceVertexs.push_back(_z);

        m_vBackFaceVertexs.push_back(-_x);
        m_vBackFaceVertexs.push_back(_y);
        m_vBackFaceVertexs.push_back(_z);
    }

    if ( updateNormal_ ) {
        m_vBackFaceNormal.clear();
        QVector<GLfloat>().swap(m_vBackFaceNormal);
        // all the normal
        m_vBackFaceNormal.push_back(0.0f);
        m_vBackFaceNormal.push_back(0.0f);
        m_vBackFaceNormal.push_back(1.0f);

        m_vBackFaceNormal.push_back(0.0f);
        m_vBackFaceNormal.push_back(0.0f);
        m_vBackFaceNormal.push_back(1.0f);

        m_vBackFaceNormal.push_back(0.0f);
        m_vBackFaceNormal.push_back(0.0f);
        m_vBackFaceNormal.push_back(1.0f);

        m_vBackFaceNormal.push_back(0.0f);
        m_vBackFaceNormal.push_back(0.0f);
        m_vBackFaceNormal.push_back(1.0f);
    }

    if ( updateColor_ ) {
        m_vBackFaceColors.clear();
        QVector<GLfloat>().swap(m_vBackFaceColors);
        // all the color
        m_vBackFaceColors.push_back(0.05f);
        m_vBackFaceColors.push_back(0.02f);
        m_vBackFaceColors.push_back(0.50f);

        m_vBackFaceColors.push_back(0.05f);
        m_vBackFaceColors.push_back(0.02f);
        m_vBackFaceColors.push_back(0.50f);

        m_vBackFaceColors.push_back(0.80f);
        m_vBackFaceColors.push_back(0.80f);
        m_vBackFaceColors.push_back(0.80f);

        m_vBackFaceColors.push_back(0.80f);
        m_vBackFaceColors.push_back(0.80f);
        m_vBackFaceColors.push_back(0.80f);
    }

    if ( updateIndex_ ) {
        m_vBackFaceIndex.clear();
        QVector<GLuint>().swap(m_vBackFaceIndex);
        // all the index
        m_vBackFaceIndex.push_back(0);
        m_vBackFaceIndex.push_back(1);
        m_vBackFaceIndex.push_back(2);
        m_vBackFaceIndex.push_back(3);
    }
    updateBackGroundBuffer(false, true, false, false, false);
    return true;
}

bool GLWidget::updateBackGroundBuffer(const bool&& updateVAO_ ,
                                      const bool&& updateVBO_ ,
                                      const bool&& updateCBO_ ,
                                      const bool&& updateNBO_,
                                      const bool&& updateEBO_ )
{
    if (m_vBackFaceVertexs.size() <= 0 ||
            m_vBackFaceNormal.size() <= 0 ||
            m_vBackFaceColors.size() <= 0 ||
            m_vBackFaceIndex.size() <= 0 ) {
        qDebug()<<tr("Error: Back Ground data is wrong!!");
        return false;
    }

    // delete all the background VAO
    if (m_pFunction->glIsVertexArray(m_uBackGroundVAO)) {
        if ( updateVAO_ ) {
            m_pFunction->glDeleteVertexArrays(1, &m_uBackGroundVAO);
             // gen all the back ground VAO
            m_pFunction->glGenVertexArrays(1, &m_uBackGroundVAO);
        }
    } else {
        // gen all the back ground VAO
        m_pFunction->glGenVertexArrays(1, &m_uBackGroundVAO);
    }
    // bing the VAO
    m_pFunction->glBindVertexArray(m_uBackGroundVAO);

    // delete all the background VBO
    if (m_pFunction->glIsBuffer(m_uBackGroundVBO)) {
        if ( updateVBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uBackGroundVBO);
            m_pFunction->glGenBuffers(1, &m_uBackGroundVBO);
            // gen all the back ground VBO
            m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uBackGroundVBO);
            m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                      m_vBackFaceVertexs.size() * static_cast<int>(sizeof (GLfloat)),
                                      reinterpret_cast<GLfloat*>(&m_vBackFaceVertexs[0]), GL_STATIC_DRAW);
        }
    } else {
        m_pFunction->glGenBuffers(1, &m_uBackGroundVBO);
        // gen all the back ground VBO
        m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uBackGroundVBO);
        m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                  m_vBackFaceVertexs.size() * static_cast<int>(sizeof (GLfloat)),
                                  reinterpret_cast<GLfloat*>(&m_vBackFaceVertexs[0]), GL_STATIC_DRAW);
    }

    // delete all the background CBO
    if (m_pFunction->glIsBuffer(m_uBackGroundCBO)) {
        if ( updateCBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uBackGroundCBO);
            m_pFunction->glGenBuffers(1, &m_uBackGroundCBO);
            // gen all the back ground CBO
            m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uBackGroundCBO);
            m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                      m_vBackFaceColors.size() * static_cast<int>(sizeof (GLfloat)),
                                      reinterpret_cast<GLfloat*>(&m_vBackFaceColors[0]), GL_STATIC_DRAW);
        }
    } else {
        m_pFunction->glGenBuffers(1, &m_uBackGroundCBO);
        // gen all the back ground CBO
        m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uBackGroundCBO);
        m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                  m_vBackFaceColors.size() * static_cast<int>(sizeof (GLfloat)),
                                  reinterpret_cast<GLfloat*>(&m_vBackFaceColors[0]), GL_STATIC_DRAW);
    }

    // delete all the background NBO
    if (m_pFunction->glIsBuffer(m_uBackGroundNBO)) {
        if ( updateNBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uBackGroundNBO);
            m_pFunction->glGenBuffers(1, &m_uBackGroundNBO);
            // gen all the background NBO
            m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uBackGroundNBO);
            m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                      m_vBackFaceNormal.size() * static_cast<int>(sizeof(GLfloat)) ,
                                      reinterpret_cast<GLfloat*>(&m_vBackFaceNormal[0]), GL_STATIC_DRAW);
        }
    } else {
        m_pFunction->glGenBuffers(1, &m_uBackGroundNBO);
        // gen all the background NBO
        m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uBackGroundNBO);
        m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                  m_vBackFaceNormal.size() * static_cast<int>(sizeof(GLfloat)) ,
                                  reinterpret_cast<GLfloat*>(&m_vBackFaceNormal[0]), GL_STATIC_DRAW);
    }

    // delete all the back ground EBO
    if (m_pFunction->glIsBuffer(m_uBackGroundEBO)) {
        if ( updateEBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uBackGroundEBO);
            m_pFunction->glGenBuffers(1, &m_uBackGroundEBO);

            // gen all the background EBO
            m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uBackGroundEBO);
            m_pFunction->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                                      m_vBackFaceIndex.size() * static_cast<int>(sizeof(GLuint)) ,
                                      reinterpret_cast<GLuint*>(&m_vBackFaceIndex[0]), GL_STATIC_DRAW);
        }
    } else {
        m_pFunction->glGenBuffers(1, &m_uBackGroundEBO);

        // gen all the background EBO
        m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uBackGroundEBO);
        m_pFunction->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                                  m_vBackFaceIndex.size() * static_cast<int>(sizeof(GLuint)) ,
                                  reinterpret_cast<GLuint*>(&m_vBackFaceIndex[0]), GL_STATIC_DRAW);
    }

    m_pFunction->glBindVertexArray(0);
//    qDebug()<<tr("Success: update back ground buffer OK!");
    return true;
}

bool GLWidget::updateVertexsBuffer(const bool &&updateVAO_,
                                   const bool &&updateVBO_,
                                   const bool &&updateCBO_,
                                   const bool &&updateEBO_)
{
    // Prevent subscripts from crossing the border
    if ( m_vVertexs.size() <= 0 ||
         m_vVertexsColor.size() <= 0 ||
         m_vVertexsIndex.size() <= 0 ) {
        return false;
    }
    // delete all Vertexs VAO
    if(m_pFunction->glIsVertexArray(m_uVertexsVAO)) {
        if ( updateVAO_ ) {
            m_pFunction->glDeleteVertexArrays(1, &m_uVertexsVAO);
            // gen the Vertexs VAO
            m_pFunction->glGenVertexArrays(1, &m_uVertexsVAO);
        }
    } else {
        // gen the Vertexs VAO
        m_pFunction->glGenVertexArrays(1, &m_uVertexsVAO);
    }
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    m_pFunction->glBindVertexArray(m_uVertexsVAO);

    // delete all Vertexs VBO
    if (m_pFunction->glIsBuffer(m_uVertexsVBO)) {
        if ( updateVBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uVertexsVBO);
            // gen the Vertexs VBO
            m_pFunction->glGenBuffers(1, &m_uVertexsVBO);
            // copy the ROM to the GPU buffur
            m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uVertexsVBO);
            m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                      m_vVertexs.size() * static_cast<int>(sizeof (GLfloat)),
                                      reinterpret_cast<GLfloat*>(&m_vVertexs[0]), GL_STATIC_DRAW);
        }
    } else {
        // gen the Vertexs VBO
        m_pFunction->glGenBuffers(1, &m_uVertexsVBO);
        // copy the ROM to the GPU buffur
        m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uVertexsVBO);
        m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                  m_vVertexs.size() * static_cast<int>(sizeof (GLfloat)),
                                  reinterpret_cast<GLfloat*>(&m_vVertexs[0]), GL_STATIC_DRAW);
    }

    // delete all Vertexs CBO
    if (m_pFunction->glIsBuffer(m_uVertexsCBO)) {
        if ( updateCBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uVertexsCBO);
            // gen the Vertexs CBO
            m_pFunction->glGenBuffers(1, &m_uVertexsCBO);
            m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uVertexsCBO);
            m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                      m_vVertexsColor.size() * static_cast<int>(sizeof (GLfloat)),
                                      reinterpret_cast<GLfloat*>(&m_vVertexsColor[0]), GL_STATIC_DRAW);
        }
    } else {
        // gen the Vertexs CBO
        m_pFunction->glGenBuffers(1, &m_uVertexsCBO);
        m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uVertexsCBO);
        m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                  m_vVertexsColor.size() * static_cast<int>(sizeof (GLfloat)),
                                  reinterpret_cast<GLfloat*>(&m_vVertexsColor[0]), GL_STATIC_DRAW);
    }

    // delete all Vertexs EBO
    if (m_pFunction->glIsBuffer(m_uVertexsEBO)) {
        if ( updateEBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uVertexsEBO);
            // the Vertexs index buffur
            m_pFunction->glGenBuffers(1, &m_uVertexsEBO);
            m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uVertexsEBO);
            m_pFunction->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                                      m_vVertexsIndex.size() * static_cast<int>(sizeof(GLuint)) ,
                                      reinterpret_cast<GLuint*>(&m_vVertexsIndex[0]), GL_STATIC_DRAW);
        }
    } else {
        // the Vertexs index buffur
        m_pFunction->glGenBuffers(1, &m_uVertexsEBO);
        m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uVertexsEBO);
        m_pFunction->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                                  m_vVertexsIndex.size() * static_cast<int>(sizeof(GLuint)) ,
                                  reinterpret_cast<GLuint*>(&m_vVertexsIndex[0]), GL_STATIC_DRAW);
    }
    m_pFunction->glBindVertexArray(0);
    return true;
}

bool GLWidget::updateLinesBuffer(const bool&& updateVAO_,
                                 const bool&& updateVBO_,
                                 const bool&& updateCBO_,
                                 const bool&& updateEBO_)
{
    // Prevent subscripts from crossing the border
    if ( m_vLineVertexs.size() <= 0 ||
         m_vLineColor.size() <= 0 ||
         m_vLineIndex.size() <= 0 ) {
        return false;
    }
    // delete all Vertexs VAO
    if(m_pFunction->glIsVertexArray(m_uLinesVAO)) {
        if ( updateVAO_ ) {
            m_pFunction->glDeleteVertexArrays(1, &m_uLinesVAO);
            // gen the Vertexs VAO
            m_pFunction->glGenVertexArrays(1, &m_uLinesVAO);
        } else {
            m_pFunction->glDeleteVertexArrays(1, &m_uLinesVAO);
            // gen the Vertexs VAO
            m_pFunction->glGenVertexArrays(1, &m_uLinesVAO);
        }
    }
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    m_pFunction->glBindVertexArray(m_uLinesVAO);

    // delete all Vertexs VBO
    if (m_pFunction->glIsBuffer(m_uLinesVBO)) {
        if ( updateVBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uLinesVBO);
            // gen the Vertexs VBO
            m_pFunction->glGenBuffers(1, &m_uLinesVBO);
            // copy the ROM to the GPU buffur
            m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uLinesVBO);
            m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                      m_vLineVertexs.size() * static_cast<int>(sizeof (GLfloat)),
                                      reinterpret_cast<GLfloat*>(&m_vLineVertexs[0]), GL_STATIC_DRAW);
        }
    } else {
        // gen the Vertexs VBO
        m_pFunction->glGenBuffers(1, &m_uLinesVBO);
        // copy the ROM to the GPU buffur
        m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uLinesVBO);
        m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                  m_vLineVertexs.size() * static_cast<int>(sizeof (GLfloat)),
                                  reinterpret_cast<GLfloat*>(&m_vLineVertexs[0]), GL_STATIC_DRAW);
    }

    // delete all Vertexs CBO
    if (m_pFunction->glIsBuffer(m_uLinesCBO)) {
        if ( updateCBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uLinesCBO);
            // gen the Vertexs CBO
            m_pFunction->glGenBuffers(1, &m_uLinesCBO);
            m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uLinesCBO);
            m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                      m_vLineColor.size() * static_cast<int>(sizeof (GLfloat)),
                                      reinterpret_cast<GLfloat*>(&m_vLineColor[0]), GL_STATIC_DRAW);
        }
    } else {
        // gen the Vertexs CBO
        m_pFunction->glGenBuffers(1, &m_uLinesCBO);
        m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uLinesCBO);
        m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                  m_vLineColor.size() * static_cast<int>(sizeof (GLfloat)),
                                  reinterpret_cast<GLfloat*>(&m_vLineColor[0]), GL_STATIC_DRAW);
    }
    // delete all Vertexs EBO
    if (m_pFunction->glIsBuffer(m_uLinesEBO)) {
        if ( updateEBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uLinesEBO);
            // the Vertexs index buffur
            m_pFunction->glGenBuffers(1, &m_uLinesEBO);
            m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uLinesEBO);
            m_pFunction->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                                      m_vLineIndex.size() * static_cast<int>(sizeof(GLuint)) ,
                                      reinterpret_cast<GLuint*>(&m_vLineIndex[0]), GL_STATIC_DRAW);
        }
    } else {
        // the Vertexs index buffur
        m_pFunction->glGenBuffers(1, &m_uLinesEBO);
        m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uLinesEBO);
        m_pFunction->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                                  m_vLineIndex.size() * static_cast<int>(sizeof(GLuint)) ,
                                  reinterpret_cast<GLuint*>(&m_vLineIndex[0]), GL_STATIC_DRAW);
    }
    m_pFunction->glBindVertexArray(0);
    return true;
}

bool GLWidget::updateTrianglesBuffer(const bool&& updateVAO_,
                                     const bool&& updateVBO_,
                                     const bool&& updateCBO_,
                                     const bool&& updateNBO_,
                                     const bool&& updateEBO_)
{
    if ( m_vTrianglesVertexs.size() <= 0 ||
         m_vTrianglesColor.size() <= 0 ||
         m_vTrianglesNormal.size()<= 0 ||
         m_vTriangleIndex.size()<= 0 ) {
        return false;
    }
    // delete all Quads  VAO
    if(m_pFunction->glIsVertexArray(m_uTrianglesVAO)) {
        if ( updateVAO_ ) {
            m_pFunction->glDeleteVertexArrays(1, &m_uTrianglesVAO);
            // gen the m_uTrianglesVAO
            m_pFunction->glGenVertexArrays(1, &m_uTrianglesVAO);
        }
    } else {
        // gen the m_uTrianglesVAO
        m_pFunction->glGenVertexArrays(1, &m_uTrianglesVAO);
    }
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    m_pFunction->glBindVertexArray(m_uTrianglesVAO);

    // delete all Quads VBO
    if (m_pFunction->glIsBuffer(m_uTrianglesVBO)) {
        if ( updateVBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uTrianglesVBO);
            // gen the VBO
            m_pFunction->glGenBuffers(1, &m_uTrianglesVBO);
            // copy the ROM to the GPU buffur
            m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uTrianglesVBO);
            m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                      m_vTrianglesVertexs.size() * static_cast<int>(sizeof (GLfloat)),
                                      reinterpret_cast<GLfloat*>(&m_vTrianglesVertexs[0]), GL_STATIC_DRAW);
        }
    } else {
        // gen the VBO
        m_pFunction->glGenBuffers(1, &m_uTrianglesVBO);
        // copy the ROM to the GPU buffur
        m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uTrianglesVBO);
        m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                  m_vTrianglesVertexs.size() * static_cast<int>(sizeof (GLfloat)),
                                  reinterpret_cast<GLfloat*>(&m_vTrianglesVertexs[0]), GL_STATIC_DRAW);
    }

    // delete all Quads CBO
    if (m_pFunction->glIsBuffer(m_uTrianglesCBO)) {
        if ( updateCBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uTrianglesCBO);
            // gen the CBO
            m_pFunction->glGenBuffers(1, &m_uTrianglesCBO);
            m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uTrianglesCBO);
            m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                      m_vTrianglesColor.size() * static_cast<int>(sizeof (GLfloat)),
                                      reinterpret_cast<GLfloat*>(&m_vTrianglesColor[0]), GL_STATIC_DRAW);
        }

    } else {
        // gen the CBO
        m_pFunction->glGenBuffers(1, &m_uTrianglesCBO);
        m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uTrianglesCBO);
        m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                  m_vTrianglesColor.size() * static_cast<int>(sizeof (GLfloat)),
                                  reinterpret_cast<GLfloat*>(&m_vTrianglesColor[0]), GL_STATIC_DRAW);
    }

    // delete all Quads NBO
    if (m_pFunction->glIsBuffer(m_uTrianglesNBO)) {
        if ( updateNBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uTrianglesNBO);
            // gen the NBO
            m_pFunction->glGenBuffers(1, &m_uTrianglesNBO);
            m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uTrianglesNBO);
            m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                      m_vTrianglesNormal.size() * static_cast<int>(sizeof (GLfloat)),
                                      reinterpret_cast<GLfloat*>(&m_vTrianglesNormal[0]), GL_STATIC_DRAW);
        }
    } else {
        // gen the NBO
        m_pFunction->glGenBuffers(1, &m_uTrianglesNBO);
        m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uTrianglesNBO);
        m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                  m_vTrianglesNormal.size() * static_cast<int>(sizeof (GLfloat)),
                                  reinterpret_cast<GLfloat*>(&m_vTrianglesNormal[0]), GL_STATIC_DRAW);
    }
    // delete all Quads EBO
    if (m_pFunction->glIsBuffer(m_uTrianglesEBO)) {
        if ( updateEBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uTrianglesEBO);
            // the Quad index buffur
            m_pFunction->glGenBuffers(1, &m_uTrianglesEBO);
            m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uTrianglesEBO);
            m_pFunction->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                                      m_vTriangleIndex.size() * static_cast<int>(sizeof(GLuint)) ,
                                      reinterpret_cast<GLuint*>(&m_vTriangleIndex[0]), GL_STATIC_DRAW);
        }
    } else {
        // the Quad index buffur
        m_pFunction->glGenBuffers(1, &m_uTrianglesEBO);
        m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uTrianglesEBO);
        m_pFunction->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                                  m_vTriangleIndex.size() * static_cast<int>(sizeof(GLuint)) ,
                                  reinterpret_cast<GLuint*>(&m_vTriangleIndex[0]), GL_STATIC_DRAW);
    }

    m_pFunction->glBindVertexArray(0);
    return true;
}

bool GLWidget::updateQuadsBuffer(const bool&& updateVAO_,
                                 const bool&& updateVBO_,
                                 const bool&& updateCBO_,
                                 const bool&& updateNBO_,
                                 const bool&& updateEBO_)
{
    if ( m_vQuadsVertexs.size() <= 0 ||
         m_vQuadsColor.size() <= 0 ||
         m_vQuadsNormal.size() <= 0 ||
         m_vQuadsIndex.size() <= 0 ) {
        return false;
    }

    // delete all Quads  VAO
    if(m_pFunction->glIsVertexArray(m_uQuadsVAO)) {
        if ( updateVAO_ ) {
            m_pFunction->glDeleteVertexArrays(1, &m_uQuadsVAO);
            // gen the m_uQuadsVAO
            m_pFunction->glGenVertexArrays(1, &m_uQuadsVAO);
        }
    } else {
        // gen the m_uQuadsVAO
        m_pFunction->glGenVertexArrays(1, &m_uQuadsVAO);
    }
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    m_pFunction->glBindVertexArray(m_uQuadsVAO);

    // delete all Quads VBO
    if (m_pFunction->glIsBuffer(m_uQuadsVBO)) {
        if ( updateVBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uQuadsVBO);
            // gen the VBO
            m_pFunction->glGenBuffers(1, &m_uQuadsVBO);
            // copy the ROM to the GPU buffur
            m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uQuadsVBO);
            m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                      m_vQuadsVertexs.size() * static_cast<int>(sizeof (GLfloat)),
                                      reinterpret_cast<GLfloat*>(&m_vQuadsVertexs[0]), GL_STATIC_DRAW);
        }
    } else {
        // gen the VBO
        m_pFunction->glGenBuffers(1, &m_uQuadsVBO);
        // copy the ROM to the GPU buffur
        m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uQuadsVBO);
        m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                  m_vQuadsVertexs.size() * static_cast<int>(sizeof (GLfloat)),
                                  reinterpret_cast<GLfloat*>(&m_vQuadsVertexs[0]), GL_STATIC_DRAW);
    }

    // delete all Quads CBO
    if (m_pFunction->glIsBuffer(m_uQuadsCBO)) {
        if ( updateCBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uQuadsCBO);
            // gen the CBO
            m_pFunction->glGenBuffers(1, &m_uQuadsCBO);
            m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uQuadsCBO);
            m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                      m_vQuadsColor.size() * static_cast<int>(sizeof (GLfloat)),
                                      reinterpret_cast<GLfloat*>(&m_vQuadsColor[0]), GL_STATIC_DRAW);
        }
    } else {
        // gen the CBO
        m_pFunction->glGenBuffers(1, &m_uQuadsCBO);
        m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uQuadsCBO);
        m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                  m_vQuadsColor.size() * static_cast<int>(sizeof (GLfloat)),
                                  reinterpret_cast<GLfloat*>(&m_vQuadsColor[0]), GL_STATIC_DRAW);
    }

    // delete all Quads NBO
    if (m_pFunction->glIsBuffer(m_uQuadsNBO)) {
        if ( updateNBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uQuadsNBO);
            // gen the NBO
            m_pFunction->glGenBuffers(1, &m_uQuadsNBO);
            m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uQuadsNBO);
            m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                      m_vQuadsNormal.size() * static_cast<int>(sizeof (GLfloat)),
                                      reinterpret_cast<GLfloat*>(&m_vQuadsNormal[0]), GL_STATIC_DRAW);
        }
    } else {
        // gen the NBO
        m_pFunction->glGenBuffers(1, &m_uQuadsNBO);
        m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uQuadsNBO);
        m_pFunction->glBufferData(GL_ARRAY_BUFFER,
                                  m_vQuadsNormal.size() * static_cast<int>(sizeof (GLfloat)),
                                  reinterpret_cast<GLfloat*>(&m_vQuadsNormal[0]), GL_STATIC_DRAW);
    }

    // delete all Quads EBO
    if (m_pFunction->glIsBuffer(m_uQuadsEBO)) {
        if ( updateEBO_ ) {
            m_pFunction->glDeleteBuffers(1, &m_uQuadsEBO);
            // the Quad index buffur
            m_pFunction->glGenBuffers(1, &m_uQuadsEBO);
            m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uQuadsEBO);
            m_pFunction->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                                      m_vQuadsIndex.size() * static_cast<int>(sizeof(GLuint)) ,
                                      reinterpret_cast<GLuint*>(&m_vQuadsIndex[0]), GL_STATIC_DRAW);
        }
    } else {
        // the Quad index buffur
        m_pFunction->glGenBuffers(1, &m_uQuadsEBO);
        m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uQuadsEBO);
        m_pFunction->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                                  m_vQuadsIndex.size() * static_cast<int>(sizeof(GLuint)) ,
                                  reinterpret_cast<GLuint*>(&m_vQuadsIndex[0]), GL_STATIC_DRAW);
    }

    /*****************************************************************************************************************
     * this mode is gen all the buffer, then separate buffur as vertex and color
     * ***************************************************************************************************************/
//    m_pFunction->glBufferData(GL_ARRAY_BUFFER,
//                              (m_vVertexs.size() + m_vVertexsColor.size()) * static_cast<int>(sizeof (GLfloat)),
//                              nullptr, GL_STATIC_DRAW);

//    m_pFunction->glBufferSubData(GL_ARRAY_BUFFER,
//                                 0,
//                                 m_vVertexs.size() * static_cast<int>(sizeof (GLfloat)),
//                                 reinterpret_cast<GLfloat*>(&m_vVertexs[0]));

//    m_pFunction->glBufferSubData(GL_ARRAY_BUFFER,
//                                 m_vVertexs.size() * static_cast<int>(sizeof (GLfloat)),
//                                 m_vVertexsColor.size() * static_cast<int>(sizeof (GLfloat)),
//                                 reinterpret_cast<GLfloat*>(&m_vVertexsColor[0]));

//    // the Point index buffur
//    m_pFunction->glGenBuffers(1, &m_uPointEBO);
//    m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uPointEBO);
//    m_pFunction->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
//                              m_vVertexsIndex.size() * static_cast<int>(sizeof(GLuint)) ,
//                              reinterpret_cast<GLuint*>(&m_vVertexsIndex[0]), GL_STATIC_DRAW);

    m_pFunction->glBindVertexArray(0);
    return true;
}

bool GLWidget::updateBuffer() {
    updateVertexsBuffer();
    updateLinesBuffer();
    updateTrianglesBuffer();
    updateQuadsBuffer();
    m_bUpdateBuffer = true;  // the flag of flush buffer
    initializeContralMatrix(); // initialize all the matrix
    return true;
}

void GLWidget::swapData(const QVector3D& vCenter_, // the center of the model
                        const GLfloat& fRange_,  // the range of the model
                        QVector<GLfloat>* vVertexs_, // the point array
                        QVector<GLfloat>* vVertexsColor_, // the point color
                        QVector<GLuint>* vVertexsIndex_, // the point index
                        QVector<GLfloat>* vLineVertexs_, // the line point array
                        QVector<GLfloat>* vLineVertexsColor_, // the line point color
                        QVector<GLfloat>* vLineVertexsNormal_, // the line point normal
                        QVector<GLuint>* vLineVertexsIndex_, // the line index
                        QVector<GLfloat>* vTriangleVertexs_, // the triangle point array
                        QVector<GLfloat>* vTriangleVertexsColor_, // the triangle point color
                        QVector<GLfloat>* vTriangleVertexsNormal_, // the triangle point normal
                        QVector<GLuint>* vTriangleVertexsIndex_, // the triangle index
                        QVector<GLfloat>* vQuadVertexs_, // the quad point array
                        QVector<GLfloat>* vQuadVertexsColor_, // the quad point color
                        QVector<GLfloat>* vQuadVertexsNormal_, // the quad point normal
                        QVector<GLuint>* vQuadVertexsIndex_) // the quad index
{
    m_vCenter =vCenter_;
    m_fRange =  fRange_;

    // update the vertexs date
    if (vVertexs_ != nullptr){
        m_vVertexs.swap(*vVertexs_);
    }
    if ( vVertexsColor_ != nullptr ) {
        m_vVertexsColor.swap(*vVertexsColor_);
    }
    if ( vVertexsIndex_ != nullptr ) {
        m_vVertexsIndex.swap(*vVertexsIndex_);
    }

    // update the lines date
    if ( vLineVertexs_ != nullptr ) {
        m_vLineVertexs.swap(*vLineVertexs_);
    }
    if ( vLineVertexsNormal_ != nullptr ){
        m_vLineNormal.swap(*vLineVertexsNormal_);
    }
    if ( vLineVertexsColor_ != nullptr ){
        m_vLineColor.swap(*vLineVertexsColor_);
    }
    if ( vLineVertexsIndex_ != nullptr ){
        m_vLineIndex.swap(*vLineVertexsIndex_);
    }

    // update triangle date
    if ( vTriangleVertexs_ != nullptr ){
        m_vTrianglesVertexs.swap(*vTriangleVertexs_);
    }
    if ( vTriangleVertexsColor_ != nullptr ){
        m_vTrianglesColor.swap(*vTriangleVertexsColor_);
    }
    if ( vTriangleVertexsNormal_ != nullptr ){
        m_vTrianglesNormal.swap(*vTriangleVertexsNormal_);
    }
    if ( vTriangleVertexsIndex_ != nullptr ){
        m_vTriangleIndex.swap(*vTriangleVertexsIndex_);
    }

    // update qude date
    if ( vQuadVertexs_ != nullptr ){
        m_vQuadsVertexs.swap(*vQuadVertexs_);
    }
    if ( vQuadVertexsColor_ != nullptr ){
        m_vQuadsColor.swap(*vQuadVertexsColor_);
    }
    if ( vQuadVertexsNormal_ != nullptr ){
        m_vQuadsNormal.swap(*vQuadVertexsNormal_);
    }
    if ( vQuadVertexsIndex_!= nullptr ){
        m_vQuadsIndex.swap(*vQuadVertexsIndex_);
    }

#ifdef QT_DEBUG   // if it is debug model, it will output
    qDebug()<<"***********************************************************";
    qDebug()<<"***************All The Render Size*************************";
    qDebug()<<"                 Range:"<<m_fRange;
    qDebug()<<"                Center:"<<m_vCenter;
    qDebug()<<"    Vertexs       Size:"<<m_vVertexs.size();
    qDebug()<<"    Vertexs Color Size:"<<m_vVertexsColor.size();
    qDebug()<<"    Vertexs Index Size:"<<m_vVertexsIndex.size();

    qDebug()<<"     Lines Vertex Size:"<<m_vLineVertexs.size();
    qDebug()<<"     Lines Color  Size:"<<m_vLineColor.size();
    qDebug()<<"     Lines Normal Size:"<<m_vLineNormal.size();
    qDebug()<<"     Lines Indes  Size:"<<m_vLineIndex.size();

    qDebug()<<"Triangles Vertexs Size:"<<m_vTrianglesVertexs.size();
    qDebug()<<"Triangles Colors  Size:"<<m_vTrianglesColor.size();
    qDebug()<<"Triangles Normal  Size:"<<m_vTrianglesNormal.size();
    qDebug()<<"Triangles Index   Size:"<<m_vTriangleIndex.size();

    qDebug()<<"    Quads Vertexs Size:"<<m_vQuadsVertexs.size();
    qDebug()<<"    Quads Colors  Size:"<<m_vQuadsColor.size();
    qDebug()<<"    Quads Normal  Size:"<<m_vQuadsNormal.size();
    qDebug()<<"    Quads Index   Size:"<<m_vQuadsIndex.size();
    qDebug()<<"***********************************************************"<<'\n'<<'\n';
#endif

    updateBuffer();  // update data to buffer

    repaint();
}

void GLWidget::setGLCoordsRangle(const GLfloat range_)
{
    m_fRange = range_;
}

void GLWidget::switchTransparency()
{
//    if (m_bTransparency) {
//        m_pFunction->glEnable(GL_BLEND);
////        m_pFunction->glDisable(GL_DEPTH_TEST);   // if you use GL_BLEND you need to disable Depth test
//    }
//    else {
//        m_pFunction->glDisable(GL_BLEND);
////        m_pFunction->glEnable(GL_DEPTH_TEST);   // if you use GL_BLEND you need to disable Depth test
//    }
    m_bTransparency = !m_bTransparency;
    qDebug()<<tr(" switch Transparency ");
    this->update();
}

bool GLWidget::DrawBackGroundCall()
{
    // set draw mode
    m_pFunction->glBindVertexArray(m_uBackGroundVAO);   // all the point
    // Position attribute start from the nullptr transfer the buffur to vertex shader
    m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uBackGroundVBO);
    m_pFunction->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat),
                                       static_cast<GLvoid*>(nullptr));
    m_pFunction->glEnableVertexAttribArray(0);

    // Color attribute transfer the buffer to vertex shader
    m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uBackGroundCBO);
    m_pFunction->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat),
                                       static_cast<GLvoid*>(nullptr));
    m_pFunction->glEnableVertexAttribArray(1);

    // normal attribute transfer the buffer to vertex shader
    m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uBackGroundNBO);
    m_pFunction->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat),
                                       static_cast<GLvoid*>(nullptr));
    m_pFunction->glEnableVertexAttribArray(2);

    // use DrawElement draw element
    m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uBackGroundEBO);   // all the index
    m_pFunction->glDrawElements(GL_QUADS, m_vBackFaceIndex.size(), GL_UNSIGNED_INT, nullptr);

    // disbin the buffer
    m_pFunction->glBindVertexArray(0);
    return true;
}

bool GLWidget::DrawBackGround()
{
    m_pFunction->glUseProgram(m_uiBackgroundShader);

    // set shader light variable value
    m_pFunction->glUniform3f(m_iBackColor, 0.0f, 0.3176470588235294f, 0.9058823529411765f);
    m_pFunction->glUniform3f(m_iBackLightColor, 1.0f, 1.0f, 1.0f);
    m_pFunction->glUniform3f(m_iBackLightPos, 20*m_fRange, 30*m_fRange, 150*m_fRange);
    m_pFunction->glUniform3f(m_iBackViewPos, 0*m_fRange, 0*m_fRange, 100*m_fRange);

    DrawBackGroundCall();

    m_pFunction->glUseProgram(0);
    return true;
}

bool GLWidget::DrawReferenceTap()
{
    m_pFunction->glUseProgram(m_uiBackgroundShader);
    // if it doesn't hava mesh,it will not need offset
    GLint objectColorLoc = glGetUniformLocation(m_uiBackgroundShader, "objectColor");
    GLint lightColorLoc = glGetUniformLocation(m_uiBackgroundShader, "lightColor");
    GLint lightPosLoc = glGetUniformLocation(m_uiBackgroundShader, "lightPos");
    GLint viewPosLoc = glGetUniformLocation(m_uiBackgroundShader, "viewPos");

    // set shader light variable value
    m_pFunction->glUniform3f(objectColorLoc, 0.0f, 0.3176470588235294f, 0.9058823529411765f);
    m_pFunction->glUniform3f(lightColorLoc, 0.7f, 0.7f, 0.7f);
    m_pFunction->glUniform3f(lightPosLoc, 20*m_fRange, 30*m_fRange, 150*m_fRange);
    m_pFunction->glUniform3f(viewPosLoc, 0*m_fRange, 0*m_fRange, 100*m_fRange);

    // get the locale of the value from the shader
    const GLint _model_Loc = glGetUniformLocation(m_uiBackgroundShader, "model");
    const GLint _view_Loc  = glGetUniformLocation(m_uiBackgroundShader, "view");
    const GLint _project_Loc = glGetUniformLocation(m_uiBackgroundShader, "projection");

    // set the value of the shader program
    const QMatrix4x4 _Trianglematrx = m_qBackGroundMatrix;
    m_pFunction->glUniformMatrix4fv(_model_Loc, 1, GL_FALSE, _Trianglematrx.data());
    m_pFunction->glUniformMatrix4fv(_view_Loc, 1, GL_FALSE, m_qViewMatrix.data() );
    m_pFunction->glUniformMatrix4fv(_project_Loc, 1, GL_FALSE, m_qProjectMatrix.data());

    // set draw mode
    m_pFunction->glBindVertexArray(m_uReferenceTapVAO);   // all the point
    // Position attribute start from the nullptr transfer the buffur to vertex shader
    m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uReferenceTapVBO);
    m_pFunction->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat),
                                       static_cast<GLvoid*>(nullptr));
    m_pFunction->glEnableVertexAttribArray(0);

    // Color attribute transfer the buffer to vertex shader
    m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uReferenceTapCBO);
    m_pFunction->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat),
                                       static_cast<GLvoid*>(nullptr));
    m_pFunction->glEnableVertexAttribArray(1);

    // normal attribute transfer the buffer to vertex shader
    m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uReferenceTapNBO);
    m_pFunction->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat),
                                       static_cast<GLvoid*>(nullptr));
    m_pFunction->glEnableVertexAttribArray(2);

    // use DrawElement draw element
    m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uReferenceTapEBO);   // all the index
    m_pFunction->glDrawElements(GL_QUADS, m_vReferenceTapeIndex.size(), GL_UNSIGNED_INT, nullptr);

    // disbin the buffer
    m_pFunction->glBindVertexArray(0);
    m_pFunction->glUseProgram(0);
    return true;
}

bool GLWidget::DrawVertexs()
{
    m_pFunction->glUseProgram(m_uiVertexsShader);

    // sset shader light variable value
    glUniform3f(m_iVertexCcoLoc, 0.8f, 0.1f, 0.5f);
    glUniform3f(m_iVertexLightColorLoc, 1.0f, 1.0f, 1.0f);
    glUniform3f(m_iVertexLightPosLoc, 30.0f*m_fRange, 30.0f*m_fRange, 100.0f*m_fRange);
    glUniform3f(m_iVertexViewPosLoc, 0.0f*m_fRange,  0.0f*m_fRange, 100.0f*m_fRange);

    // set the value of the shader program
    const QMatrix4x4 _vertexsMatrx = m_qTranslateMatrix * m_qRoateMatrix * m_qModelMatrix;
    glUniformMatrix4fv(m_iVertexsModel_Loc, 1, GL_FALSE, _vertexsMatrx.data());
    glUniformMatrix4fv(m_iVertexsView_Loc, 1, GL_FALSE, m_qViewMatrix.data() );
    glUniformMatrix4fv(m_iVertexsProject_Loc, 1, GL_FALSE, m_qProjectMatrix.data());

    // Draw the Vertexs Render connect to the shader
    m_pFunction->glBindVertexArray(m_uVertexsVAO);   // all the point

    // Position attribute start from the nullptr transfer the buffur to vertex shader
    m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uVertexsVBO);
    m_pFunction->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat),
                                       static_cast<GLvoid*>(nullptr));
    m_pFunction->glEnableVertexAttribArray(0);

    // Color attribute transfer the buffer to vertex shader
    m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uVertexsCBO);
    m_pFunction->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat),
                                       static_cast<GLvoid*>(nullptr));
    m_pFunction->glEnableVertexAttribArray(1);

    glPointSize(5);
    m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uVertexsEBO);   // all the index
    m_pFunction->glDrawElements(GL_POINTS, m_vVertexsIndex.size(), GL_UNSIGNED_INT, nullptr);
    glPointSize(1);

    // disbin the buffer
    m_pFunction->glBindVertexArray(0);
    m_pFunction->glUseProgram(0);
    return true;
}

bool GLWidget::DrawLines()
{
    m_pFunction->glUseProgram(m_uiVertexsShader);

    // sset shader light variable value
    glUniform3f(m_iLineCcoLoc,  0.1f,  0.1f,   0.8f);
    glUniform3f(m_iLineLightColorLoc,   1.0f,  1.0f,   1.0f);
    glUniform3f(m_iLineLightPosLoc,    30.0f*m_fRange, 30.0f*m_fRange, 100.0f*m_fRange);
    glUniform3f(m_iLineViewPosLoc,      0.0f*m_fRange,  0.0f*m_fRange, 100.0f*m_fRange);

    // set the value of the shader program
    const QMatrix4x4 _linesMatrx = m_qTranslateMatrix * m_qRoateMatrix * m_qModelMatrix;
    glUniformMatrix4fv(m_iLineModel_Loc, 1, GL_FALSE, _linesMatrx.data());
    glUniformMatrix4fv(m_iLineView_Loc, 1, GL_FALSE, m_qViewMatrix.data() );
    glUniformMatrix4fv(m_iLineProject_Loc, 1, GL_FALSE, m_qProjectMatrix.data());

    // Draw the Vertexs Render connect to the renders
    m_pFunction->glBindVertexArray(m_uLinesVAO);   // all the point

    // Position attribute start from the nullptr transfer the buffur to vertex shader
    m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uLinesVBO);
    m_pFunction->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat),
                                       static_cast<GLvoid*>(nullptr));
    m_pFunction->glEnableVertexAttribArray(0);

    // Color attribute transfer the buffer to vertex shader
    m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uLinesCBO);
    m_pFunction->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat),
                                       static_cast<GLvoid*>(nullptr));
    m_pFunction->glEnableVertexAttribArray(1);

    m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uLinesEBO);   // all the index
    m_pFunction->glDrawElements(GL_LINES, m_vLineIndex.size(), GL_UNSIGNED_INT, nullptr);

    // disbin the buffer
    m_pFunction->glBindVertexArray(0);
    m_pFunction->glUseProgram(0);
    return true;
}

bool GLWidget::TriangleDrawCall()
{
    // set draw mode
    m_pFunction->glBindVertexArray(m_uTrianglesVAO);   // all the point
    // Position attribute start from the nullptr transfer the buffur to vertex shader
    m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uTrianglesVBO);
    m_pFunction->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat),
                                       static_cast<GLvoid*>(nullptr));
    m_pFunction->glEnableVertexAttribArray(0);
    // Color attribute transfer the buffer to vertex shader
    m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uTrianglesCBO);
    m_pFunction->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat),
                                       static_cast<GLvoid*>(nullptr));
    m_pFunction->glEnableVertexAttribArray(1);
    // Color attribute transfer the buffer to vertex shader
    m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uTrianglesNBO);
    m_pFunction->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat),
                                       static_cast<GLvoid*>(nullptr));
    m_pFunction->glEnableVertexAttribArray(2);

    // use DrawElement draw element
    m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uTrianglesEBO);   // all the index
    m_pFunction->glDrawElements(GL_TRIANGLES, m_vTriangleIndex.size(), GL_UNSIGNED_INT, nullptr);

    // use drawArray to draw element
    // m_pFunction->glBindVertexArray(m_uQuadsVAO);
    // m_pFunction->glDrawArrays(GL_QUADS, 0, m_vQuadsIndex.size());

    // disbin the buffer
    m_pFunction->glBindVertexArray(0);
}

bool GLWidget::DrawTrianglesLines()
{
    m_pFunction->glUseProgram(m_uiLinesShader);

    // draw out line 0.1882352941176471
    glUniform3f(m_iLineCcoLoc,0.188f,0.188f,0.188f);
    glUniform3f(m_iLineLightColorLoc, 1.0f, 1.0f, 1.0f);
    glUniform3f(m_iLineLightPosLoc, 30*m_fRange, 30*m_fRange, 100*m_fRange);
    glUniform3f(m_iLineViewPosLoc, 0*m_fRange, 0*m_fRange, 100*m_fRange);

    // set the value of the shader program
    const QMatrix4x4 _matrx = m_qTranslateMatrix * m_qRoateMatrix * m_qModelMatrix;
    glUniformMatrix4fv(m_iLineModel_Loc, 1, GL_FALSE, _matrx.data());
    glUniformMatrix4fv(m_iLineView_Loc, 1, GL_FALSE, m_qViewMatrix.data() );
    glUniformMatrix4fv(m_iLineProject_Loc, 1, GL_FALSE, m_qProjectMatrix.data());

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // set drawModel as line
    TriangleDrawCall();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set drawModel as face

    m_pFunction->glUseProgram(0);
    return true;
}

bool GLWidget::DrawTrianglesFaces()
{
    m_pFunction->glUseProgram(m_uiMaterialLightShader);
    // set shader light variable value
    glUniform3f(m_iFaceViewPosLoc, 0*m_fRange, 0*m_fRange, 100*m_fRange);
    glUniform3f(m_iFaceLightPos, 30*m_fRange, 500*m_fRange, 1000*m_fRange);
    glUniform3f(m_iFaceLightambinet, 1.0f, 0.5f, 0.31f);  // ambient color
    glUniform3f(m_iFaceLightdiffuse, 1.0f, 0.5f, 0.31f);  // diffuse color
    glUniform3f(m_iFaceLightspecular, 1.0f, 1.0f, 1.0f);  // specular color

    glUniform3f(m_iFaceMaterialambinet, 1.0f, 0.5f, 0.31f);  // ambient color
    glUniform3f(m_iFaceMaterialdiffuse, 1.0f, 0.5f, 0.31f);  // diffuse color
    glUniform3f(m_iFaceMaterialspecular, 1.0f, 1.0f, 1.0f);  // specular color
    glUniform1f(m_iFaceMaterialshininess, 32.0f);  // ambient color

    // set the value of the shader program
    const QMatrix4x4 _Trianglematrx = m_qTranslateMatrix * m_qRoateMatrix * m_qModelMatrix;
    glUniformMatrix4fv(m_iFacemodel_Loc, 1, GL_FALSE, _Trianglematrx.data());
    glUniformMatrix4fv(m_iFaceView_Loc, 1, GL_FALSE, m_qViewMatrix.data() );
    glUniformMatrix4fv(m_iFaceProject_Loc, 1, GL_FALSE, m_qProjectMatrix.data());

    if ( m_bShowMesh ) {  // if has mesh will offset it
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(m_fOffset, m_fOffset);
        TriangleDrawCall();
        glDisable(GL_POLYGON_OFFSET_FILL);
    } else {  // if it doesn't hava mesh,it will not need offset
        TriangleDrawCall();
    }
    m_pFunction->glUseProgram(0);
    return true;
}

bool GLWidget::QuadsDrawCall()
{
    // Draw the QUADS Render
    m_pFunction->glBindVertexArray(m_uQuadsVAO);   // all the point
    // Position attribute start from the nullptr transfer the buffur to vertex shader
    m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uQuadsVBO);
    m_pFunction->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat),
                                       static_cast<GLvoid*>(nullptr));
    m_pFunction->glEnableVertexAttribArray(0);

    // Color attribute transfer the buffer to vertex shader
    m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uQuadsCBO);
    m_pFunction->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat),
                                       static_cast<GLvoid*>(nullptr));
    m_pFunction->glEnableVertexAttribArray(1);

    // Color attribute transfer the buffer to vertex shader
    m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uQuadsNBO);
    m_pFunction->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat),
                                       static_cast<GLvoid*>(nullptr));
    m_pFunction->glEnableVertexAttribArray(2);

    m_pFunction->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uQuadsEBO);   // all the index
    m_pFunction->glDrawElements(GL_QUADS, m_vQuadsIndex.size(), GL_UNSIGNED_INT, nullptr);

    // disbin the buffer
    m_pFunction->glBindVertexArray(0);
}

bool GLWidget::DrawQuadsLines()
{
    m_pFunction->glUseProgram(m_uiLinesShader);

    // draw out line
    glUniform3f(m_iLineCcoLoc, 0.188f, 0.188f, 0.188f);
    glUniform3f(m_iLineLightColorLoc, 1.0f, 1.0f, 1.0f);
    glUniform3f(m_iLineLightPosLoc, 30*m_fRange, 30*m_fRange, 100*m_fRange);
    glUniform3f(m_iLineViewPosLoc, 0*m_fRange, 0*m_fRange, 100*m_fRange);

    // set the value of the shader program
    const QMatrix4x4 _matrx = m_qTranslateMatrix * m_qRoateMatrix * m_qModelMatrix;
    glUniformMatrix4fv(m_iLineModel_Loc, 1, GL_FALSE, _matrx.data());
    glUniformMatrix4fv(m_iLineView_Loc, 1, GL_FALSE, m_qViewMatrix.data() );
    glUniformMatrix4fv(m_iLineProject_Loc, 1, GL_FALSE, m_qProjectMatrix.data());
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // set drawModel as line
    QuadsDrawCall();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set drawModel as face
    return true;
}

bool GLWidget::DrawQuadsFaces()
{
    m_pFunction->glUseProgram(m_uiMaterialLightShader);
    // set shader light variable value
    glUniform3f(m_iFaceViewPosLoc, 0*m_fRange, 0*m_fRange, 100*m_fRange);
    glUniform3f(m_iFaceLightPos, 30*m_fRange, 500*m_fRange, 1000*m_fRange);
    glUniform3f(m_iFaceLightambinet, 1.0f, 0.5f, 0.31f);  // ambient color
    glUniform3f(m_iFaceLightdiffuse, 1.0f, 0.5f, 0.31f);  // diffuse color
    glUniform3f(m_iFaceLightspecular, 1.0f, 1.0f, 1.0f);  // specular color

    glUniform3f(m_iFaceMaterialambinet, 1.0f, 0.5f, 0.31f);  // ambient color
    glUniform3f(m_iFaceMaterialdiffuse, 1.0f, 0.5f, 0.31f);  // diffuse color
    glUniform3f(m_iFaceMaterialspecular, 1.0f, 1.0f, 1.0f);  // specular color
    glUniform1f(m_iFaceMaterialshininess, 32.0f);  // ambient color

    // set the value of the shader program
    const QMatrix4x4 _Quadmatrx = m_qTranslateMatrix * m_qRoateMatrix * m_qModelMatrix;
    m_pFunction->glUniformMatrix4fv(m_iFacemodel_Loc, 1, GL_FALSE, _Quadmatrx.data());
    m_pFunction->glUniformMatrix4fv(m_iFaceView_Loc, 1, GL_FALSE, m_qViewMatrix.data() );
    m_pFunction->glUniformMatrix4fv(m_iFaceProject_Loc, 1, GL_FALSE, m_qProjectMatrix.data());

    if ( m_bShowMesh ) {
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(m_fOffset, m_fOffset);
        QuadsDrawCall();
        glDisable(GL_POLYGON_OFFSET_FILL);
    } else {
        QuadsDrawCall();
    }
    m_pFunction->glUseProgram(0);
    return true;
}

void GLWidget::showPointSwitch()
{
    m_bShowPoint = !m_bShowPoint;
    this->update();
}

void GLWidget::showLineSwitch()
{
    m_bShowLine = !m_bShowLine;
    this->update();
}

void GLWidget::showMeshSwitch()
{
    m_bShowMesh = !m_bShowMesh;
    this->update();
}

void GLWidget::showFaceSwitch()
{
    m_bShowFace = !m_bShowFace;
    this->update();
}

void GLWidget::paintGL()
{
    if ( m_bTransparency ) {
        Display();
    } else {
        // draw the backGround
        glDisable(GL_DEPTH_TEST);
        DrawBackGround();
        glPointSize(10);
        DrawReferenceTap();
        glEnable(GL_DEPTH_TEST);

        // show point
        if (m_bShowPoint) {
            DrawVertexs();  // draw all the vertexs
        }
        // show Line
        if (m_bShowLine) {
            DrawLines();  // draw all the lines
        }
        // show mesh
        if (m_bShowMesh) {
            DrawTrianglesLines();  // draw all the triangle outline
            DrawQuadsLines(); // draw all the quads outline
        }
        // show face
        if (m_bShowFace) {
            DrawTrianglesFaces();  // draw all the triangle faces
            DrawQuadsFaces(); // draw all the quads faces
        }
        glDisable(GL_DEPTH_TEST);
        // draw text
        // read all the pixel
        if(nullptr != m_pDepthBuffer) {
            m_pFunction->glReadPixels(0, 0, m_nGLWWidth, m_nGLHeight, GL_DEPTH_COMPONENT, GL_FLOAT, m_pDepthBuffer);
        }
    }
    glEnable(GL_BLEND);
//    RenderText(m_uiTextsShader, "(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
    RenderText(m_uiTextsShader, "FEMStudio Version 1.0.0.0", 25.0f, 25.0f, 0.25f, glm::vec3(0.5, 0.8f, 0.2f));
}

// override the mouse event
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::RightButton) {
//        qDebug()<<"you have pressed RightButton";
        m_pLastPoint = event->pos();
    } else if (event->buttons() == Qt::LeftButton) {
//        qDebug()<<"you have pressed LeftButton";
        Point2fT  _MousePt;
        m_ArcLastRot = m_ArcThisRot;
        _MousePt.s.X = static_cast<GLfloat>( event->pos().x() );
        _MousePt.s.Y = static_cast<GLfloat>( event->pos().y() );
        m_pArcBallT->click(&_MousePt);
        m_mousePressPoint = event->pos();
    } else if (event->buttons() == Qt::MiddleButton) {
        qDebug()<<"you have pressed MiddleButton";
    } else {
        return;
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint _nowPoint;
    if (event->button() == Qt::RightButton) {
//        qDebug()<<"you have release RightButton";
        _nowPoint = event->pos();
    } else if (event->button() == Qt::LeftButton) {
//        qDebug()<<"you have release LeftButton";
        _nowPoint = event->pos();
    } else if (event->button() == Qt::MiddleButton) {
//        qDebug()<<"you have release MiddleButton";
        _nowPoint = event->pos();
    } else {
        return;
    }
    m_pLastPoint = _nowPoint;
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::RightButton) {
//        qDebug()<<"you have double click RightButton";
    }
    else if (event->buttons() == Qt::LeftButton) {
        qDebug()<<"you have double click LeftButton";
        GLint viewport[4];
        GLdouble mvmatrix[16], projmatrix[16];
        GLint realy;  /*  OpenGL y coordinate position  */
        GLdouble objectx, objecty, objectz;  /*  returned world x, y, z coords  */
//        glGetIntegerv (GL_VIEWPORT,         viewport);
//        glGetDoublev (GL_MODELVIEW_MATRIX,  mvmatrix);
//        glGetDoublev (GL_PROJECTION_MATRIX, projmatrix);

        // when we add menuBar and ToolBar the viewPort will be changed, so must change the value
        viewport[0] = 0;
        viewport[1] = 0;
        viewport[2] = m_nGLWWidth;
        viewport[3] = m_nGLHeight;

        // model matrix
        QMatrix4x4 _modelMatrx = m_qTranslateMatrix * m_qRoateMatrix * m_qModelMatrix;
        float* _pTempModel = _modelMatrx.data();
        // project matrix
        float* _pTempProject = m_qProjectMatrix.data();
        // Copy all the data to float array;
        for (int _i = 0; _i < 16; _i++) {
            mvmatrix[_i] = static_cast<GLdouble>(_pTempModel[_i]);
            projmatrix[_i] = static_cast<GLdouble>(_pTempProject[_i]);
        }

        // note viewport[3] is height of window in pixels
        realy = viewport[3] - static_cast<GLint>(event->y()) - 1;
        qDebug()<<QString("Coordinates at cursor are (%1, %2)").arg(event->x()).arg(viewport[3] - event->y());
        qDebug()<<QString("Coordinates at cursor are (%1, %2)").arg(event->x()).arg(realy);

        // prevent the vertext overflow
        if (m_vVertexs.size() >= 3) {
            // handle calculate the point on OpenGL coords
            QVector4D _vector4D(m_vVertexs[0], m_vVertexs[1], m_vVertexs[2], 1.0);
            QVector4D _resulte4D = _modelMatrx * _vector4D;  // calculate the point in the position of World Coords
            _resulte4D = m_qProjectMatrix * _resulte4D;  // calculate the point int screen SCALE[-1, 1]
            // calculate homogeneous equation
            GLfloat _windX = _resulte4D.x();
            GLfloat _windY = _resulte4D.y();
    //        GLfloat _windZ = _resulte4D.z();
            GLfloat _scaleSize = _resulte4D.w();
            GLfloat _windXPixel = (_windX/_scaleSize + 1) * viewport[2]/2;
            GLfloat _windYPixel = (1 - _windY/_scaleSize) * viewport[3]/2;
            qDebug()<<_windXPixel<<"  "<< _windYPixel;

            // translate Windows coords to world coords
            GLdouble _wx, _wy, _wz;
            gluProject(static_cast<GLdouble>(m_vVertexs[0]),
                       static_cast<GLdouble>(m_vVertexs[1]),
                       static_cast<GLdouble>(m_vVertexs[2]),
                       mvmatrix, projmatrix, viewport, &_wx, &_wy, &_wz);

            // translate world coords to Windows coords
            qDebug()<<QString("World coords at(x = %1, y = %2, z = %3) to Window Coors is (wx = %4, wy = %5, wz = %6)").
                      arg(static_cast<GLdouble>(m_vVertexs[0])).
                      arg(static_cast<GLdouble>(m_vVertexs[1])).
                      arg(static_cast<GLdouble>(m_vVertexs[2])).
                      arg(_wx).arg(_wy).arg(_wz);

            /* **************************************************************************************************
             *                      calculate the really point in opengl widget
             * 1. gluUnproject
             * 2. calculate the depth from depth buffer must use OpenGL Widget coords
             * 3. calculate the objectx, objecty, objectz must use Project Matrix MouseX and MouseY
             * because you add the toolbar and menubar, both of them ocuupie position
             ****************************************************************************************************/
            GLint _reallyMouseX = event->x();
            GLint _reallyMouseY = viewport[3] - event->y() - 1;

            // Calculate the Point as Z Depth
            gluUnProject (static_cast<GLdouble>(_reallyMouseX),
                          static_cast<GLdouble>(_reallyMouseY),
                          static_cast<GLdouble>(m_pDepthBuffer[_reallyMouseY * viewport[2] + _reallyMouseX]),
                          mvmatrix, projmatrix, viewport, &objectx, &objecty, &objectz);

            qDebug()<<QString("Windows coords at(wx = %1, wy = %2, wz = %3) to World coords at(x = %4, y = %5, z = %6)").
                      arg(_reallyMouseX).
                      arg(_reallyMouseY).
                      arg( static_cast<GLdouble>(m_pDepthBuffer[_reallyMouseY * viewport[2] + _reallyMouseX] ) ).
                      arg(objectx).arg(objecty).arg(objectz);
        }

    }
    else if (event->buttons() == Qt::MiddleButton) {
//        qDebug()<<"you have double click MiddleButton";
    }
    else {
        return;
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    // the model translate
    if (event->buttons() == Qt::RightButton) {
        QPoint _nowPoint = event->pos();
        QPoint _movedVector =_nowPoint -  m_pLastPoint;
        // translate the model matrix
        m_qTranslateMatrix.translate( static_cast<GLfloat>(_movedVector.x()) / m_fProportionality, -static_cast<GLfloat>(_movedVector.y())  / m_fProportionality, 0.0f);
        m_pLastPoint = _nowPoint;
    }
    // the model rotate
    else if (event->buttons() == Qt::LeftButton)
    {
        Point2fT  _MousePt;
        _MousePt.s.X = static_cast<float>(event->pos().x());
        _MousePt.s.Y = static_cast<float>(event->pos().y());

        m_pArcBallT->drag(IN &_MousePt, OUT &m_ArcThisQuat);						// Update End Vector And Get Rotation As Quaternion
        Matrix3fSetRotationFromQuat4f(OUT &m_ArcThisRot, IN &m_ArcThisQuat);		// Convert Quaternion Into Matrix3fT
        Matrix3fMulMatrix3f(OUT &m_ArcThisRot, IN &m_ArcLastRot);				    // Accumulate Last Rotation Into This One
        Matrix4fSetRotationFromMatrix3f(OUT &m_ArcTransform, IN &m_ArcThisRot);	    // Set Our Final m_ArcTransform's Rotation From This One

        // copy the data of arcball  to rotate Matrix
        float *_matrix = m_qRoateMatrix.data();
        for ( int _i = 0; _i < 16; _i++ )
        {
            _matrix[_i] = m_ArcTransform.M[_i];
        }
        m_pLastPoint  = event->pos();
    }
    else if (event->buttons() == Qt::MiddleButton)
    {
    }
    else
    {
        return;
    }
    this->update();
}
bool GLWidget::clearAllData()
{
    // clear all the unused vertexs data
    m_vVertexs.clear();
    QVector<GLfloat>().swap(m_vVertexs);
    m_vVertexsColor.clear();
    QVector<GLfloat>().swap(m_vVertexsColor);
    m_vVertexsIndex.clear();
    QVector<GLuint>().swap(m_vVertexsIndex);

    // clear all the unused line data
    m_vLineVertexs.clear();
    QVector<GLfloat>().swap(m_vLineVertexs);
    m_vLineNormal.clear();
    QVector<GLfloat>().swap(m_vLineNormal);
    m_vLineColor.clear();
    QVector<GLfloat>().swap(m_vLineColor);
    m_vLineIndex.clear();
    QVector<GLuint>().swap(m_vLineIndex);

    // clear all the unused triangle data
    m_vTrianglesVertexs.clear();
    QVector<GLfloat>().swap(m_vTrianglesVertexs);
    m_vTrianglesNormal.clear();
    QVector<GLfloat>().swap(m_vTrianglesNormal);
    m_vTrianglesColor.clear();
    QVector<GLfloat>().swap(m_vTrianglesColor);
    m_vTriangleIndex.clear();
    QVector<GLuint>().swap(m_vTriangleIndex);

    // clear all the unused Quad data
    m_vQuadsVertexs.clear();
    QVector<GLfloat>().swap(m_vQuadsVertexs);
    m_vQuadsNormal.clear();
    QVector<GLfloat>().swap(m_vQuadsNormal);
    m_vQuadsColor.clear();
    QVector<GLfloat>().swap(m_vQuadsColor);
    m_vQuadsIndex.clear();
    QVector<GLuint>().swap(m_vQuadsIndex);

    qDebug()<<"You have clear all the OpenGL graphic struct data";

    return true;
}

// textture
void GLWidget::RenderText(GLuint &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
    // Activate corresponding render state
    m_pFunction->glUseProgram(shader);
    glm::mat4 projection = glm::ortho(0.0f,
                                      static_cast<GLfloat>(this->width()),
                                      0.0f,
                                      static_cast<GLfloat>(this->height()));
    m_pFunction->glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    m_pFunction->glUniform3f(glGetUniformLocation(shader, "textColor"), color.x, color.y, color.z);
    m_pFunction->glActiveTexture(GL_TEXTURE0);
    m_pFunction->glBindVertexArray(m_uTextVAO);

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = m_CharactersMap[*c];

        GLfloat xpos = x + static_cast<float>(ch.Bearing.x) * scale;
        GLfloat ypos = y - static_cast<float>(ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = static_cast<float>(ch.Size.x) * scale;
        GLfloat h = static_cast<float>(ch.Size.y) * scale;

        // Update VBO for each character
        GLfloat vertices[4][4] = {
             { xpos,     ypos + h, 0.0, 0.0 },
             { xpos,     ypos,     0.0, 1.0 },
             { xpos + w, ypos,     1.0, 1.0 },
             { xpos + w, ypos + h, 1.0, 0.0 }
        };

        // Render glyph texture over quad
        m_pFunction->glBindTexture(GL_TEXTURE_2D, ch.TextureID);

        // Update content of VBO memory
        m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, m_uTextVBO);
        m_pFunction->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
        m_pFunction->glBindBuffer(GL_ARRAY_BUFFER, 0);

////         Position attribute
//        m_pFunction->glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
//        m_pFunction->glEnableVertexAttribArray(0);

//        // Position attribute
//        m_pFunction->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
//        m_pFunction->glEnableVertexAttribArray(0);

        // Render quad
        m_pFunction->glDrawArrays(GL_QUADS, 0, 4);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        x += static_cast<float>(ch.Advance >> 6) * scale;
    }
    m_pFunction->glBindVertexArray(0);
    m_pFunction->glBindTexture(GL_TEXTURE_2D, 0);
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    if ( event->delta() > 0 ) {
        m_fScale *= 1.1f;
        QMatrix4x4 _matrix;
        _matrix.scale(1.1f, 1.1f, 1.1f);
        m_qModelMatrix = _matrix * m_qModelMatrix;
    }
    else if (event->delta() < 0) {
        m_fScale *= 0.9f;
        QMatrix4x4 _matrix;
        _matrix.scale(0.9f, 0.9f, 0.9f);
        m_qModelMatrix = _matrix * m_qModelMatrix;
    }
    else {
        return;
    }
    this->update();
}

// clear all the buffer
bool GLWidget::clearBuffer()
{
    clearVertexsBuffer();
    clearLineBuffer();
    clearTriangleBuffer();
    clearQuadsBuffer();
    return true;
}

// clear Vertext buffer
bool GLWidget::clearVertexsBuffer()
{
    // delete all Vertexs VAO
    if(m_pFunction->glIsVertexArray(m_uVertexsVAO)) {
        m_pFunction->glDeleteVertexArrays(1, &m_uVertexsVAO);
    }
    // delete all Vertexs VBO
    if (m_pFunction->glIsBuffer(m_uVertexsVBO)) {
        m_pFunction->glDeleteBuffers(1, &m_uVertexsVBO);
    }
    // delete all Vertexs CBO
    if (m_pFunction->glIsBuffer(m_uVertexsCBO)) {
        m_pFunction->glDeleteBuffers(1, &m_uVertexsCBO);
    }
    // delete all Vertexs EBO
    if (m_pFunction->glIsBuffer(m_uVertexsEBO)) {
        m_pFunction->glDeleteBuffers(1, &m_uVertexsEBO);
    }

    return true;
}

// clear line buffer
bool GLWidget::clearLineBuffer()
{
    // delete all Vertexs VAO
    if(m_pFunction->glIsVertexArray(m_uLinesVAO)) {
        m_pFunction->glDeleteVertexArrays(1, &m_uLinesVAO);
    }
    // delete all Vertexs VBO
    if (m_pFunction->glIsBuffer(m_uLinesVBO)) {
        m_pFunction->glDeleteBuffers(1, &m_uLinesVBO);
    }
    // delete all Vertexs CBO
    if (m_pFunction->glIsBuffer(m_uLinesCBO)) {
        m_pFunction->glDeleteBuffers(1, &m_uLinesCBO);
    }
    // delete all Vertexs EBO
    if (m_pFunction->glIsBuffer(m_uLinesEBO)) {
        m_pFunction->glDeleteBuffers(1, &m_uLinesEBO);
    }

    return true;
}

// clear triangle buffer
bool GLWidget::clearTriangleBuffer()
{
    // delete all Quads  VAO
    if(m_pFunction->glIsVertexArray(m_uTrianglesVAO)) {
        m_pFunction->glDeleteVertexArrays(1, &m_uTrianglesVAO);
    }
    // delete all Quads VBO
    if (m_pFunction->glIsBuffer(m_uTrianglesVBO)) {
        m_pFunction->glDeleteBuffers(1, &m_uTrianglesVBO);
    }
    // delete all Quads CBO
    if (m_pFunction->glIsBuffer(m_uTrianglesCBO)) {
        m_pFunction->glDeleteBuffers(1, &m_uTrianglesCBO);
    }
    // delete all Quads NBO
    if (m_pFunction->glIsBuffer(m_uTrianglesNBO)) {
        m_pFunction->glDeleteBuffers(1, &m_uTrianglesNBO);
    }
    // delete all Quads EBO
    if (m_pFunction->glIsBuffer(m_uTrianglesEBO)) {
        m_pFunction->glDeleteBuffers(1, &m_uTrianglesEBO);
    }

    return true;
}

// clear quads buffer
bool GLWidget::clearQuadsBuffer()
{
    // delete all Quads  VAO
    if(m_pFunction->glIsVertexArray(m_uQuadsVAO)) {
        m_pFunction->glDeleteVertexArrays(1, &m_uQuadsVAO);
    }
    // delete all Quads VBO
    if (m_pFunction->glIsBuffer(m_uQuadsVBO)) {
        m_pFunction->glDeleteBuffers(1, &m_uQuadsVBO);
    }
    // delete all Quads CBO
    if (m_pFunction->glIsBuffer(m_uQuadsCBO)) {
        m_pFunction->glDeleteBuffers(1, &m_uQuadsCBO);
    }
    // delete all Quads NBO
    if (m_pFunction->glIsBuffer(m_uQuadsNBO)) {
        m_pFunction->glDeleteBuffers(1, &m_uQuadsNBO);
    }
    // delete all Quads EBO
    if (m_pFunction->glIsBuffer(m_uQuadsEBO)) {
        m_pFunction->glDeleteBuffers(1, &m_uQuadsEBO);
    }

    return true;
}

