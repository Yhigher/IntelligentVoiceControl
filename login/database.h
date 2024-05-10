#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <qsqlquery.h>

class DataBase : public QObject
{
public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

signals:
public slots:
    bool createTable();
    bool RegisterUser(QString Account, QString passwd);
    bool ChangeUserData(QString Account, QString NewPasswd);
    bool DeleteUserData(QString Account);
    bool SelectUserData();
    bool JudgeUserExist(QString Account, QString NewPasswd);

private:
    QSqlDatabase *myDatabase;
};

#endif // DATABASE_H
