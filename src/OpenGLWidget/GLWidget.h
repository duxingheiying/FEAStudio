/**********************************************************************************************************
 * swap data by judgement nullptr
 * if it is nullptr jump it
 * else swap it
 * as update gl buffer, if just update point position just change VBO,
 * else as the same deal with it
 *                                                                                    design by guweicao
 *                                                                                    2019.3.3
 **********************************************************************************************************/

#ifndef GLWIDGET_H
#define GLWIDGET_H

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
#include <QOpenGLBuffer>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QFileInfo>
#include <QDir>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <QOpenGLFunctions_4_5_Core>

#include "ArcBall.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <ft2build.h>
#include <freetype/freetype.h>

// Order Independent Transparency
#include "vmath.h"
#define MAX_FRAMEBUFFER_WIDTH 2560
#define MAX_FRAMEBUFFER_HEIGHT 1440

using namespace vmath;

struct Character {
    GLuint TextureID;    // ID handle of the glyph texture
    glm::ivec2 Size;     // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;      // Horizontal offset to advance to next glyph
};

class GLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
public:
    explicit GLWidget(QWidget *parent = nullptr);
    virtual ~GLWidget() override;

public:
    bool clearAllData();  // clear all the point/line/triangle/quad
    bool updateBuffer();  // update buffer
    bool initializeContralMatrix(); // initialize all matrix
    void setGLCoordsRangle(const GLfloat);  // set the scale or range
    void showPointSwitch();
    void showLineSwitch();
    void showMeshSwitch();
    void showFaceSwitch();
    void switchTransparency();
    void swapData( const QVector3D& vCenter_, // the center of the model
                   const GLfloat& fRange_,  // the range of the model
                   QVector<GLfloat>* vVertexs_, // the point array
                   QVector<GLfloat>* vVertexsColor_, // the point color
                   QVector<GLuint>*  vVertexsIndex_, // the point index
                   QVector<GLfloat>* vLineVertexs_, // the line point normal
                   QVector<GLfloat>* vLineVertexsColor_, // the line point array
                   QVector<GLfloat>* vLineVertexsNormal_, // the line point color
                   QVector<GLuint>*  vLineVertexsIndex_, // the line index
                   QVector<GLfloat>* vTriangleVertexs_, // the triangle point normal
                   QVector<GLfloat>* vTriangleVertexsColor_, // the triangle point array
                   QVector<GLfloat>* vTriangleVertexsNormal_, // the triangle point color
                   QVector<GLuint>*  vTriangleVertexsIndex_, // the triangle index
                   QVector<GLfloat>* vQuadVertexs_, // the quad point normal
                   QVector<GLfloat>* vQuadVertexsColor_, // the quad point array
                   QVector<GLfloat>* vQuadVertexsNormal_, // the quad point color
                   QVector<GLuint>*  vQuadVertexsIndex_ ); // the quad index

protected:
//    virtual void resizeEvent(QResizeEvent *event);
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void initializeGL() override;
    virtual void resizeGL(const GLint width, const GLint height) override;
    virtual void paintGL() override;

