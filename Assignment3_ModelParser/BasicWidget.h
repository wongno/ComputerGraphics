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
    int dir = 3;
    Obj o = Obj("./objects/bunny.obj");


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

    void setDir(int x) {
        dir = x;
    }

    int getDir() {
        return dir;
    }

    // Make sure we have some size that makes sense.
    QSize sizeHint() const { return QSize(800, 600); }
};

//#pragma once
//
//#include <QtGui>
//#include <QtWidgets>
//#include <QtOpenGL>
//#include <QtCore/QObject>
//
//#define USE_QT_OPENGL true
///**
// * This is just a basic OpenGL widget that will allow a change of background color.
// */
//class BasicWidget : public QOpenGLWidget, protected QOpenGLFunctions
//{
//  Q_OBJECT
//
//private:
//
//protected:
//  // Required interaction overrides
//  void keyReleaseEvent(QKeyEvent* keyEvent) override;
//
//  // Required overrides form QOpenGLWidget
//  void initializeGL() override;
//  void resizeGL(int w, int h) override;
//  void paintGL() override;
//  QOpenGLBuffer vbo_;
//  QOpenGLBuffer ibo_;
//  QOpenGLBuffer cbo_;
//
//public:
//  BasicWidget(QWidget* parent=nullptr);
//  virtual ~BasicWidget();
//  
//  // Make sure we have some size that makes sense.
//  QSize sizeHint() const {return QSize(800,600);}
//};
