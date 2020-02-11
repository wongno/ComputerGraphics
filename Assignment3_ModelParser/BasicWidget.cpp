#include "BasicWidget.h"
#include "Obj.h"

//////////////////////////////////////////////////////////////////////
// Publics

BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent), vbo_(QOpenGLBuffer::VertexBuffer), cbo_(QOpenGLBuffer::VertexBuffer), ibo_(QOpenGLBuffer::IndexBuffer)

{
    setFocusPolicy(Qt::StrongFocus);
}

BasicWidget::~BasicWidget()
{

    vbo_.release();
    vbo_.destroy();
    ibo_.release();
    ibo_.destroy();
    cbo_.release();
    cbo_.destroy();
    vao_.release();
    vao_.destroy();
}

//////////////////////////////////////////////////////////////////////
// Privates
QString BasicWidget::vertexShaderString() const
{
    QString str =
        "#version 330\n"
        "layout(location = 0) in vec3 position;\n"
        "layout(location = 1) in vec4 color;\n"
        "out vec4 vertColor;\n"
        "void main()\n"
        "{\n"
        "  gl_Position = vec4(position, 1.0);\n"
        "  vertColor = color;\n"
        "}\n";
    return str;
}

QString BasicWidget::fragmentShaderString() const
{
    QString str =
        "#version 330\n"
        "in vec4 vertColor;\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "  color = vertColor;\n"
        "}\n";
    return str;
}


void BasicWidget::createShader()
{
    QOpenGLShader vert(QOpenGLShader::Vertex);
    vert.compileSourceCode(vertexShaderString());
    QOpenGLShader frag(QOpenGLShader::Fragment);
    frag.compileSourceCode(fragmentShaderString());
    bool ok = shaderProgram_.addShader(&vert);
    if (!ok) {
        qDebug() << shaderProgram_.log();
    }
    ok = shaderProgram_.addShader(&frag);
    if (!ok) {
        qDebug() << shaderProgram_.log();
    }
    ok = shaderProgram_.link();
    if (!ok) {
        qDebug() << shaderProgram_.log();
    }
}

///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent)
{
    // TODO
    // Handle key events here.
    if (keyEvent->key() == Qt::Key_Left) {
        qDebug() << "Left Arrow Pressed";
        setDir(3);
        update();  // We call update after we handle a key press to trigger a redraw when we are ready
    }
    else if (keyEvent->key() == Qt::Key_Right) {
        qDebug() << "Right Arrow Pressed";
        setDir(6);
        update();  // We call update after we handle a key press to trigger a redraw when we are ready
    }
    else {
        qDebug() << "You Pressed an unsupported Key!";
    }
    // ENDTODO
}
void BasicWidget::initializeGL()
{
    makeCurrent();
    initializeOpenGLFunctions();

    QOpenGLContext* curContext = this->context();
    qDebug() << "[BasicWidget]::initializeGL() -- Context Information:";
    qDebug() << "  Context Valid: " << std::string(curContext->isValid() ? "true" : "false").c_str();
    qDebug() << "  GL Version Used: " << curContext->format().majorVersion() << "." << curContext->format().minorVersion();
    qDebug() << "  Vendor: " << reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    qDebug() << "  Renderer: " << reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    qDebug() << "  Version: " << reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << "  GLSL Version: " << reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

    // Set up our shaders.
    createShader();

    // TODO:  Add vertex and index data to draw two triangles
    // Define our verts
    static const GLfloat verts[12] =
    {
      -0.8f, -0.8f, 0.0f, // Left vertex position
      0.8f, -0.8f, 0.0f,  // right vertex position
      -0.8f,  0.8f, 0.0f,  // Top vertex position
      0.8f, 0.8f, 0.0f
    };
    // Define our vert colors
    static const GLfloat colors[16] =
    {
        1.0f, 0.0f, 0.0f, 1.0f, // red
        0.0f, 1.0f, 0.0f, 1.0f, // green
        0.0f, 0.0f, 1.0f, 1.0f, // blue
        1.0f, 1.0f, 0.0f, 1.0f  // yellow
    };
    // Define our indices 14904, 2503
    static const GLuint idx[6] =
    {
        0, 1, 2, 2, 1, 3
    };
        // ENDTODO
    // Set up our buffers and our vao
  // Temporary bind of our shader.
    shaderProgram_.bind();
    // Create and prepare a vbo
    vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo_.create();
    // Bind our vbo inside our vao
    vbo_.bind();
    vbo_.allocate(verts, 12 * sizeof(GL_FLOAT));

    // TODO:  Generate our color buffer
    cbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
    cbo_.create();
    // Bind our vbo inside our vao
    cbo_.bind();
    cbo_.allocate(colors, 16 * sizeof(GL_FLOAT));
    // ENDTODO

    // TODO:  Generate our index buffer
    ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo_.create();
    // Bind our vbo inside our vao
    ibo_.bind();
    ibo_.allocate(idx, 6 * sizeof(GL_FLOAT));
    // ENDTODO

    // Create a VAO to keep track of things for us.
    vao_.create();
    vao_.bind();
    vbo_.bind();
    shaderProgram_.enableAttributeArray(0);
    shaderProgram_.setAttributeBuffer(0, GL_FLOAT, 0, 3);
    cbo_.bind();
    shaderProgram_.enableAttributeArray(1);
    shaderProgram_.setAttributeBuffer(1, GL_FLOAT, 0, 4);
    ibo_.bind();
    // Releae the vao THEN the vbo
    vao_.release();
    shaderProgram_.release();

    glViewport(0, 0, width(), height());
}

void BasicWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void BasicWidget::paintGL()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram_.bind();
    vao_.bind();
    // TODO: Change number of indices drawn
    glDrawElements(GL_TRIANGLES, getDir(), GL_UNSIGNED_INT, 0);
    // ENDTODO
    vao_.release();
    shaderProgram_.release();

}

//#include "BasicWidget.h"
//
////////////////////////////////////////////////////////////////////////
//// Publics
//BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent), vbo_(QOpenGLBuffer::VertexBuffer), cbo_(QOpenGLBuffer::VertexBuffer), ibo_(QOpenGLBuffer::IndexBuffer)
//{
//  setFocusPolicy(Qt::StrongFocus);
//}
//
//BasicWidget::~BasicWidget()
//{
//}
//
////////////////////////////////////////////////////////////////////////
//// Privates
//
/////////////////////////////////////////////////////////////////////////
//// Protected
//void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent)
//{
//  // TODO
//  // Handle key events here.
//  qDebug() << "You Pressed an unsupported Key!";
//  // ENDTODO
//}
//void BasicWidget::initializeGL()
//{
//  makeCurrent();
//  initializeOpenGLFunctions();
//
//  QOpenGLContext* curContext = this->context();
//  qDebug() << "[BasicWidget]::initializeGL() -- Context Information:";
//  qDebug() << "  Context Valid: " << std::string(curContext->isValid() ? "true" : "false").c_str();
//  qDebug() << "  GL Version Used: " << curContext->format().majorVersion() << "." << curContext->format().minorVersion();
//  qDebug() << "  Vendor: " << reinterpret_cast<const char*>(glGetString(GL_VENDOR));
//  qDebug() << "  Renderer: " << reinterpret_cast<const char*>(glGetString(GL_RENDERER));
//  qDebug() << "  Version: " << reinterpret_cast<const char*>(glGetString(GL_VERSION));
//  qDebug() << "  GLSL Version: " << reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
//
//  glViewport(0, 0, width(), height());
//}
//
//void BasicWidget::resizeGL(int w, int h)
//{
//  glViewport(0, 0, w, h);
//}
//
//void BasicWidget::paintGL()
//{
//  glDisable(GL_DEPTH_TEST);
//  glDisable(GL_CULL_FACE);
//
//  glClearColor(0.f, 0.f, 0.f, 1.f);
//  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//  // TODO:  render.
//}