private:
    virtual void initializeProgram();
    virtual void initializeOIT();
    
    // OverLoad the funtion
    inline GLuint CreateProgram(const GLchar* vertexPath, const GLchar* fragmentPath);
    inline GLuint CreateProgram(const QString vertexPath, const QString fragmentPath);

    // clear all buffuer
    inline bool clearBuffer();
    inline bool clearVertexsBuffer();
    inline bool clearLineBuffer();
    inline bool clearTriangleBuffer();
    inline bool clearQuadsBuffer();

    bool calculateReferenceTapData(const bool &&updateVertex_ = true,
                                   const bool &&updateColor_ = true,
                                   const bool &&updateNormal_ = true,
                                   const bool &&updateIndex_ = true);

    bool updateReferenceTapData(const bool &&updateVAO_ = true,
                                const bool &&updateVBO_ = true,
                                const bool &&updateCBO_ = true,
                                const bool &&updateNBO_ = true,
                                const bool &&updateEBO_ = true);

    // calculate all the background vertexs
    inline bool calculateBackGroundData(const bool&& updateVertex_ = true,
                                        const bool&& updateColor_ = true,
                                        const bool&& updateNormal_ = true,
                                        const bool&& updateIndex_ = true);

    // create back ground date
    inline bool updateBackGroundBuffer(const bool&& updateVAO_ = true,
                                       const bool&& updateVBO_ = true,
                                       const bool&& updateCBO_ = true,
                                       const bool&& updateNBO_ = true,
                                       const bool&& updateEBO_ = true);

    // Creat Point Buffer
    inline bool updateVertexsBuffer(const bool&& updateVAO_ = true,
                                    const bool&& updateVBO_ = true,
                                    const bool&& updateCBO_ = true,
                                    const bool&& updateEBO_ = true);

    inline bool updateLinesBuffer(const bool&& updateVAO_ = true,
                                  const bool&& updateVBO_ = true,
                                  const bool&& updateCBO_ = true,
                                  const bool&& updateEBO_ = true);

    inline bool updateTrianglesBuffer(const bool&& updateVAO_ = true,
                                      const bool&& updateVBO_ = true,
                                      const bool&& updateCBO_ = true,
                                      const bool&& updateNBO_ = true,
                                      const bool&& updateEBO_ = true);

    inline bool updateQuadsBuffer(const bool&& updateVAO_ = true,
                                  const bool&& updateVBO_ = true,
                                  const bool&& updateCBO_ = true,
                                  const bool&& updateNBO_ = true,
                                  const bool&& updateEBO_ = true);

    // draw back groun
    inline bool DrawBackGround();
    inline bool DrawBackGroundCall();

    // draw reference tap
    bool DrawReferenceTap();

    // DrawObject
    inline bool DrawVertexs();
    inline bool DrawLines();
    inline bool DrawTrianglesFaces();
    inline bool TriangleDrawCall();
    inline bool DrawTrianglesLines();
    inline bool DrawQuadsFaces();
    inline bool QuadsDrawCall();
    inline bool DrawQuadsLines();

    // draw text
    bool initialTextTexture();
    void RenderText(GLuint &shader,   // the shader
                    std::string text,  // text
                    GLfloat x,  // x point
                    GLfloat y,  // y point
                    GLfloat scale,  // scale size
                    glm::vec3 color);  // the color

    QString getStringFromUnsignedChar(const unsigned char *str);

public:

protected:

