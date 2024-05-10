#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QMainWindow>
#include "database.h"

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();
    void doShowRegisterFail(void);

// 自定义信号槽
signals:
    void ShowMainWindow();
    void RegisterUser(QString Account, QString passWD);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::RegisterWindow *ui;
};

#endif // REGISTERWINDOW_H
