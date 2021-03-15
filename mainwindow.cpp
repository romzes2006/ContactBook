#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = new Database(this);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete db;
    delete modelContacts;
    delete modelPhones;
}



void MainWindow::on_btn_ConnectDB_clicked()
{
    db->connectToDataBase();
    setupModels("contacts","phones","phone_type");
    ui->tableView->setModel(modelContacts);
    ui->tableView_2->setModel(modelPhones);
    ui->tableView_2->hideColumn(0);
    ui->tableView_2->hideColumn(1);
    ui->tableView_2->setItemDelegate(new QSqlRelationalDelegate(ui->tableView_2));
    ui->tableView->hideColumn(0);
    ui->tableView->horizontalHeader()->setSectionsMovable(true);

    modelContacts->select();
    modelPhones->select();
    //modelPhones->setFilter(modelContacts->fieldIndex("id"))
   // modelPhoneType->select();
}

void MainWindow::setupModels(const QString &MainTableName, const QString &SecondaryTableName, const QString &PhoneTypeTableName)
{
    modelContacts = new QSqlTableModel(this);
    modelContacts->setTable(MainTableName);
    modelContacts->setHeaderData(0,Qt::Horizontal,tr("id"));
    modelContacts->setHeaderData(1,Qt::Horizontal,tr("Фамилия"));
    modelContacts->setHeaderData(3,Qt::Horizontal,tr("Имя"));
    modelContacts->setHeaderData(2,Qt::Horizontal,tr("Отчество"));
    //modelContacts->setRelation(0,QSqlRelation(MainTableName,"contact_id",SecondaryTableName));
    modelPhones = new QSqlRelationalTableModel(this);
   // modelPhoneType = new QSqlRelationalTableModel(this);
    modelPhones->setTable(SecondaryTableName);
    modelPhones->setHeaderData(0,Qt::Horizontal,tr("id"));
    modelPhones->setHeaderData(1,Qt::Horizontal,tr("contact_id"));
    modelPhones->setHeaderData(2,Qt::Horizontal,tr("Тип телефона"));
    modelPhones->setHeaderData(3,Qt::Horizontal,tr("Номер телефона"));
    modelPhones->setRelation(modelPhones->fieldIndex("phone_type_id"),
                             QSqlRelation(PhoneTypeTableName,"id","type"));

    }

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
   // modelPhones->setTable();
}
