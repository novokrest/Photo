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

static const int INDEX_COLUMN        = 0;
static const int BUSDEV_COLUMN       = 1;
static const int SERIALNUMBER_COLUMN = 2;


class MainWindow : public QMainWindow
{
Q_OBJECT

    typedef std::vector<int> vint;
    typedef std::vector<Camera> CameraVec;

    Ui::MainWindow* m_ui;

    ChdkPtpManager* m_chdkptp;

    QFuture<CameraList> m_listCamerasFuture;
    QFutureWatcher<CameraList> m_listCamerasWatcher;

    void initGUI();
    void initCamerasTable();
    void initSliders();
    void initSliderAv();
    void initSliderSv();
    void initSliderTv();
    void initSliderDelay();

    void initConnects();

public:
    MainWindow();
    virtual ~MainWindow();

public slots:
    void slotReloadCameras();
//     void slotReloadCamerasReady(CameraInfoList result);

    void slotListCamerasReady();

    void slotStartShooting();
    void slotStartSelectedCameraShooting();
    void updateSettings();
    void slotShutdownAll();

    void slotCameraDoubleClicked(QTableWidgetItem* item);

    void slotDiagnose();
    void slotConfigureStaticProps();

    void slotFlashModeChanged(int state);
    void slotPreshootChanged(int state);

    void slotDownloadLastPhotos();
    void slotManualFocusChanged(int state);

private slots:
    void serialNumberReady(const QString& sn);
};

#endif // MAINWINDOW_H
