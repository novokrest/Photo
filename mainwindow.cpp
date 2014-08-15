#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chdkptpmanager.h"

#include <QtCore/QString>
#include <QtCore/QSignalMapper>
#include <QtConcurrent/QtConcurrent>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QAction>

MainWindow::MainWindow():
    QMainWindow(),
    m_ui(new Ui::MainWindow),
    m_chdkptp(new ChdkPtpManager)
{
    m_ui->setupUi(this);

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);

    // http://qt-project.org/forums/viewthread/2884
    qRegisterMetaType<CameraList>("CameraList");

    // List of cameras
    m_ui->camerasTableWidget->setHorizontalHeaderLabels({tr("Index"), tr("Bus/Device"), tr("Serial Number")});
    connect(m_ui->actionReloadCameras, SIGNAL(triggered()), this, SLOT(slotReloadCameras()));
//     connect(m_chdkptp, SIGNAL(queryCamerasReady(CameraInfoList)), this, SLOT(slotReloadCamerasReady(CameraInfoList)));

    // Shooting process
    connect(m_ui->actionShoot, SIGNAL(triggered()), this, SLOT(slotStartShooting()));

    // Check propsets
    connect(m_ui->actionDiagnose, SIGNAL(triggered()), this, SLOT(slotDiagnose()));

    connect(&m_listCamerasWatcher, SIGNAL(finished()), this, SLOT(slotListCamerasReady()));

    // Set up Tv slider
    // TBD: verify if all these Tv values are supported on Canon PowerShot A1400
    QStringList tvValues;
    for (int tv96 = -576; tv96 <= 960; tv96 += 32) {
        double tvSec = pow(2, static_cast<double>(tv96) / (-96.0));
        if (tv96 <= 0)
            tvValues << tr("%1 s").arg(tvSec);
        else
            tvValues << tr("1/%1 s").arg(1.0 / tvSec);
    }
    m_ui->tvSlider->setValues(tvValues);
    m_ui->tvSlider->setSliderValue(32); // 1/25.4

    // Set up Av slider
    // TBD: verify if all these Av values are supported on Canon PowerShot A1400
    QStringList avValues;
    for (int av96 = 0; av96 <= 960; av96 += 32) {
        double fn = pow(2, static_cast<double>(av96) / 96.0 / 2.0);
        avValues << tr("f/%1").arg(QString::number(fn, 'f', 1));
    }
    m_ui->avSlider->setValues(avValues);
    m_ui->avSlider->setSliderValue(9); // f/2.8

    // Set up Sv slider
    // TBD: verify if all these Sv values are supported on Canon PowerShot A1400
    QStringList svValues;
    for (int sv96 = 384; sv96 <= 960; sv96 += 32) {
        double iso = 3.125 * pow(2, static_cast<double>(sv96) / 96.0);
        svValues << tr("ISO %1").arg(QString::number(iso, 'f', 0));
    }
    m_ui->isoSlider->setValues(svValues);
    m_ui->isoSlider->setSliderValue(3); // ISO 100
}

MainWindow::~MainWindow()
{
}

void MainWindow::slotReloadCameras()
{
    m_ui->camerasTableWidget->clearContents();
    m_ui->camerasTableWidget->clearSpans();
    m_ui->camerasTableWidget->setRowCount(0);

    m_listCamerasFuture = QtConcurrent::run(m_chdkptp, &ChdkPtpManager::listCameras);
    m_listCamerasWatcher.setFuture(m_listCamerasFuture);
}

// void MainWindow::slotReloadCamerasReady(CameraInfoList result)
// {
//     m_ui->camerasTableWidget->clearContents();
//     m_ui->camerasTableWidget->clearSpans();
// 
//     int count = result.size();
//     m_ui->camerasTableWidget->setRowCount(count);
//     for (int i = 0; i < count; ++i) {
//         CameraInfo cam = result.at(i);
//         m_ui->camerasTableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(cam.index)));
//         m_ui->camerasTableWidget->setItem(i, 1, new QTableWidgetItem(QString()));
//         m_ui->camerasTableWidget->setItem(i, 2, new QTableWidgetItem(cam.serialNumber));
//     }
// 
//     if (result.size() == 0) {
//         // http://www.codeprogress.com/cpp/libraries/qt/showQtExample.php?index=201&key=QTableWidgetMergeCells
//         m_ui->camerasTableWidget->setRowCount(1);
// 
//         QTableWidgetItem* item = new QTableWidgetItem("No cameras connected");
//         item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//         QFont font = item->font();
//         font.setItalic(true);
//         item->setFont(font);
//         m_ui->camerasTableWidget->setItem(0, 0, item);
//         m_ui->camerasTableWidget->setSpan(0, 0, 1, 3);
//     }
// }

void MainWindow::slotListCamerasReady()
{
    m_cameras = m_listCamerasWatcher.future().result();

    m_ui->camerasTableWidget->clearContents();
    m_ui->camerasTableWidget->clearSpans();

    int count = m_cameras.size();
    m_ui->camerasTableWidget->setRowCount(count);
    for (int i = 0; i < count; ++i) {
        Camera cam = m_cameras.at(i);
        m_ui->camerasTableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(i)));
        m_ui->camerasTableWidget->setItem(i, 1, new QTableWidgetItem(QString("%1/%2").arg(cam.bus()).arg(cam.dev())));
//         m_ui->camerasTableWidget->setItem(i, 2, new QTableWidgetItem(cam.serialNumber));
    }

    if (m_cameras.size() == 0) {
        // http://www.codeprogress.com/cpp/libraries/qt/showQtExample.php?index=201&key=QTableWidgetMergeCells
        m_ui->camerasTableWidget->setRowCount(1);

        QTableWidgetItem* item = new QTableWidgetItem("No cameras connected");
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QFont font = item->font();
        font.setItalic(true);
        item->setFont(font);
        m_ui->camerasTableWidget->setItem(0, 0, item);
        m_ui->camerasTableWidget->setSpan(0, 0, 1, 3);
    }

    for (int i = 0; i < count; ++i) {
        connect(&m_cameras.at(i), SIGNAL(serialNumberReady(QString)), this, SLOT(serialNumberReady(QString)));
        m_cameras[i].startSerialNumberQuery();
    }
}

void MainWindow::slotStartShooting()
{
    m_chdkptp->setTv96(-576 + 32 * m_ui->tvSlider->sliderValue());
    m_chdkptp->setAv96(32 * m_ui->avSlider->sliderValue());
    m_chdkptp->setSv96(384 + 32 * m_ui->isoSlider->sliderValue());

    QtConcurrent::run(m_chdkptp, &ChdkPtpManager::startShooting);
}

void MainWindow::slotDiagnose()
{
    QtConcurrent::run(m_chdkptp, &ChdkPtpManager::startDiagnose);
}

void MainWindow::serialNumberReady(const QString& sn)
{
    Camera* c = dynamic_cast<Camera*>(sender());
    auto it = std::find(m_cameras.begin(), m_cameras.end(), *c);
    if (it == m_cameras.end()) {
        qDebug() << "camera not found: 1nah";
        return;
    }

    int index = it - m_cameras.begin();

    m_ui->camerasTableWidget->setItem(index, 2, new QTableWidgetItem(sn));
}

#include "mainwindow.moc"
