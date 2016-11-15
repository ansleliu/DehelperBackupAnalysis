#include "MySQLite.h"
#include <QDebug>

MySQLite::MySQLite(const QString &dbpath,
                   const QString &connName,
                   const QString &DBName)
    : m_connName(connName)
{
    db = new QSqlDatabase(QSqlDatabase::addDatabase(DBName, connName));
    db->setDatabaseName(dbpath);
    if (!db->open())
    {
        qDebug() << QString("数据库错误")
                 << QString("无法打开数据库: %1")
                    .arg(db->lastError().text());
    }
    qDebug() << QString("数据库 %1 创建成功").arg(connName);
}

MySQLite::~MySQLite()
{
    qDebug() << "当前的连接是：" << db->connectionName()
             <<" ,它将要被移除！";

    db->close();
    delete db;
    db = NULL;
    QSqlDatabase::removeDatabase(m_connName);

    QStringList connect = QSqlDatabase::connectionNames();
    for(int i=0;i<connect.size();i++)
    {
        qDebug() << "移除后还包括这些连接" << connect.at(i);
    }
    qDebug() << "已经移出了一个连接";
}

QVariant MySQLite::rexec(const QString &sql)
{
    QSqlQuery query = db->exec(sql);
    if (query.next())
    {
        return query.record().value(0);
    }
    else
    {
        if (query.lastError().number() != -1)	// 没有对应的数据
        {
            qDebug() << QString("数据库错误")
                     << QString("没有对应的数据: %1 %2")
                        .arg(query.lastError().number())
                        .arg(query.lastError().type());
        }

    }
    return "";
}

uint MySQLite::lastInsertID()
{
    return rexec("SELECT last_insert_rowid();").toUInt();
}

bool MySQLite::exec(const QString &sql)
{
    db->exec(sql);

    QSqlError::ErrorType type = db->lastError().type();

    if (type != QSqlError::NoError)
    {
        QString message = db->lastError().text();
        qDebug() << QString("数据库错误")
                 << QString("数据库错误: %1")
                    .arg(message);
        return false;
    }
    return true;
}

bool MySQLite::isTableExist(const QString &tableName)
{
    return db->tables(QSql::Tables).contains(tableName);
}

