/********************************************************************************
** Form generated from reading UI file 'parameterslider.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETERSLIDER_H
#define UI_PARAMETERSLIDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParameterSlider
{
public:
    QHBoxLayout *horizontalLayout;
    QSlider *slider;
    QLineEdit *lineEdit;

    void setupUi(QWidget *ParameterSlider)
    {
        if (ParameterSlider->objectName().isEmpty())
            ParameterSlider->setObjectName(QStringLiteral("ParameterSlider"));
        ParameterSlider->resize(244, 41);
        horizontalLayout = new QHBoxLayout(ParameterSlider);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        slider = new QSlider(ParameterSlider);
        slider->setObjectName(QStringLiteral("slider"));
        slider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(slider);

        lineEdit = new QLineEdit(ParameterSlider);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        lineEdit->setMinimumSize(QSize(90, 0));
        lineEdit->setMaximumSize(QSize(90, 16777215));
        lineEdit->setBaseSize(QSize(50, 0));

        horizontalLayout->addWidget(lineEdit);


        retranslateUi(ParameterSlider);

        QMetaObject::connectSlotsByName(ParameterSlider);
    } // setupUi

    void retranslateUi(QWidget *ParameterSlider)
    {
        ParameterSlider->setWindowTitle(QApplication::translate("ParameterSlider", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class ParameterSlider: public Ui_ParameterSlider {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERSLIDER_H
