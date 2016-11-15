#ifndef MYSQLITE_H
#define MYSQLITE_H
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>
#include <QString>

class MySQLite
{
public:
    MySQLite(const QString &dbpath,
             const QString &connName,
             const QString &DBName);
    virtual ~MySQLite();

public:
    QVariant rexec(const QString &sql);	// ִ��sql���,���ص�һ�е�һ�е�ֵ
    uint  lastInsertID();	// ȡ���������ݵ�ID
    bool exec(const QString &sql); // ִ�в���Ҫ���ؽ��sql���

    bool isTableExist(const QString &tableName);	// ���������Ƿ����
    QSqlDatabase *getdb()
    {
        return db;
    }
protected:
    QSqlDatabase *db;
    QString m_connName;
};

#endif // MYSQLITE_H
