#include "BasicWidget.h"

#include "Renderable.h"

//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent), logger_(this)
{
    setFocusPolicy(Qt::StrongFocus);
    camera_.setPosition(QVector3D(0.5, 0.5, 2.0));
    camera_.setLookAt(QVector3D(0.5, 0.5, 0.0));
    world_.setToIdentity();
}

BasicWidget::~BasicWidget()
{
    delete renderable_;
}

//////////////////////////////////////////////////////////////////////
// Privates
///////////////////////////////////////////////////////////////////////
// Protected
void BasicWidget::keyReleaseEvent(QKeyEvent* keyEvent)
{
    // Handle key events here.
    if (keyEvent->key() == Qt::Key_Left)
    {
        // rotate object by 4 degrees on y axis
        renderable_->update(4);
        update(); // We call update after we handle a key press to trigger a redraw when we are ready
    }
    else if (keyEvent->key() == Qt::Key_Right)
    {
        // rotate object by 4 degrees on y axis
        renderable_->update(-4);
        update(); // We call update after we handle a key press to trigger a redraw when we are ready
    }
    else if (keyEvent->key() == Qt::Key_R)
    {
        camera_.setPosition(QVector3D(0.5, 0.5, 2.0));
        camera_.setLookAt(QVector3D(0.5, 0.5, 0.0));
        update();
    }
    else
    {
        qDebug() << "You Pressed an unsupported Key!";
    }
}

void BasicWidget::mousePressEvent(QMouseEvent* mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        mouseAction_ = Rotate;
    }
    else if (mouseEvent->button() == Qt::RightButton)
    {
        mouseAction_ = Zoom;
    }
    lastMouseLoc_ = mouseEvent->pos();
}

void BasicWidget::mouseMoveEvent(QMouseEvent* mouseEvent)
{
    if (mouseAction_ == NoAction)
    {
        return;
    }
    QPoint delta = mouseEvent->pos() - lastMouseLoc_;
    lastMouseLoc_ = mouseEvent->pos();

    if (mouseAction_ == Rotate)
    {

        float mouseSpeed = 0.005f;
        float horizontalAngle = mouseSpeed * float(width() / 2 - lastMouseLoc_.x());
        float verticalAngle = mouseSpeed * float(height() / 2 - lastMouseLoc_.y());

        camera_.translateLookAt(QVector3D(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle)));
    }
    else if (mouseAction_ == Zoom)
    {
        camera_.translateCamera(QVector3D(0, 0, delta.y()));
    }
    update();
}

void BasicWidget::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
    mouseAction_ = NoAction;
}

void BasicWidget::initializeGL()
{
    makeCurrent();
    initializeOpenGLFunctions();

    qDebug() << QDir::currentPath();
    // TODO:  You may have to change these paths.
    QStringList objPath = QCoreApplication::arguments();
    std::string stringpath;

    try
    {
        stringpath = objPath.at(1).toUtf8().constData();
    }
    catch (int e)
    {
        qDebug() << "Please pass in a valid file path";
        exit(e);
    }

    // create object from .obj specifications
    ObjReader house = ObjReader(stringpath);
    std::string texturePath = house.getMtlFilepath();
    QString texFile = QString::fromUtf8(texturePath.c_str());

    std::vector<float> vertexInfo = house.getVerticesAndTextures();

    std::vector<unsigned int> faces = house.getFaces();

    // create renderable object
    Renderable* object = new Renderable();
    object->init(vertexInfo, faces, texFile);

    renderable_ = object;

    glViewport(0, 0, width(), height());
    frameTimer_.start();
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

    camera_.setPerspective(70.f, (float)w / (float)h, 0.001, 1000.0);
    glViewport(0, 0, w, h);
}

void BasicWidget::paintGL()
{
    qint64 msSinceRestart = frameTimer_.restart();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    renderable_->draw(world_, camera_.getViewMatrix(), camera_.getProjectionMatrix());

    update();
}