/********************************************************************************
** Form generated from reading UI file 'funwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FUNWINDOW_H
#define UI_FUNWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FunWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_13;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_11;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_12;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_4;
    QLineEdit *lineEdit_2;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_7;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FunWindow)
    {
        if (FunWindow->objectName().isEmpty())
            FunWindow->setObjectName("FunWindow");
        FunWindow->setEnabled(true);
        FunWindow->resize(1003, 673);
        FunWindow->setStyleSheet(QString::fromUtf8("#centralwidget{\n"
"	border-image: url(:/image/spiderman.png);\n"
"}"));
        centralwidget = new QWidget(FunWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_13 = new QHBoxLayout(centralwidget);
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 26pt \"\351\230\277\351\207\214\345\267\264\345\267\264\346\231\256\346\203\240\344\275\223 L\";"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");

        verticalLayout->addWidget(textEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_6->addLayout(verticalLayout);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 26pt \"\351\230\277\351\207\214\345\267\264\345\267\264\346\231\256\346\203\240\344\275\223 L\";"));

        horizontalLayout_7->addWidget(label_6);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_11);


        verticalLayout_5->addLayout(horizontalLayout_7);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_12);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        horizontalLayout_11 = new QHBoxLayout(widget);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout_8->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName("pushButton_3");

        horizontalLayout_8->addWidget(pushButton_3);


        verticalLayout_3->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName("pushButton_4");

        horizontalLayout_9->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(widget);
        pushButton_5->setObjectName("pushButton_5");

        horizontalLayout_9->addWidget(pushButton_5);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        pushButton_6 = new QPushButton(widget);
        pushButton_6->setObjectName("pushButton_6");

        horizontalLayout_10->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(widget);
        pushButton_7->setObjectName("pushButton_7");

        horizontalLayout_10->addWidget(pushButton_7);


        verticalLayout_3->addLayout(horizontalLayout_10);


        horizontalLayout_11->addLayout(verticalLayout_3);


        horizontalLayout_12->addWidget(widget);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_13);


        verticalLayout_4->addLayout(horizontalLayout_12);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);


        verticalLayout_5->addLayout(verticalLayout_4);


        verticalLayout_6->addLayout(verticalLayout_5);


        horizontalLayout_13->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 26pt \"\351\230\277\351\207\214\345\267\264\345\267\264\346\231\256\346\203\240\344\275\223 L\";"));

        horizontalLayout_3->addWidget(label_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(label_3);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_4->addWidget(lineEdit);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
""));

        horizontalLayout_5->addWidget(label_4);

        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");

        horizontalLayout_5->addWidget(lineEdit_2);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_8);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
""));

        horizontalLayout_6->addWidget(label_5);

        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName("lineEdit_3");

        horizontalLayout_6->addWidget(lineEdit_3);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_10);


        verticalLayout_2->addLayout(horizontalLayout_6);


        verticalLayout_7->addLayout(verticalLayout_2);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 26pt \"\351\230\277\351\207\214\345\267\264\345\267\264\346\231\256\346\203\240\344\275\223 L\";"));

        verticalLayout_7->addWidget(label_7);


        horizontalLayout_13->addLayout(verticalLayout_7);

        FunWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FunWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1003, 25));
        FunWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(FunWindow);
        statusbar->setObjectName("statusbar");
        FunWindow->setStatusBar(statusbar);

        retranslateUi(FunWindow);

        QMetaObject::connectSlotsByName(FunWindow);
    } // setupUi

    void retranslateUi(QMainWindow *FunWindow)
    {
        FunWindow->setWindowTitle(QCoreApplication::translate("FunWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("FunWindow", "\350\257\255\351\237\263\350\257\206\345\210\253", nullptr));
        pushButton->setText(QCoreApplication::translate("FunWindow", "PushButton", nullptr));
        label_6->setText(QCoreApplication::translate("FunWindow", "\346\214\211\351\222\256\346\216\247\345\210\266", nullptr));
        pushButton_2->setText(QCoreApplication::translate("FunWindow", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("FunWindow", "PushButton", nullptr));
        pushButton_4->setText(QCoreApplication::translate("FunWindow", "PushButton", nullptr));
        pushButton_5->setText(QCoreApplication::translate("FunWindow", "PushButton", nullptr));
        pushButton_6->setText(QCoreApplication::translate("FunWindow", "PushButton", nullptr));
        pushButton_7->setText(QCoreApplication::translate("FunWindow", "PushButton", nullptr));
        label_2->setText(QCoreApplication::translate("FunWindow", "\347\216\257\345\242\203\346\225\260\346\215\256\346\230\276\347\244\272", nullptr));
        label_3->setText(QCoreApplication::translate("FunWindow", "\346\270\251\345\272\246\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("FunWindow", "\346\271\277\345\272\246\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("FunWindow", "\345\205\211\346\225\217\357\274\232", nullptr));
        label_7->setText(QCoreApplication::translate("FunWindow", "\345\212\237\350\203\275\345\276\205\345\274\200\345\217\221......", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FunWindow: public Ui_FunWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FUNWINDOW_H
