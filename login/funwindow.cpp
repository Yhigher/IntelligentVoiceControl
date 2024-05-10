#include "funwindow.h"
#include "ui_funwindow.h"
#include "QMessageBox"

FunWindow::FunWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FunWindow)
{
    ui->setupUi(this);
    myAudio = new Audio;
    mySpeaker = new QTextToSpeech;
    tcpclient = new QTcpSocket;
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(1280,720);
    connect(tcpclient,&QTcpSocket::readyRead,this,&FunWindow::tcpclientreaddata);
    //未连接状态  去连接
    if(tcpclient->state() != QAbstractSocket::ConnectedState) {
        //连接服务器
        tcpclient->connectToHost(IP_ADDR, PORT);
        //等待连接成功
        if(!tcpclient->waitForConnected(30000)) {
           qDebug() << "Connection failed!";
           return;
        }
        QMessageBox::information(this, "success", "connection sucessfully!");
    }
    FunWindow::hash.insert("打开灯。", 0);
    FunWindow::hash.insert("关闭灯。", 1);
    FunWindow::hash.insert("打开蜂鸣器。", 2);
    FunWindow::hash.insert("关闭蜂鸣器。", 3);
    FunWindow::hash.insert("打开风扇。", 4);
    FunWindow::hash.insert("关闭风扇。", 5);
}

FunWindow::~FunWindow()
{
    if (nullptr != myAudio)
    {
        delete myAudio;
        myAudio = nullptr;
    }
    if (nullptr != mySpeaker)
    {
        delete mySpeaker;
        mySpeaker = nullptr;
    }
    delete ui;
}

void FunWindow::tcpclientreaddata()
{
    QString data = tcpclient->readAll();
    QStringList parse_data = data.split('-');
    ui->lineEdit_t->setText(parse_data[0] + " ℃");
    ui->lineEdit_h->setText(parse_data[1] + " %");
    ui->lineEdit_l->setText(parse_data[2] + " Lux");
}

void FunWindow::on_pushButton_pressed()
{
    ui->pushButton->setText("松开识别");
    // 开始录音
    myAudio->startAudio("audiofile");
}

void FunWindow::on_pushButton_released()
{
    ui->pushButton->setText("按下识别");
    // 结束录音 进行对应的语言识别
    QString str = myAudio->startSpeech();
    myAudio->stopAudio();
    qDebug() << str;
    ui->textEdit->setText(str);
    // 模糊匹配
    if(str.contains("开") && str.contains("灯"))
    {
        str = "打开灯。";
    }
    else if(str.contains("关") && str.contains("灯"))
    {
        str = "关闭灯。";
    }
    else if(str.contains("开") && str.contains("器"))
    {
        str = "打开蜂鸣器。";
    }
    else if(str.contains("关") && str.contains("器"))
    {
        str = "关闭蜂鸣器。";
    }
    else if(str.contains("开") && str.contains("风"))
    {
        str = "打开风扇。";
    }
    else if(str.contains("关") && str.contains("风"))
    {
        str = "关闭风扇。";
    }
    int choice = -1;
    if (FunWindow::hash.contains(str)) {
        // 键存在，可以安全地访问值
        qDebug() << str;
        choice = FunWindow::hash.value(str);
        // 将文本转语音
        mySpeaker->say(str);
    } else {
        choice = FunWindow::hash.value("error");
        // 将文本转语音
        mySpeaker->say("抱歉，没听清楚，请再说一遍。");
    }
    qDebug() << choice;
    switch(choice)
    {
        case ledOn:
            tcpclient->write("ledOn");
            break;
        case ledOff:
            tcpclient->write("ledOff");
            break;
        case beeOn:
            tcpclient->write("beeOn");
            break;
        case beeOff:
            tcpclient->write("beeOff");
            break;
        case fanOn:
            tcpclient->write("fanOn");
            break;
        case fanOff:
            tcpclient->write("fanOff");
            break;
        default:
            qDebug() << "未能识别到指令";
            break;
    }

}

void FunWindow::on_pushButton_2_clicked()
{
    tcpclient->write("led_on");
}
