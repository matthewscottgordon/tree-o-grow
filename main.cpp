#include "MainWindow.h"

#include <QApplication>

int main( int argc, char *argv[] )
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Tree-o-Grow");
    QCoreApplication::setApplicationVersion("0.1");

    MainWindow mainWindow;
    mainWindow.show();
    
    return app.exec();
}
