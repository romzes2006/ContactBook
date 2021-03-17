#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlRelation>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtDebug>


#define TABLE                   "TableExample"
#define TABLE_DATE              "Date"
#define TABLE_TIME              "Time"
#define TABLE_MESSAGE           "Message"
#define TABLE_RANDOM            "Random"

class Database : public QObject
{
    Q_OBJECT;

public:
        explicit Database(QObject *parent);
       ~Database();
        bool connectToDataBase();
        bool insertContactIntoTable(const QVariantList &data);

private:
        QSqlDatabase db;
private:
        bool openDataBase();

        void closeDataBase();
        };
#endif // DATABASE_H