private:
    QVector3D  m_vCenter;           // the center of medal
    // the canvas scales
    GLfloat m_fRange;
    QVector<GLfloat> m_vReferenceTapeVertexs;  // all the reference tap vertexs list
    QVector<GLfloat> m_vReferenceTapeNormal;   // all the reference tap normals list
    QVector<GLfloat> m_vReferenceTapeColors;   // all the reference tap  colors list
    QVector<GLuint> m_vReferenceTapeIndex;    // all the reference tap index list

    // back ground data
    QVector<GLfloat> m_vBackFaceVertexs;  // all the back ground vertexs list
    QVector<GLfloat> m_vBackFaceNormal;   // all the back ground normals list
    QVector<GLfloat> m_vBackFaceColors;   // all the back ground colors list
    QVector<GLuint> m_vBackFaceIndex;    // all the back ground index list

    // vertexs data
    QVector<GLfloat> m_vVertexs;          // all the point x y z list
    QVector<GLfloat> m_vVertexsColor;     // all the point color r g b list
    QVector<GLuint> m_vVertexsIndex;     // all the poing index list

    // line data
    QVector<GLfloat> m_vLineVertexs;      // all lines points
    QVector<GLfloat> m_vLineNormal;       // all lines points normal
    QVector<GLfloat> m_vLineColor;        // all lines points color
    QVector<GLuint>  m_vLineIndex;        // all lines points index

    // triangles data
    QVector<GLfloat> m_vTrianglesVertexs; // all Triangles
    QVector<GLfloat> m_vTrianglesNormal;  // all Triangles points normal
    QVector<GLfloat> m_vTrianglesColor;   // all triangles points color
    QVector<GLuint>  m_vTriangleIndex;    // all triangles points index

    // quads data
    QVector<GLfloat> m_vQuadsVertexs;     // all Quads points
    QVector<GLfloat> m_vQuadsNormal;      // all Quads points Normals
    QVector<GLfloat> m_vQuadsColor;       // all Quads points color
    QVector<GLuint>  m_vQuadsIndex;        // all Quads points index

    // Qt matrix
    QMatrix4x4 m_qBackGroundMatrix; // background Matrix
    QMatrix4x4 m_qRoateMatrix;      // rotate Matrix
    QMatrix4x4 m_qTranslateMatrix;  // translate Matrix
    QMatrix4x4 m_qModelMatrix;      // Model Matrix
    QMatrix4x4 m_qViewMatrix;       // view Matrix
    QMatrix4x4 m_qProjectMatrix;    // project Matrix

    // widget Widget and height
    GLint    m_nGLWWidth;
    GLint    m_nGLHeight;
    GLdouble m_dHWPropotion;
    GLdouble m_dPixelToCoord;
//    GLdouble m_nRange;             // range of OpenGLCoords

    // shader program
    GLuint m_uiVertexsShader;        // vertex Shader
    GLuint m_uiLinesShader;          // line Shader
    GLuint m_uiFacesShader;          // face Shader
    GLuint m_uiTextsShader;          // Text Shader
    GLuint m_uiBackgroundShader;     // background Shader
    GLuint m_uiMultiLightShader;     // multilight Shader
    GLuint m_uiMaterialLightShader;  // materiallight Shader

    // back ground
    GLint m_iBackColor;
    GLint m_iBackLightColor;
    GLint m_iBackLightPos;
    GLint m_iBackViewPos;
    GLint m_iBackMode_loc;
    GLint m_iBackView_Loc;
    GLint m_iBackProject_Loc;

    // vertext
    GLint m_iVertexCcoLoc;
    GLint m_iVertexLightColorLoc;
    GLint m_iVertexLightPosLoc;
    GLint m_iVertexViewPosLoc;
    GLint m_iVertexsModel_Loc;
    GLint m_iVertexsView_Loc;
    GLint m_iVertexsProject_Loc;

    // line
    GLint m_iLineCcoLoc;
    GLint m_iLineLightColorLoc;
    GLint m_iLineLightPosLoc;
    GLint m_iLineViewPosLoc;
    GLint m_iLineModel_Loc;
    GLint m_iLineView_Loc;
    GLint m_iLineProject_Loc;

    // mesh
    GLint m_iMeshCcoLoc;
    GLint m_iMeshLightColorLoc;
    GLint m_iMeshLightPosLoc;
    GLint m_iMeshViewPosLoc;
    GLint m_iMeshModel_Loc;
    GLint m_iMeshView_Loc;
    GLint m_iMeshProject_Loc;

    // face
    GLint m_iFaceViewPosLoc;
    GLint m_iFaceLightPos;
    GLint m_iFaceLightambinet;
    GLint m_iFaceLightdiffuse;
    GLint m_iFaceLightspecular;

    GLint m_iFaceMaterialambinet;
    GLint m_iFaceMaterialdiffuse;
    GLint m_iFaceMaterialspecular;
    GLint m_iFaceMaterialshininess;

    GLint m_iFacemodel_Loc;
    GLint m_iFaceView_Loc;
    GLint m_iFaceProject_Loc;


    // Order Independent Transparency
    // Member variables
    // Program to construct the linked list (renders the transparent objects)
    // Head pointer image and PBO for clearing it
    GLuint  head_pointer_texture;
    GLuint  head_pointer_clear_buffer;
    // Atomic counter buffer
    GLuint  atomic_counter_buffer;
    // Linked list buffer
    GLuint  linked_list_buffer;
    GLuint  linked_list_texture;

    GLint m_iRenderLightPosition;

    // Program to render the scene
    GLuint render_scene_prog;
    struct
    {
        GLint model_matrix;
        GLint view_matrix;
        GLint projection_matrix;
    } render_scene_uniforms;

    // Program to resolve
    GLuint resolve_program;

    // Full Screen Quad
    GLuint quad_vbo;
    GLuint quad_vao;

    void Display();

    // initial glfunction
