#include <QtWidgets/QApplication>
#include "mainwindow.h"
#include "utils.h"

int main(int argc, char** argv)
{
//    std::string executableDir = getExecutableDir();
//    qDebug() << QString(executableDir.c_str());
    QApplication app(argc, argv);
    MainWindow win;
    win.show();
    return app.exec(); 
}
