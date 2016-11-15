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
        qDebug() << QString("���ݿ����")
                 << QString("�޷������ݿ�: %1")
                    .arg(db->lastError().text());
    }
    qDebug() << QString("���ݿ� %1 �����ɹ�").arg(connName);
}

MySQLite::~MySQLite()
{
    qDebug() << "��ǰ�������ǣ�" << db->connectionName()
             <<" ,����Ҫ���Ƴ���";

    db->close();
    delete db;
    db = NULL;
    QSqlDatabase::removeDatabase(m_connName);

    QStringList connect = QSqlDatabase::connectionNames();
    for(int i=0;i<connect.size();i++)
    {
        qDebug() << "�Ƴ��󻹰�����Щ����" << connect.at(i);
    }
    qDebug() << "�Ѿ��Ƴ���һ������";
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
        if (query.lastError().number() != -1)	// û�ж�Ӧ������
        {
            qDebug() << QString("���ݿ����")
                     << QString("û�ж�Ӧ������: %1 %2")
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
        qDebug() << QString("���ݿ����")
                 << QString("���ݿ����: %1")
                    .arg(message);
        return false;
    }
    return true;
}

bool MySQLite::isTableExist(const QString &tableName)
{
    return db->tables(QSql::Tables).contains(tableName);
}

