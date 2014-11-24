#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chdkptpmanager.h"

#include <cstring>

#include <QtCore/QString>
#include <QtCore/QSignalMapper>
#include <QtConcurrent/QtConcurrent>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QAction>
#include <QtWidgets/QMessageBox>


MainWindow::MainWindow():
    QMainWindow(),
    m_ui(new Ui::MainWindow),
    m_chdkptp(new ChdkPtpManager)
{
    m_ui->setupUi(this);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);

    initGUI();
    initConnects();
}

void MainWindow::initGUI()
{
    initCamerasTable();
    initSliderAv();
    initSliderSv();
    initSliderTv();
    initSliderDelay();
}

void MainWindow::initConnects()
{
    //Actions
    connect(m_ui->actionReloadCameras, SIGNAL(triggered()), this, SLOT(slotReloadCameras()));
    connect(m_chdkptp, SIGNAL(signalCamerasListReady()), this, SLOT(slotCamerasListReady()));

    connect(m_ui->actionGetAdditionalCamerasInfo, SIGNAL(triggered()), this, SLOT(slotGetAdditionalCamerasInfo()));
    connect(m_chdkptp, SIGNAL(signalAdditionalCamerasInfoReady()), this, SLOT(slotAdditionalCamerasInfoReady()));

    connect(m_ui->actionApplyShootingSettings, SIGNAL(triggered()), this, SLOT(slotApplyShootingSettings()));
    connect(m_chdkptp, SIGNAL(signalSettingsApplied()), this, SLOT(slotShootingSettingsApplied()));

    connect(m_ui->actionShoot, SIGNAL(triggered()), this, SLOT(slotStartShooting()));
    connect(m_chdkptp, SIGNAL(signalShootingDone()), this, SLOT(slotShootingDone()));

    connect(m_ui->actionDownloadLastPhotos, SIGNAL(triggered()), this, SLOT(slotDownloadLastPhotos()));
    connect(m_chdkptp, SIGNAL(signalDownloadPhotosDone()), this, SLOT(slotDownloadPhotosDone()));

    // Shooting process
    //connect(m_ui->actionShoot, SIGNAL(triggered()), this, SLOT(slotStartShooting()));
    //connect(m_ui->actionSelectedCameraShoot, SIGNAL(triggered()), this, SLOT(slotStartSelectedCameraShooting()));

    // Turn off all cameras
    connect(m_ui->actionShutdownAll, SIGNAL(triggered()), this, SLOT(slotShutdownAll()));

    // Check propsets
    connect(m_ui->actionDiagnose, SIGNAL(triggered()), this, SLOT(slotDiagnose()));
    connect(m_ui->actionConfigureStaticProps, SIGNAL(triggered()), this, SLOT(slotConfigureStaticProps()));

    // Hightlight camera
    connect(m_ui->camerasTableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(slotCameraDoubleClicked(QTableWidgetItem*)));

    //Flash mode
    connect(m_ui->flashCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slotFlashModeChanged(int)));
    //Preshoot
    connect(m_ui->preshootCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slotPreshootChanged(int)));

    //Focus mode
    connect(m_ui->manualFocusCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slotManualFocusChanged(int)));
}

void MainWindow::initCamerasTable()
{
    QStringList headers({"id", "bus", "dev", "vendor_id", "product_id", "serial_number", "model", "device_version", "manufacturer"});
    m_ui->camerasTableWidget->setHorizontalHeaderLabels(headers);

    //TODO: why this doesn't work?
    QTableWidgetItem* protoItem = new QTableWidgetItem();
    protoItem->setTextAlignment(Qt::AlignHCenter);
    m_ui->camerasTableWidget->setItemPrototype(protoItem);
}

void MainWindow::initSliderAv()
{
    // Set up Av slider
    // TBD: verify if all these Av values are supported on Canon PowerShot A1400
    vint avValues = {347, 384, 417, 446, 477, 510, 543, 576};
    QStringList avLabels = {"f/3.4", "f/4.0", "f/4.5", "f/5.0", "f/5.6", "f/6.3", "f/7.1", "f/8.0"};
//    for (int av96 = 0; av96 <= 960; av96 += 32) {
//        avValues.push_back(av96);
//        double fn = pow(2, static_cast<double>(av96) / 96.0 / 2.0);
//        avLabels.push_back(tr("f/%1").arg(QString::number(fn, 'f', 1)));
//    }
    m_ui->avSlider->setValues(avValues, avLabels);
    m_ui->avSlider->setSliderPosition(0); // f/2.8
}

