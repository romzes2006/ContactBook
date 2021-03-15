#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlRelation>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlRelationalDelegate>
#include <QtDebug>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_btn_ConnectDB_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Database *db;
    QSqlTableModel    *modelContacts;
    QSqlRelationalTableModel    *modelPhones;
 //   QSqlRelationalTableModel    *modelPhoneType;
   // QSqlTableModel    *modelPhones;
    void setupModels(const QString &MainTableName, const QString &SecondaryTableName, const QString &PhoneTypeTableName);

};
#endif // MAINWINDOW_H
