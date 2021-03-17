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
    //modelPhones->setFilter("");
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
    modelContacts->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //modelContacts->setRelation(0,QSqlRelation(MainTableName,"contact_id",SecondaryTableName));
    modelPhones = new QSqlRelationalTableModel(this);
   // modelPhoneType = new QSqlRelationalTableModel(this);
    modelPhones->setTable(SecondaryTableName);
    modelPhones->setHeaderData(0,Qt::Horizontal,tr("id"));
    modelPhones->setHeaderData(1,Qt::Horizontal,tr("contact_id"));
    modelPhones->setHeaderData(2,Qt::Horizontal,tr("Тип телефона"));
    modelPhones->setHeaderData(3,Qt::Horizontal,tr("Номер телефона"));
    modelPhones->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    modelPhones->setRelation(modelPhones->fieldIndex("phone_type_id"),
                             QSqlRelation(PhoneTypeTableName,"id","type"));

}

QString MainWindow::GetSelectetRowId(QSqlTableModel *dataModel, QTableView *tableView)
{
    QModelIndex currentField = tableView->currentIndex();
    QSqlRecord record = dataModel->record(tableView->model()->index(currentField.row(),1).row());
    QString record_val = record.value("id").toString();
    return record_val;
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
//     QModelIndex currentContact = ui->tableView->currentIndex();
//     qDebug() << ui->tableView->model()->data(ui->tableView->model()->index(currentContact.row(),1),0) << "/n";
//     QModelIndex tempTest = ui->tableView->model()->index(currentContact.row(),1);
//     auto temp2 = tempTest.row();
//     qDebug() << tempTest << "/n" << temp2;
//     QSqlRecord record = modelContacts->record(ui->tableView->model()->index(currentContact.row(),1).row());
//     qDebug() << "id = " << record.value("id").toInt();
//     QString record_val = record.value("id").toString();
//     modelPhones->setFilter("contact_id = "+record_val);
//     modelPhones->setTable();

    modelPhones->setFilter("contact_id = "+  GetSelectetRowId(modelContacts,ui->tableView));
}

void MainWindow::on_pushButton_3_clicked()
{
    qDebug() << "Вставка записи: " << modelContacts->insertRow(modelContacts->rowCount());
    //modelContacts->insertRows();
}

void MainWindow::on_pushButton_2_clicked()
{
    modelContacts->submitAll();
    modelPhones->submitAll();
}

void MainWindow::on_pushButton_4_clicked()
{
    modelContacts->select();
    modelPhones->select();
}

void MainWindow::on_pushButton_clicked()
{
    QString id_parent_row = GetSelectetRowId(modelContacts,ui->tableView);
    //qDebug() << "Вставка записи тедефона: " << modelPhones->insertRow(modelPhones->rowCount());
    //QModelIndex currentField = ui->tableView_2->currentIndex();
    QSqlRecord record = modelPhones->record();
    record.setValue("contact_id", id_parent_row);
    record.setValue("phone_type_id", "1");
    modelPhones->insertRecord(-1,record);

    //record.setValue("contact_id",GetSelectetRowId(modelContacts,ui->tableView).toInt());

}