void MainWindow::initSliderTv()
{
    // Set up Tv slider
    // TBD: verify if all these Tv values are supported on Canon PowerShot A1400
    vint tvValues;
    QStringList tvLabels;
    for (int tv96 = -576; tv96 <= 960; tv96 += 32) {
        tvValues.push_back(tv96);
        double tvSec = pow(2, static_cast<double>(tv96) / (-96.0));
        if (tv96 <= 0)
            tvLabels << tr("%1 s").arg(tvSec);
        else
            tvLabels << tr("1/%1 s").arg(1.0 / tvSec);
    }
    m_ui->tvSlider->setValues(tvValues, tvLabels);
    m_ui->tvSlider->setSliderPosition(32); // 1/25.4

}

void MainWindow::initSliderSv()
{
    // Set up Sv slider
    // TBD: verify if all these Sv values are supported on Canon PowerShot A1400
    vint svValues = {0, 1, 2, 3, 4, 5, 6};
    QStringList svLabels({"AUTO", "ISO 80", "ISO 100", "ISO 200", "ISO 400", "ISO 800", "ISO 1600"});
//    for (int sv96 = 384; sv96 <= 960; sv96 += 32) {
//        svValues.push_back(sv96);
//        double iso = 3.125 * pow(2, static_cast<double>(sv96) / 96.0);
//        svLabels << tr("ISO %1").arg(QString::number(iso, 'f', 0));
//    }
    m_ui->isoSlider->setValues(svValues, svLabels);
    m_ui->isoSlider->setSliderPosition(3); // ISO 200
}

void MainWindow::initSliderDelay()
{
    //Set up delay slider
    vint delayValues;
    QStringList delayLabels;
    for (int delay = 0; delay < 11; ++delay) {
        delayValues.push_back(delay);
        delayLabels.push_back(tr("%1s").arg(QString::number(delay)));
    }
    m_ui->delaySlider->setValues(delayValues, delayLabels);
    m_ui->delaySlider->setSliderPosition(0);
}

void MainWindow::initSliders()
{
}

MainWindow::~MainWindow()
{
}

void MainWindow::slotReloadCameras()
{
    m_ui->camerasTableWidget->clearContents();
    m_ui->camerasTableWidget->clearSpans();
    m_ui->camerasTableWidget->setRowCount(0);

    QtConcurrent::run(m_chdkptp, &ChdkPtpManager::listCameras);
}

void MainWindow::slotCamerasListReady()
{
    m_ui->camerasTableWidget->clearContents();
    m_ui->camerasTableWidget->clearSpans();

    int count = m_chdkptp->m_cameras.size();

    if (count == 0) {
        QTableWidgetItem* item = new QTableWidgetItem("No cameras connected");
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QFont font = item->font();
        font.setItalic(true);
        item->setFont(font);

        m_ui->camerasTableWidget->setRowCount(1);
        m_ui->camerasTableWidget->setItem(0, 0, item);
        m_ui->camerasTableWidget->setSpan(0, 0, 1, m_ui->camerasTableWidget->columnCount());
        return;
    }

    m_ui->camerasTableWidget->setRowCount(count);
    for (int i = 0; i < count; ++i) {
        Camera cam = m_chdkptp->m_cameras.at(i);
        m_ui->camerasTableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(i)));
        m_ui->camerasTableWidget->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(cam.bus())));
        m_ui->camerasTableWidget->setItem(i, 2, new QTableWidgetItem(QString("%1").arg(cam.dev())));
        m_ui->camerasTableWidget->setItem(i, 3, new QTableWidgetItem(QString("%1").arg(cam.vendorId())));
        m_ui->camerasTableWidget->setItem(i, 4, new QTableWidgetItem(QString("%1").arg(cam.productId())));
    }
}

void MainWindow::slotGetAdditionalCamerasInfo()
{
    QtConcurrent::run(m_chdkptp, &ChdkPtpManager::getAdditionalCamerasInfo);
}

void MainWindow::slotAdditionalCamerasInfoReady()
{
    int count = m_chdkptp->m_cameras.size();
    for (int i = 0; i < count; ++i) {
        Camera cam = m_chdkptp->m_cameras.at(i);
        m_ui->camerasTableWidget->setItem(i, 5, new QTableWidgetItem(QString("%1").arg(cam.serial())));
        m_ui->camerasTableWidget->setItem(i, 6, new QTableWidgetItem(QString("%1").arg(cam.modelName())));
        m_ui->camerasTableWidget->setItem(i, 7, new QTableWidgetItem(QString("%1").arg(cam.deviceV())));
        m_ui->camerasTableWidget->setItem(i, 8, new QTableWidgetItem(QString("%1").arg(cam.manufacturer())));
    }
}

void MainWindow::slotApplyShootingSettings()
{
    Settings settings;
    collectSettings(settings);
    m_chdkptp->setSettings(settings);

//    QtConcurrent::run(m_chdkptp, &ChdkPtpManager::applySettings);
}

