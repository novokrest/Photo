/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <parameterslider.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionReloadCameras;
    QAction *actionShoot;
    QAction *actionDiagnose;
    QAction *actionConfigureStaticProps;
    QAction *actionShutdownAll;
    QAction *actionSelectedCameraShoot;
    QAction *actionDownloadLastPhotos;
    QAction *actionApplyShootingSettings;
    QAction *actionGetAdditionalCamerasInfo;
    QWidget *centralwidget;
    QDockWidget *camerasDockWidget;
    QWidget *camerasDockWidgetContents;
    QTableWidget *camerasTableWidget;
    QDockWidget *dockWidget_4;
    QWidget *dockWidgetContents_4;
    QCheckBox *flashCheckBox;
    QCheckBox *preshootCheckBox;
    QCheckBox *multicamCheckBox;
    QCheckBox *manualFocusCheckBox;
    QSpinBox *focusSpinBox;
    QDockWidget *shootingDockWidget;
    QWidget *shootingDockWidgetContents;
    ParameterSlider *tvSlider;
    ParameterSlider *avSlider;
    ParameterSlider *isoSlider;
    ParameterSlider *delaySlider;
    QDockWidget *dockWidget_3;
    QWidget *dockWidgetContents_3;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QMenuBar *menubar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1101, 846);
        MainWindow->setTabShape(QTabWidget::Rounded);
        MainWindow->setDockNestingEnabled(true);
        MainWindow->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        actionReloadCameras = new QAction(MainWindow);
        actionReloadCameras->setObjectName(QStringLiteral("actionReloadCameras"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/update.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReloadCameras->setIcon(icon);
        actionShoot = new QAction(MainWindow);
        actionShoot->setObjectName(QStringLiteral("actionShoot"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/multi-camera-photo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShoot->setIcon(icon1);
        actionDiagnose = new QAction(MainWindow);
        actionDiagnose->setObjectName(QStringLiteral("actionDiagnose"));
        actionDiagnose->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/document-export.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDiagnose->setIcon(icon2);
        actionConfigureStaticProps = new QAction(MainWindow);
        actionConfigureStaticProps->setObjectName(QStringLiteral("actionConfigureStaticProps"));
        actionConfigureStaticProps->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/applications-development.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConfigureStaticProps->setIcon(icon3);
        actionShutdownAll = new QAction(MainWindow);
        actionShutdownAll->setObjectName(QStringLiteral("actionShutdownAll"));
        actionShutdownAll->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/system-shutdown.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShutdownAll->setIcon(icon4);
        actionSelectedCameraShoot = new QAction(MainWindow);
        actionSelectedCameraShoot->setObjectName(QStringLiteral("actionSelectedCameraShoot"));
        actionSelectedCameraShoot->setEnabled(false);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/selected-camera-photo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelectedCameraShoot->setIcon(icon5);
        actionDownloadLastPhotos = new QAction(MainWindow);
        actionDownloadLastPhotos->setObjectName(QStringLiteral("actionDownloadLastPhotos"));
        actionDownloadLastPhotos->setEnabled(false);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icons/download-last-photos.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDownloadLastPhotos->setIcon(icon6);
        actionApplyShootingSettings = new QAction(MainWindow);
        actionApplyShootingSettings->setObjectName(QStringLiteral("actionApplyShootingSettings"));
        actionApplyShootingSettings->setEnabled(false);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icons/set-settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionApplyShootingSettings->setIcon(icon7);
        actionGetAdditionalCamerasInfo = new QAction(MainWindow);
        actionGetAdditionalCamerasInfo->setObjectName(QStringLiteral("actionGetAdditionalCamerasInfo"));
        actionGetAdditionalCamerasInfo->setEnabled(false);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/icons/extra-camera-info.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGetAdditionalCamerasInfo->setIcon(icon8);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        camerasDockWidget = new QDockWidget(centralwidget);
        camerasDockWidget->setObjectName(QStringLiteral("camerasDockWidget"));
        camerasDockWidget->setGeometry(QRect(10, 10, 1081, 229));
        camerasDockWidget->setMinimumSize(QSize(384, 183));
        camerasDockWidget->setFloating(false);
        camerasDockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
        camerasDockWidgetContents = new QWidget();
        camerasDockWidgetContents->setObjectName(QStringLiteral("camerasDockWidgetContents"));
        camerasTableWidget = new QTableWidget(camerasDockWidgetContents);
        if (camerasTableWidget->columnCount() < 9)
            camerasTableWidget->setColumnCount(9);
        camerasTableWidget->setObjectName(QStringLiteral("camerasTableWidget"));
        camerasTableWidget->setGeometry(QRect(9, 9, 1071, 192));
        camerasTableWidget->setMinimumSize(QSize(360, 0));
        camerasTableWidget->setLayoutDirection(Qt::LeftToRight);
        camerasTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        camerasTableWidget->setAlternatingRowColors(false);
        camerasTableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        camerasTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        camerasTableWidget->setTextElideMode(Qt::ElideRight);
        camerasTableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        camerasTableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        camerasTableWidget->setColumnCount(9);
        camerasTableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        camerasTableWidget->horizontalHeader()->setDefaultSectionSize(100);
        camerasTableWidget->horizontalHeader()->setStretchLastSection(true);
        camerasTableWidget->verticalHeader()->setVisible(false);
        camerasDockWidget->setWidget(camerasDockWidgetContents);
        dockWidget_4 = new QDockWidget(centralwidget);
        dockWidget_4->setObjectName(QStringLiteral("dockWidget_4"));
        dockWidget_4->setGeometry(QRect(30, 490, 381, 181));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dockWidget_4->sizePolicy().hasHeightForWidth());
        dockWidget_4->setSizePolicy(sizePolicy);
        dockWidget_4->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QStringLiteral("dockWidgetContents_4"));
        flashCheckBox = new QCheckBox(dockWidgetContents_4);
        flashCheckBox->setObjectName(QStringLiteral("flashCheckBox"));
        flashCheckBox->setEnabled(false);
        flashCheckBox->setGeometry(QRect(10, 60, 57, 21));
        flashCheckBox->setChecked(false);
        preshootCheckBox = new QCheckBox(dockWidgetContents_4);
        preshootCheckBox->setObjectName(QStringLiteral("preshootCheckBox"));
        preshootCheckBox->setEnabled(false);
        preshootCheckBox->setGeometry(QRect(10, 90, 78, 21));
        preshootCheckBox->setChecked(true);
        multicamCheckBox = new QCheckBox(dockWidgetContents_4);
        multicamCheckBox->setObjectName(QStringLiteral("multicamCheckBox"));
        multicamCheckBox->setEnabled(false);
        multicamCheckBox->setGeometry(QRect(10, 10, 85, 21));
        multicamCheckBox->setChecked(true);
        manualFocusCheckBox = new QCheckBox(dockWidgetContents_4);
        manualFocusCheckBox->setObjectName(QStringLiteral("manualFocusCheckBox"));
        manualFocusCheckBox->setEnabled(false);
        manualFocusCheckBox->setGeometry(QRect(10, 120, 111, 21));
        focusSpinBox = new QSpinBox(dockWidgetContents_4);
        focusSpinBox->setObjectName(QStringLiteral("focusSpinBox"));
        focusSpinBox->setEnabled(false);
        focusSpinBox->setGeometry(QRect(120, 120, 91, 24));
        focusSpinBox->setMinimum(-1);
        focusSpinBox->setMaximum(5000);
        focusSpinBox->setValue(1000);
        dockWidget_4->setWidget(dockWidgetContents_4);
        shootingDockWidget = new QDockWidget(centralwidget);
        shootingDockWidget->setObjectName(QStringLiteral("shootingDockWidget"));
        shootingDockWidget->setGeometry(QRect(430, 490, 411, 261));
        sizePolicy.setHeightForWidth(shootingDockWidget->sizePolicy().hasHeightForWidth());
        shootingDockWidget->setSizePolicy(sizePolicy);
        shootingDockWidget->setMinimumSize(QSize(200, 95));
        shootingDockWidget->setFloating(false);
        shootingDockWidgetContents = new QWidget();
        shootingDockWidgetContents->setObjectName(QStringLiteral("shootingDockWidgetContents"));
        tvSlider = new ParameterSlider(shootingDockWidgetContents);
        tvSlider->setObjectName(QStringLiteral("tvSlider"));
        tvSlider->setGeometry(QRect(9, 9, 381, 41));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tvSlider->sizePolicy().hasHeightForWidth());
        tvSlider->setSizePolicy(sizePolicy1);
        avSlider = new ParameterSlider(shootingDockWidgetContents);
        avSlider->setObjectName(QStringLiteral("avSlider"));
        avSlider->setEnabled(false);
        avSlider->setGeometry(QRect(10, 70, 382, 41));
        sizePolicy1.setHeightForWidth(avSlider->sizePolicy().hasHeightForWidth());
        avSlider->setSizePolicy(sizePolicy1);
        isoSlider = new ParameterSlider(shootingDockWidgetContents);
        isoSlider->setObjectName(QStringLiteral("isoSlider"));
        isoSlider->setGeometry(QRect(10, 130, 382, 41));
        delaySlider = new ParameterSlider(shootingDockWidgetContents);
        delaySlider->setObjectName(QStringLiteral("delaySlider"));
        delaySlider->setEnabled(false);
        delaySlider->setGeometry(QRect(10, 190, 382, 41));
        shootingDockWidget->setWidget(shootingDockWidgetContents);
        dockWidget_3 = new QDockWidget(centralwidget);
        dockWidget_3->setObjectName(QStringLiteral("dockWidget_3"));
        dockWidget_3->setGeometry(QRect(20, 240, 1081, 241));
        dockWidget_3->setFloating(false);
        dockWidget_3->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidget_3->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents_3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tabWidget = new QTabWidget(dockWidgetContents_3);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tabWidget);

        dockWidget_3->setWidget(dockWidgetContents_3);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1101, 20));
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionReloadCameras);
        toolBar->addAction(actionGetAdditionalCamerasInfo);
        toolBar->addAction(actionApplyShootingSettings);
        toolBar->addAction(actionShoot);
        toolBar->addAction(actionSelectedCameraShoot);
        toolBar->addAction(actionDownloadLastPhotos);
        toolBar->addAction(actionConfigureStaticProps);
        toolBar->addAction(actionShutdownAll);
        toolBar->addAction(actionDiagnose);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionReloadCameras->setText(QApplication::translate("MainWindow", "Reload Camera List", 0));
