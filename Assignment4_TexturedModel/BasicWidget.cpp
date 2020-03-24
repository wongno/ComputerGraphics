#include "BasicWidget.h"
#include <iostream>
#include <vector>

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent), logger_(this)
{

    setFocusPolicy(Qt::StrongFocus);
}

BasicWidget::~BasicWidget()
{
    for (auto renderable : renderables_)
    {
        delete renderable;
    }
    renderables_.clear();
}


//////////////////////////////////////////////////////////////////////
// Privates
///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent)
{
    // Handle key events here.
    if (keyEvent->key() == Qt::Key_Q)
    {
        exit(1);
    }
    else if (keyEvent->key() == Qt::Key_W)
    {
        qDebug() << "W Pressed";
        if (frameType == 1)
        {
            BasicWidget::setWireframe(2);
        }
        else
        {
            BasicWidget::setWireframe(1);
        }
        update(); // We call update after we handle a key press to trigger a redraw when we are ready
    }
    else
    {
        qDebug() << "You Pressed an unsupported Key!";
    }
}
void BasicWidget::initializeGL()
{
    makeCurrent();
    initializeOpenGLFunctions();

    qDebug() << QDir::currentPath();

    QStringList d = QCoreApplication::arguments();


    ObjReader house = ObjReader(d.at(1).toUtf8().constData());

    std::string texturePath = house.getMtlFilepath();
    QString texFile = QString::fromUtf8(texturePath.c_str());;


    std::vector<float> vertexInfo = house.getVerticesAndTextures();

    std::vector<unsigned int> faces = house.getFaces();

    Renderable* ren = new Renderable();
    ren->init(vertexInfo, faces, texFile);

    renderables_.push_back(ren);
    glViewport(0, 0, width(), height());

}

void BasicWidget::resizeGL(int w, int h)
{
    if (!logger_.isLogging())
    {
        logger_.initialize();
        // Setup the logger for real-time messaging
        connect(&logger_, &QOpenGLDebugLogger::messageLogged, [=]() {
            const QList<QOpenGLDebugMessage> messages = logger_.loggedMessages();
            for (auto msg : messages)
            {
                qDebug() << msg;
            }
            });
        logger_.startLogging();
    }
    glViewport(0, 0, w, h);
    view_.setToIdentity();
    view_.lookAt(QVector3D(-5.0f, 1.0f, 1.0f),
        QVector3D(0.0f, 1.0f, 0.0f),
        QVector3D(0.0f, 1.0f, 0.0f));
    projection_.setToIdentity();
    projection_.perspective(90.f, (float)w / (float)h, 0.001, 1000.0);
    glViewport(0, 0, w, h);
}

void BasicWidget::paintGL()
{
    // qint64 msSinceRestart = frameTimer_.restart();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (frameType == 1)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (frameType == 2)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    for (auto renderable : renderables_)
    {
        // renderable->update(msSinceRestart);
        renderable->draw(view_, projection_);
    }
    update();
}