void MainWindow::collectSettings(Settings& settings)
{
    settings.multicamMode = m_ui->multicamCheckBox->isChecked();
    settings.preshoot = m_ui->preshootCheckBox->isChecked();
    settings.flash = m_ui->flashCheckBox->isChecked();
    settings.av96 = m_ui->avSlider->sliderValue();
    settings.tv96 = m_ui->tvSlider->sliderValue();
    settings.isoMode = m_ui->isoSlider->sliderValue();
    settings.manualFocus = m_ui->manualFocusCheckBox->isChecked();
    settings.focus = m_ui->focusSpinBox->value();
    settings.delay = m_ui->delaySlider->sliderValue();
    //settings.zoom = m_ui->zoom
}

void MainWindow::slotShootingSettingsApplied()
{
    qDebug() << "Settings are applied succesfully";
}

void MainWindow::slotStartShooting()
{
    if (m_chdkptp->m_cameras.size() == 0) {
        QMessageBox::warning(
                    this,
                    tr("Shooting Failed"),
                    tr("No cameras were previously discovered. Please connect the cameras and click 'Update the list of cameras' and then try shooting again."));
        return;
    }

    slotApplyShootingSettings();
    QtConcurrent::run(m_chdkptp, &ChdkPtpManager::startMulticamShooting);
}

void MainWindow::slotShootingDone()
{
    qDebug() << "Shooting is done";
}

void MainWindow::slotDownloadLastPhotos()
{
    QtConcurrent::run(m_chdkptp, &ChdkPtpManager::startDownloadRecentPhotos);
}

void MainWindow::slotDownloadPhotosDone()
{}

void MainWindow::updateSettings()
{
    m_chdkptp->setTv96(-576 + 32 * m_ui->tvSlider->sliderValue());
    m_chdkptp->setAv96(32 * m_ui->avSlider->sliderValue());
    m_chdkptp->setSv96(384 + 32 * m_ui->isoSlider->sliderValue());
    m_chdkptp->setDelay(m_ui->delaySlider->sliderValue());
}

void MainWindow::slotStartSelectedCameraShooting()
{
    qDebug() << "selected camera shoot";

    QList<QTableWidgetItem*> selectedItems = m_ui->camerasTableWidget->selectedItems();
    if (selectedItems.size() != 1) {
        qDebug() << "To many items selected: " << selectedItems.size();
        return;
    }

    QTableWidgetItem* selectedItem = selectedItems.at(0);
    if (selectedItem->column() != BUSDEV_COLUMN) {
        qDebug() << "Uncorrect item column: " << selectedItem->column();
        return;
    }

    int selectedIndex = selectedItem->row();

    auto it = std::find_if(m_chdkptp->m_cameras.begin(), m_chdkptp->m_cameras.end(),
                           [selectedItem](Camera const & camera) { return selectedItem->text() == camera.uid(); });

    if (it == m_chdkptp->m_cameras.end()) {
        qDebug() << "No camera has uid = " << selectedItem->text();
        return;
    }

    int cameraIndex = it - m_chdkptp->m_cameras.begin();
    assert(selectedIndex == cameraIndex);

    updateSettings();
    m_chdkptp->runCustomScript();
}

void MainWindow::slotShutdownAll()
{
    QtConcurrent::run(m_chdkptp, &ChdkPtpManager::shutdownAll);
}

void MainWindow::slotDiagnose()
{
    QtConcurrent::run(m_chdkptp, &ChdkPtpManager::startDiagnose);
}

void MainWindow::slotConfigureStaticProps()
{
    QtConcurrent::run(m_chdkptp, &ChdkPtpManager::startConfigureStaticProps);
}

void MainWindow::serialNumberReady(const QString& sn)
{
    Camera* c = dynamic_cast<Camera*>(sender());
    auto it = std::find(m_chdkptp->m_cameras.begin(), m_chdkptp->m_cameras.end(), *c);
    if (it == m_chdkptp->m_cameras.end()) {
        qDebug() << "camera not found: 1nah";
        return;
    }

    m_ui->camerasTableWidget->setItem(it->index(), 2, new QTableWidgetItem(sn));
}

void MainWindow::slotCameraDoubleClicked(QTableWidgetItem* item)
{
    qDebug() << item->text() << " doubleclicked";

    auto it = std::find_if(
                m_chdkptp->m_cameras.begin(), m_chdkptp->m_cameras.end(),
                [item](const Camera& c) {
        return item->text() == c.uid();
    });
    if (it == m_chdkptp->m_cameras.end()) {
        qDebug() << "camera not found: 2nah";
        return;
    }

    int index = it - m_chdkptp->m_cameras.begin();

    m_chdkptp->highlightCamera(index);
}

void MainWindow::slotFlashModeChanged(int state)
{
    m_chdkptp->setFlashMode(state);
}

void MainWindow::slotPreshootChanged(int state)
{
    m_chdkptp->setPreshootMode(state);
}

void MainWindow::slotManualFocusChanged(int state)
{
    m_ui->focusSpinBox->setEnabled(state);
}

#include "mainwindow.moc"
