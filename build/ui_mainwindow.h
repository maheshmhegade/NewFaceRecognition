#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Feb 6 08:46:03 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSlider *horizontalSlider;
    QLabel *label;
    QLCDNumber *lcdNumber;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *openImageBtn;
    QPushButton *detectFacesBtn;
    QPushButton *recogniseBtn;
    QPushButton *updateDatabaseBtn;
    QPushButton *saveConfigBtn;
    QLineEdit *configLocation;
    QPushButton *openConfigBtn;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(798, 598);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(5);
        horizontalSlider->setSingleStep(1);
        horizontalSlider->setPageStep(1);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBelow);
        horizontalSlider->setTickInterval(24);

        gridLayout->addWidget(horizontalSlider, 0, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));

        gridLayout->addWidget(lcdNumber, 0, 2, 1, 1);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout->addWidget(widget, 1, 0, 1, 4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        openImageBtn = new QPushButton(centralWidget);
        openImageBtn->setObjectName(QString::fromUtf8("openImageBtn"));

        verticalLayout->addWidget(openImageBtn);

        detectFacesBtn = new QPushButton(centralWidget);
        detectFacesBtn->setObjectName(QString::fromUtf8("detectFacesBtn"));

        verticalLayout->addWidget(detectFacesBtn);

        recogniseBtn = new QPushButton(centralWidget);
        recogniseBtn->setObjectName(QString::fromUtf8("recogniseBtn"));

        verticalLayout->addWidget(recogniseBtn);

        updateDatabaseBtn = new QPushButton(centralWidget);
        updateDatabaseBtn->setObjectName(QString::fromUtf8("updateDatabaseBtn"));

        verticalLayout->addWidget(updateDatabaseBtn);

        saveConfigBtn = new QPushButton(centralWidget);
        saveConfigBtn->setObjectName(QString::fromUtf8("saveConfigBtn"));

        verticalLayout->addWidget(saveConfigBtn);


        gridLayout->addLayout(verticalLayout, 1, 4, 1, 1);

        configLocation = new QLineEdit(centralWidget);
        configLocation->setObjectName(QString::fromUtf8("configLocation"));

        gridLayout->addWidget(configLocation, 2, 0, 1, 1);

        openConfigBtn = new QPushButton(centralWidget);
        openConfigBtn->setObjectName(QString::fromUtf8("openConfigBtn"));

        gridLayout->addWidget(openConfigBtn, 2, 3, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(tr2i18n("Libkface GUI Test Program", 0));
        label->setText(tr2i18n("Accuracy", 0));
        openImageBtn->setText(tr2i18n("Open Image", 0));
        detectFacesBtn->setText(tr2i18n("Detect Faces", 0));
        recogniseBtn->setText(tr2i18n("Recognise", 0));
        updateDatabaseBtn->setText(tr2i18n("Update Database", 0));
        saveConfigBtn->setText(tr2i18n("Save Config", 0));
        configLocation->setText(tr2i18n("Some Default File Location", 0));
        openConfigBtn->setText(tr2i18n("Config Directory", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_H

