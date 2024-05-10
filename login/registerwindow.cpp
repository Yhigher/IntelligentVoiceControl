#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "QString"
#include "QMessageBox"

#define PASSWORD_LENGTH_MIN 6

RegisterWindow::RegisterWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setFixedSize(1280,720);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::doShowRegisterFail()
{
    QMessageBox::critical(this, "critical", "注册失败！");
    this->show();
    return;
}

void RegisterWindow::on_pushButton_clicked()
{
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QString repeat = ui->lineEdit_3->text();
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
    else if(password.size() < PASSWORD_LENGTH_MIN)
    {
        QMessageBox::critical(this, "warning", "your password is too short!");
        return;
    }
    if (repeat == "")
    {
        QMessageBox::critical(this, "warning", "please input your password again!");
        return;
    }
    else if (password != repeat)
    {
        QMessageBox::critical(this, "warning", "your password not consistent your repeated password");
        return;
    }
    emit RegisterUser(username, password);
}


void RegisterWindow::on_pushButton_2_clicked()
{
    this->close();
    emit ShowMainWindow();
}

