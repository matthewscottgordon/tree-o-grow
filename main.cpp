#include "MainWindow.h"

#include <QApplication>
#include <QSurfaceFormat>

int main( int argc, char *argv[] )
{
    QSurfaceFormat format;
    format.setDepthBufferSize( 4 );
    format.setSamples(24);
    format.setVersion(3, 3);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile( QSurfaceFormat::CoreProfile );
    QSurfaceFormat::setDefaultFormat(format);

    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Tree-o-Grow");
    QCoreApplication::setApplicationVersion("0.1");

    MainWindow mainWindow;
    mainWindow.show();
    
    return app.exec();
}
