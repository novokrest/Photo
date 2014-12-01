/********************************************************************************
** Form generated from reading UI file 'testedwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTEDWINDOW_H
#define UI_TESTEDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QDockWidget *dockWidget_12;
    QWidget *dockWidgetContents_12;
    QDockWidget *dockWidget_11;
    QWidget *dockWidgetContents_11;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        dockWidget_12 = new QDockWidget(centralwidget);
        dockWidget_12->setObjectName(QStringLiteral("dockWidget_12"));
        dockWidget_12->setGeometry(QRect(510, 30, 121, 301));
        dockWidgetContents_12 = new QWidget();
        dockWidgetContents_12->setObjectName(QStringLiteral("dockWidgetContents_12"));
        dockWidget_12->setWidget(dockWidgetContents_12);
        dockWidget_11 = new QDockWidget(centralwidget);
        dockWidget_11->setObjectName(QStringLiteral("dockWidget_11"));
        dockWidget_11->setGeometry(QRect(230, 120, 401, 231));
        dockWidget_11->setFloating(true);
        dockWidgetContents_11 = new QWidget();
        dockWidgetContents_11->setObjectName(QStringLiteral("dockWidgetContents_11"));
        dockWidget_11->setWidget(dockWidgetContents_11);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTEDWINDOW_H
