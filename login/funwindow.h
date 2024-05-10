#ifndef FUNWINDOW_H
#define FUNWINDOW_H

#include <QMainWindow>
#include "Audio.h"
#include <QtTextToSpeech>
#include <QObject>

#define IP_ADDR "192.168.103.229"
//#define IP_ADDR "192.168.103.203"
#define PORT 8888

namespace Ui {
class FunWindow;
}

class FunWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FunWindow(QWidget *parent = nullptr);
    ~FunWindow();
    enum cmd
    {
        ledOn = 0,
        ledOff,
        beeOn,
        beeOff,
        fanOn,
        fanOff,
        error
    };
    Q_ENUM(cmd)
    QHash<QString, int> hash;

public slots:
    void tcpclientreaddata();

private slots:


    void on_pushButton_pressed();

    void on_pushButton_released();

    void on_pushButton_2_clicked();

private:
    Ui::FunWindow *ui;
    Audio *myAudio;
    QTextToSpeech *mySpeaker;
    QTcpSocket *tcpclient;
};

#endif // FUNWINDOW_H
