#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include "qstring.h"
#include "QMessageBox"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setFixedSize(1280,720);
    myDataBase = new DataBase;
    myFunWindow = new FunWindow;
    myRegisterWindow = new RegisterWindow;

    // connect(myRegisterWindow, SIGNAL(ShowMainWindow()), this, SLOT(doShowMainWindow()));
    connect(myRegisterWindow, RegisterWindow::ShowMainWindow, this, MainWindow::doShowMainWindow);
    connect(myRegisterWindow, RegisterWindow::RegisterUser, this, MainWindow::doRegisterUser);

}

MainWindow::~MainWindow()
{
    if (nullptr != myFunWindow)
    {
        delete myFunWindow;
        myFunWindow = nullptr;
    }
    if (nullptr != myRegisterWindow)
    {
        delete myRegisterWindow;
        myRegisterWindow = nullptr;
    }
    if (nullptr != myDataBase)
    {
        delete myDataBase;
        myDataBase = nullptr;
    }
    delete ui;
}

void MainWindow::doShowMainWindow()
{
    this->show();
}

void MainWindow::doRegisterUser(QString username, QString passwd)
{
    if(myDataBase->RegisterUser(username, passwd))
    {
        QMessageBox::information(this, "info", "注册成功，请登录！");
        myRegisterWindow->close();
        this->show();
    }
    else
    {
        myRegisterWindow->doShowRegisterFail();
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    if (username == "")
    {
        QMessageBox::critical(this, "warning", "please input your username!");
        return;
    }
    if (password == "")
    {
        QMessageBox::critical(this, "warning", "please input your password!");
        return;
    }
    if(myDataBase->JudgeUserExist(username, password))
    {
        QMessageBox::information(this, "success", "login successfully!");
        this->close();
        myFunWindow->show();
    }
    else
    {
        QMessageBox::critical(this, "warning", "user is not existed");
        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    this->close();
    myRegisterWindow->show();
}

