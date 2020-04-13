// /**
//  * Support code written by Erik W. Anderson
//  */

#include <QtCore>
#include <QtGui>
#include <QtOpenGL>
#include <map> 

// Lab application
#include "App.h"

#include "ObjReader.h"
#include <iostream>

static bool enableGLDebug = true;

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    QString appDir = a.applicationDirPath();
    QDir::setCurrent(appDir);

    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    fmt.setStencilBufferSize(8);
    fmt.setVersion(3, 3);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    if (enableGLDebug)
    {
        fmt.setOption(QSurfaceFormat::DebugContext);
    }
    QSurfaceFormat::setDefaultFormat(fmt);
    std::cout << "My argument is: " << argv[1] << "\n";
    App app;

    app.show();




    return QApplication::exec();
}