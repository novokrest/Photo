/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "parameterslider.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionReloadCameras;
    QAction *actionShoot;
    QAction *actionDiagnose;
    QAction *actionConfigureStaticProps;
    QAction *actionShutdownAll;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableView *tableView_2;
    QMenuBar *menubar;
    QDockWidget *shootingDockWidget;
    QWidget *shootingDockWidgetContents;
    QVBoxLayout *verticalLayout_4;
    ParameterSlider *tvSlider;
    ParameterSlider *avSlider;
    ParameterSlider *isoSlider;
    QDockWidget *camerasDockWidget;
    QWidget *camerasDockWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *camerasTableWidget;
    QDockWidget *dockWidget_3;
    QWidget *dockWidgetContents_3;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *textBrowser;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(760, 541);
        MainWindow->setTabShape(QTabWidget::Rounded);
        MainWindow->setDockNestingEnabled(false);
        MainWindow->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        actionReloadCameras = new QAction(MainWindow);
        actionReloadCameras->setObjectName(QStringLiteral("actionReloadCameras"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/view-refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReloadCameras->setIcon(icon);
        actionShoot = new QAction(MainWindow);
        actionShoot->setObjectName(QStringLiteral("actionShoot"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/camera-photo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShoot->setIcon(icon1);
        actionDiagnose = new QAction(MainWindow);
        actionDiagnose->setObjectName(QStringLiteral("actionDiagnose"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/document-export.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDiagnose->setIcon(icon2);
        actionConfigureStaticProps = new QAction(MainWindow);
        actionConfigureStaticProps->setObjectName(QStringLiteral("actionConfigureStaticProps"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/applications-development.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConfigureStaticProps->setIcon(icon3);
        actionShutdownAll = new QAction(MainWindow);
        actionShutdownAll->setObjectName(QStringLiteral("actionShutdownAll"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/system-shutdown.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShutdownAll->setIcon(icon4);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        horizontalLayout->addWidget(tableView);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        tableView_2 = new QTableView(widget);
        tableView_2->setObjectName(QStringLiteral("tableView_2"));

        verticalLayout->addWidget(tableView_2);


        horizontalLayout->addWidget(widget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 760, 20));
        MainWindow->setMenuBar(menubar);
        shootingDockWidget = new QDockWidget(MainWindow);
        shootingDockWidget->setObjectName(QStringLiteral("shootingDockWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(shootingDockWidget->sizePolicy().hasHeightForWidth());
        shootingDockWidget->setSizePolicy(sizePolicy);
        shootingDockWidget->setMinimumSize(QSize(200, 79));
        shootingDockWidgetContents = new QWidget();
        shootingDockWidgetContents->setObjectName(QStringLiteral("shootingDockWidgetContents"));
        verticalLayout_4 = new QVBoxLayout(shootingDockWidgetContents);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        tvSlider = new ParameterSlider(shootingDockWidgetContents);
        tvSlider->setObjectName(QStringLiteral("tvSlider"));

        verticalLayout_4->addWidget(tvSlider);

        avSlider = new ParameterSlider(shootingDockWidgetContents);
        avSlider->setObjectName(QStringLiteral("avSlider"));
        avSlider->setEnabled(false);

        verticalLayout_4->addWidget(avSlider);

        isoSlider = new ParameterSlider(shootingDockWidgetContents);
        isoSlider->setObjectName(QStringLiteral("isoSlider"));

        verticalLayout_4->addWidget(isoSlider);

        shootingDockWidget->setWidget(shootingDockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), shootingDockWidget);
        camerasDockWidget = new QDockWidget(MainWindow);
        camerasDockWidget->setObjectName(QStringLiteral("camerasDockWidget"));
        camerasDockWidget->setMinimumSize(QSize(378, 183));
        camerasDockWidgetContents = new QWidget();
        camerasDockWidgetContents->setObjectName(QStringLiteral("camerasDockWidgetContents"));
        verticalLayout_3 = new QVBoxLayout(camerasDockWidgetContents);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        camerasTableWidget = new QTableWidget(camerasDockWidgetContents);
        if (camerasTableWidget->columnCount() < 3)
            camerasTableWidget->setColumnCount(3);
        camerasTableWidget->setObjectName(QStringLiteral("camerasTableWidget"));
        camerasTableWidget->setMinimumSize(QSize(360, 0));
        camerasTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        camerasTableWidget->setColumnCount(3);
        camerasTableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        camerasTableWidget->horizontalHeader()->setDefaultSectionSize(50);
        camerasTableWidget->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_3->addWidget(camerasTableWidget);

        camerasDockWidget->setWidget(camerasDockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), camerasDockWidget);
        dockWidget_3 = new QDockWidget(MainWindow);
        dockWidget_3->setObjectName(QStringLiteral("dockWidget_3"));
        dockWidget_3->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents_3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        textBrowser = new QTextBrowser(dockWidgetContents_3);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout_2->addWidget(textBrowser);

        dockWidget_3->setWidget(dockWidgetContents_3);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockWidget_3);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionReloadCameras);
        toolBar->addAction(actionShoot);
        toolBar->addAction(actionConfigureStaticProps);
        toolBar->addAction(actionShutdownAll);
        toolBar->addAction(actionDiagnose);

        retranslateUi(MainWindow);

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
        label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        shootingDockWidget->setWindowTitle(QApplication::translate("MainWindow", "Shooting", 0));
        camerasDockWidget->setWindowTitle(QApplication::translate("MainWindow", "Cameras", 0));
        dockWidget_3->setWindowTitle(QApplication::translate("MainWindow", "Console", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
