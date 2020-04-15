#include "BasicWidget.h"




//////////////////////////////////////////////////////////////////////
// Publics
BasicWidget::BasicWidget(QWidget* parent) : QOpenGLWidget(parent), logger_(this)
{
    setFocusPolicy(Qt::StrongFocus);
    camera_.setPosition(QVector3D(0, 40, 0));
    camera_.setLookAt(QVector3D(1, 10, 0.0));
    world_.setToIdentity();
}

BasicWidget::~BasicWidget()
{
    delete root_;
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
        qDebug() << "Left Arrow Pressed";
        update(); // We call update after we handle a key press to trigger a redraw when we are ready
    }
    else if (keyEvent->key() == Qt::Key_Right)
    {
        qDebug() << "Right Arrow Pressed";
        update(); // We call update after we handle a key press to trigger a redraw when we are ready
    }
    else if (keyEvent->key() == Qt::Key_R)
    {
        camera_.setPosition(QVector3D(0, 40, 0));
        camera_.setLookAt(QVector3D(1, 10, 0.0));
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

    // create the sun
    QMatrix4x4 identity;
    identity.setToIdentity();

    QString texFile = "../sun.ppm";
    TreeNode* sun = new TreeNode();
    sun->init(texFile, "sun", identity, 4);

    // create earth1
    QString earthTex = "../earth.ppm";
    QMatrix4x4 earthMatrix;
    earthMatrix.setToIdentity();
    earthMatrix.translate(QVector3D(10, 0, 0));

    TreeNode* earthNode = new TreeNode();
    earthNode->init(earthTex, "earth", earthMatrix, 1.5);

    // create earth2
    QMatrix4x4 earthMatrix2;
    earthMatrix2.setToIdentity();
    earthMatrix.translate(QVector3D(15, 0, 0));

    TreeNode* earthNode2 = new TreeNode();
    earthNode2->init(earthTex, "earth", earthMatrix, 2);

    // create a mercury
    QString mercuryTex = "../mercury.ppm";
    QMatrix4x4 mercuryMatrix;
    mercuryMatrix.setToIdentity();
    mercuryMatrix.translate(QVector3D(5, 0, 7));

    TreeNode* mercuryNode = new TreeNode();
    mercuryNode->init(mercuryTex, "mercury", mercuryMatrix, 1);

    // create moons moon

    QString rockTex = "../rock.ppm";
    QMatrix4x4 moonMatrix;
    moonMatrix.setToIdentity();
    moonMatrix.translate(QVector3D(2, 0, 0));

    TreeNode* moonNode = new TreeNode();
    moonNode->init(rockTex, "moonforearth", moonMatrix, .5);

    TreeNode* moonNodeMerc = new TreeNode();
    moonNodeMerc->init(rockTex, "moonformerc", moonMatrix, .5);

    QMatrix4x4 moonMatrix2;
    moonMatrix2.setToIdentity();
    moonMatrix2.translate(QVector3D(2, 0, 2));

    TreeNode* moonNode2 = new TreeNode();
    moonNode2->init(rockTex, "moon2forearth", moonMatrix2, .5);

    TreeNode* moonNodeMerc2 = new TreeNode();
    moonNodeMerc2->init(rockTex, "moon2merc2", moonMatrix2, .5);

    QMatrix4x4 mercMoonMatrix2;
    mercMoonMatrix2.setToIdentity();
    mercMoonMatrix2.translate(QVector3D(3.3, 0, 1));

    TreeNode* moonNodeMerc3 = new TreeNode();
    moonNodeMerc3->init(rockTex, "moon2merc2", mercMoonMatrix2, .7);

    QMatrix4x4 moonMatrix3;
    moonMatrix3.setToIdentity();
    moonMatrix3.translate(QVector3D(9, 0, 2));


    TreeNode* farMoonNode = new TreeNode();
    farMoonNode->init(rockTex, "farmoon", moonMatrix3, .5);

    earthNode->addChild(moonNode);
    earthNode->addChild(moonNode2);

    mercuryNode->addChild(moonNodeMerc);
    mercuryNode->addChild(moonNodeMerc2);
    mercuryNode->addChild(moonNodeMerc3);

    earthNode2->addChild(farMoonNode);


    sun->addChild(earthNode);
    sun->addChild(earthNode2);
    sun->addChild(mercuryNode);


    root_ = new Tree();
    root_->setRoot(sun);


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

    root_->traverse(msSinceRestart, camera_.getViewMatrix(), camera_.getProjectionMatrix());


    update();
}
