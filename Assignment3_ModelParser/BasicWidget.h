#pragma once

#include <QtGui>
#include <QtWidgets>
#include <QtOpenGL>
#include <Obj.h>

// TODO:  This macro should work when both true AND false
#define USE_QT_OPENGL true
// ENDTODO

/**
 * This is just a basic OpenGL widget that will allow a change of background color.
 */
class BasicWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

private:
    QString vertexShaderString() const;
    QString fragmentShaderString() const;
    void createShader();
    QOpenGLVertexArrayObject vao_;
    Obj mon = Obj("./objects/monkey_centered.obj");
    Obj bun = Obj("./objects/bunny_centered.obj");
   
    unsigned int objectType = 1;
    unsigned int frameType = 1;
    Obj o = mon;


protected:
    // Required interaction overrides
    void keyReleaseEvent(QKeyEvent* keyEvent) override;

    // Required overrides form QOpenGLWidget
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    QOpenGLBuffer vbo_;
    QOpenGLBuffer ibo_;
    QOpenGLBuffer cbo_;
    QOpenGLShaderProgram shaderProgram_;




public:
    BasicWidget(QWidget* parent = nullptr);
    
    virtual ~BasicWidget();

    // Make sure we have some size that makes sense.
    QSize sizeHint() const { return QSize(800, 600); }
    
    void setShapeType(int type)
    {
        // if type = 1 then bunny, if type = 2, then monkey
        if (type == 1)
        {
            o = mon;
            objectType = type;
        }

        else
        {
            objectType = type;
            o = bun;
        }
    }

    void setWireframe(int type)
    {
        // if type = 1 then solid, if type = 2, then wireframe
        frameType = type;
    }
};