#ifndef QT_NO_TOOLTIP
        actionReloadCameras->setToolTip(QApplication::translate("MainWindow", "Update the list of cameras", 0));
#endif // QT_NO_TOOLTIP
        actionShoot->setText(QApplication::translate("MainWindow", "Shoot", 0));
#ifndef QT_NO_TOOLTIP
        actionShoot->setToolTip(QApplication::translate("MainWindow", "Take one photo using each of the available cameras", 0));
#endif // QT_NO_TOOLTIP
        actionDiagnose->setText(QApplication::translate("MainWindow", "Diagnose", 0));
        actionConfigureStaticProps->setText(QApplication::translate("MainWindow", "Set up camera static parameters", 0));
#ifndef QT_NO_TOOLTIP
        actionConfigureStaticProps->setToolTip(QApplication::translate("MainWindow", "Set up camera static parameters", 0));
#endif // QT_NO_TOOLTIP
        actionShutdownAll->setText(QApplication::translate("MainWindow", "Shutdown", 0));
#ifndef QT_NO_TOOLTIP
        actionShutdownAll->setToolTip(QApplication::translate("MainWindow", "Shutdown all cameras", 0));
#endif // QT_NO_TOOLTIP
        actionSelectedCameraShoot->setText(QApplication::translate("MainWindow", "SelectedCameraShoot", 0));
        actionDownloadLastPhotos->setText(QApplication::translate("MainWindow", "DownloadLastPhotos", 0));
        actionApplyShootingSettings->setText(QApplication::translate("MainWindow", "applyShootingSettings", 0));
        actionGetAdditionalCamerasInfo->setText(QApplication::translate("MainWindow", "getAdditionalCamerasInfo", 0));
        camerasDockWidget->setWindowTitle(QApplication::translate("MainWindow", "Cameras", 0));
        dockWidget_4->setWindowTitle(QApplication::translate("MainWindow", "Settings", 0));
        flashCheckBox->setText(QApplication::translate("MainWindow", "Flash", 0));
        preshootCheckBox->setText(QApplication::translate("MainWindow", "Preshoot", 0));
        multicamCheckBox->setText(QApplication::translate("MainWindow", "Multicam", 0));
        manualFocusCheckBox->setText(QApplication::translate("MainWindow", "Manual Focus", 0));
        shootingDockWidget->setWindowTitle(QApplication::translate("MainWindow", "Shooting", 0));
        dockWidget_3->setWindowTitle(QApplication::translate("MainWindow", "Properties", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
