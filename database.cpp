#include "database.h"


Database::Database(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("mysql60.hostland.ru");
    db.setDatabaseName("host1323541_irkutsk5");
    db.setUserName("host1323541_itstep");
    db.setPassword("269f43dc");
}

Database::~Database()
{

}

bool Database::connectToDataBase()
{

//            openDataBase();
            bool ok = this->db.open();

                if (ok) {

                  qDebug() << "УРА! Мы подключились.";
                   // modelMain = new QSqlRelationalTableModel(this, db);
                   // modelMain.setEditStrategy(QSqlTableModel::OnManualSubmit);
                    //modelMain->setTable("contacts");

                } else {
                 qDebug() << db.lastError().text() << " Увы...";
               }
return ok;

}

bool Database::insertContactIntoTable(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO contacts (last_name, middle_name, first_name) VALUES (:last_name, :middle_name, :first_name)");
       query.bindValue(":last_name", data[1].toString());
       query.bindValue(":middle_name", data[2].toString());
       query.bindValue(":first_name", data[2].toString());
       if(!query.exec()){
           qDebug() << "error insert into " << TABLE;
           qDebug() << query.lastError().text();
           return false;
       } else {
           return true;
       }
       return false;

}

bool Database::openDataBase()
{
//    bool ok = db.open();

//        if (ok) {

//          qDebug() << "УРА! Мы подключились.";
//           // modelMain = new QSqlRelationalTableModel(this, db);
//           // modelMain.setEditStrategy(QSqlTableModel::OnManualSubmit);
//            //modelMain->setTable("contacts");

//        } else {
//         qDebug() << db.lastError().text() << " Увы...";
//       }

}

void Database::closeDataBase()
{
    db.close();
}

