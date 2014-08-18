#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chdkptpmanager.h"

#include <QtWidgets/QMainWindow>
#include <QtCore/QFutureWatcher>

class QTableWidgetItem;
class QSignalMapper;

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
//     void slotReloadCamerasReady(CameraInfoList result);

    void slotListCamerasReady();

    void slotStartShooting();

    void slotCameraDoubleClicked(QTableWidgetItem* item);

    void slotDiagnose();

private slots:
    void serialNumberReady(const QString& sn);

private:
    Ui::MainWindow* m_ui;

    ChdkPtpManager* m_chdkptp;

    QFuture<CameraList> m_listCamerasFuture;
    QFutureWatcher<CameraList> m_listCamerasWatcher;
};

#endif // MAINWINDOW_H
