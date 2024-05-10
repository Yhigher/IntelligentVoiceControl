#include "database.h"
#include "qdebug.h"


DataBase::DataBase(QObject *parent)
    : QObject{parent}
{
    myDatabase = new QSqlDatabase;
    if (QSqlDatabase::contains("default_connection"))
    {
        QSqlDatabase::database("default_connection");
    }
    else
    {
        *myDatabase = QSqlDatabase::addDatabase("QSQLITE", "default_connection");
        myDatabase->setDatabaseName("USER.db");
    }
    if (myDatabase->open())
    {
        qDebug() << "successed";
    }
    else
    {
        qDebug() << "failed";
    }
    this->createTable();
    // this->RegisterUser("zhangbo", "lyhzb999");
    // this->ChangeUserData("zhangbo", "luoyahan");
    // this->RegisterUser("test", "test");
    // this->DeleteUserData("test");
    // this->SelectUserData();
    // this->JudgeUserExist("test", "123");
}

DataBase::~DataBase()
{
    if (nullptr != myDatabase)
    {
        delete myDatabase;
        myDatabase = nullptr;
    }
}

bool DataBase::createTable()
{
    QSqlQuery qsq(*myDatabase);
    myDatabase->transaction();
    qsq.prepare("create table if not exists USER(account text primary key, passwd text)");
    if(qsq.exec())
    {
        qDebug() << "创建成功！";
        myDatabase->commit();
        return true;
    }
    else
    {
        qDebug() << "创建失败！";
        myDatabase->rollback();
        return false;
    }
}

bool DataBase::RegisterUser(QString Account, QString passwd)
{
    QSqlQuery qsq(*myDatabase);
    myDatabase->transaction();
    qsq.prepare("insert into USER(account, passwd) values(:account, :passwd)");
    qsq.bindValue(":account", Account);
    qsq.bindValue(":passwd", passwd);
    if(qsq.exec())
    {
        qDebug() << "插入成功！";
        myDatabase->commit();
        return true;
    }
    else
    {
        qDebug() << "插入失败！";
        myDatabase->rollback();
        return false;
    }
}

bool DataBase::ChangeUserData(QString Account, QString NewPasswd)
{
    QSqlQuery qsq(*myDatabase);
    myDatabase->transaction();
    qsq.prepare("update USER set passwd = :passwd where account = :account");
    qsq.bindValue(":account", Account);
    qsq.bindValue(":passwd", NewPasswd);
    if(qsq.exec())
    {
        qDebug() << "更新成功！";
        myDatabase->commit();
        return true;
    }
    else
    {
        qDebug() << "更新失败！";
        myDatabase->rollback();
        return false;
    }
}

bool DataBase::DeleteUserData(QString Account)
{
    QSqlQuery qsq(*myDatabase);
    myDatabase->transaction();
    qsq.prepare("delete from USER where account = :account");
    qsq.bindValue(":account", Account);
    if(qsq.exec())
    {
        qDebug() << "删除成功！";
        myDatabase->commit();
        return true;
    }
    else
    {
        qDebug() << "删除失败！";
        myDatabase->rollback();
        return false;
    }
}

bool DataBase::SelectUserData()
{
    QSqlQuery qsq(*myDatabase);
    qsq.prepare("select* from USER");
    if(qsq.exec())
    {
        qDebug() << "查找成功！";
        while(qsq.next())
        {
            QString account = qsq.value(0).toString();
            QString passwd = qsq.value(1).toString();
            qDebug() << "Account:" << account << "Passwd:" << passwd;
        }
        return true;
    }
    else
    {
        qDebug() << "查找失败！";
        myDatabase->rollback();
        return false;
    }
}

bool DataBase::JudgeUserExist(QString Account, QString Passwd)
{
    QSqlQuery qsq(*myDatabase);
    qsq.prepare("select* from USER where account = :account and passwd = :passwd");
    qsq.bindValue(":account", Account);
    qsq.bindValue(":passwd", Passwd);
    qDebug() << Account << " " << Passwd;
    if(qsq.exec())
    {
        if (qsq.first() != NULL)
        {
            qDebug() << "用户存在！";
            return true;
        }
    }
    qDebug() << "用户不存在！";
    myDatabase->rollback();
    return false;
}


