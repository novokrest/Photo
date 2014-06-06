#include <QtGui/QApplication>
#include "photobooth.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    photobooth foo;
    foo.show();
    return app.exec();
}
