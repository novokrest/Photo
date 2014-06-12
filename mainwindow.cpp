#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chdkptpmanager.h"
#include "multicamshooter.h"

#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QtConcurrent/QtConcurrent>

MainWindow::MainWindow():
    QMainWindow(),
    m_ui(new Ui::MainWindow),
    m_chdkptp(new ChdkPtpManager)
{
    m_ui->setupUi(this);

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);

    // List of cameras
    m_ui->camerasTableWidget->setHorizontalHeaderLabels({"Index", "Serial Number"});
    connect(m_ui->actionReloadCameras, SIGNAL(triggered()), this, SLOT(slotReloadCameras()));
    connect(m_chdkptp, SIGNAL(queryCamerasReady(QList<CameraInfo>)), this, SLOT(slotReloadCamerasReady(QList<CameraInfo>)));

    // Shooting process
    connect(m_ui->actionShoot, SIGNAL(triggered()), this, SLOT(slotStartShooting()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::slotReloadCameras()
{
    m_chdkptp->slotStartQueryCameras();
}

void MainWindow::slotReloadCamerasReady(QList<CameraInfo> result)
{
    m_ui->camerasTableWidget->clearContents();
    m_ui->camerasTableWidget->setRowCount(result.size());
    for (int i = 0; i < result.size(); ++i) {
        CameraInfo cam = result.at(i);
        m_ui->camerasTableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(cam.index)));
        m_ui->camerasTableWidget->setItem(i, 1, new QTableWidgetItem(cam.serialNumber));
    }
}

void MainWindow::slotStartShooting()
{
    QtConcurrent::run(m_chdkptp, &ChdkPtpManager::startShooting);
}

#include "mainwindow.moc"
