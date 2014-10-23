#include <QCoreApplication>
#include <QDebug>
#include "camera.h"
#include "chdkptpmanager.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ChdkPtpManager chdkptpManager;
    chdkptpManager.runCustomScript();

    return a.exec();
}