//    QOpenGLExtraFunctions* m_pFunction;
    QOpenGLFunctions_4_5_Core* m_pFunction;

    // Vertexs buffers
    GLuint m_VertexsBuffer;       // vertex buffer
    GLuint m_VertexsColorBuffer;  // color buffer
    GLuint m_VertexsIndexBuffer;  // index buffer
    GLuint m_uReadBuffer;

    // referenceTap
    GLuint m_uReferenceTapVAO;
    GLuint m_uReferenceTapVBO;
    GLuint m_uReferenceTapCBO;
    GLuint m_uReferenceTapNBO;
    GLuint m_uReferenceTapEBO;

    // back groud buffers
    GLuint m_uBackGroundVAO;
    GLuint m_uBackGroundVBO;
    GLuint m_uBackGroundCBO;
    GLuint m_uBackGroundNBO;
    GLuint m_uBackGroundEBO;

    // Vertexs buffere
    GLuint m_uVertexsVAO;
    GLuint m_uVertexsVBO;
    GLuint m_uVertexsCBO;
    GLuint m_uVertexsEBO;

    // Line buffer
    GLuint m_uLinesVAO;
    GLuint m_uLinesVBO;
    GLuint m_uLinesCBO;
    GLuint m_uLinesNBO;
    GLuint m_uLinesEBO;

    // Triangles buffer
    GLuint m_uTrianglesVAO;
    GLuint m_uTrianglesVBO;
    GLuint m_uTrianglesCBO;
    GLuint m_uTrianglesNBO;
    GLuint m_uTrianglesEBO;

    // Quads buffer
    GLuint m_uQuadsVAO;
    GLuint m_uQuadsVBO;
    GLuint m_uQuadsCBO;
    GLuint m_uQuadsNBO;
    GLuint m_uQuadsEBO;

    // this VAO and VBO are used in text
    GLuint m_uTextVAO;
    GLuint m_uTextVBO;

    // deep buffer
    GLfloat* m_pDepthBuffer;

    // vertex shader and fragram shader
    QOpenGLShader *m_pVertexShader;
    QOpenGLShader *m_pFragmentShader;

    // shader program does't use it now
    QOpenGLShaderProgram m_ShaderProgram;

    // proportionality
    GLfloat m_fProportionality;

    // mouse last point
    QPoint m_pLastPoint;

    // self realize the function need variable
    QPoint m_mousePressPoint;

    // the ArcBall date
    ArcBallT* m_pArcBallT;
    Matrix4fT m_ArcTransform;
    Matrix3fT m_ArcLastRot;
    Matrix3fT m_ArcThisRot;
    Quat4fT   m_ArcThisQuat;
    GLfloat   m_fScale;
    bool      m_bUpdateBuffer;

    // contral the show
    bool m_bShowPoint;
    bool m_bShowLine;
    bool m_bShowFace;
    bool m_bShowMesh;
    bool m_bTransparency;
    GLfloat m_fOffset;

    // draw text
    std::map<GLchar, Character> m_CharactersMap;
    FT_Library m_ft;
    FT_Face m_face;
};

#endif // GLWIDGET_H
