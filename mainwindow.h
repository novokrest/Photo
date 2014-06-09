#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chdkptpmanager.h"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class ChdkPtpManager;

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();

public slots:
    void slotReloadCameras();
    void slotReloadCamerasReady(QList<CameraInfo> result);

private:
    Ui::MainWindow* m_ui;

    ChdkPtpManager* m_chdkptp;
};

#endif // MAINWINDOW_H
