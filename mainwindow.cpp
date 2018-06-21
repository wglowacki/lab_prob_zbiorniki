#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString ServerName = "MAMA";
    QString DBName = "schoolDatabase";
    QString dsn = QString("DRIVER={SQL Server};Server=%1;Database=%2;Trusted_Connection=Yes;").arg(ServerName).arg(DBName);

    db = QSqlDatabase::addDatabase("QODBC3");
    db.setConnectOptions();
    db.setDatabaseName(dsn);

    if(!db.open()) {

    } else {
        std::cout << "Connection with db established";
        QSqlQuery qry;
        if(qry.exec("SELECT * FROM [schoolDatabase].[dbo].[students]" ))
            while(qry.next())
               std::cout << qry.value(0).toString().toStdString() << "\n";
    }


    qTable = new QSqlQueryModel();
    //ui->tableWidget->setModel(qTable);
    ui->tableView->setModel(qTable);
    ui->tableView->show();
    qFirstValue = new QSqlQueryModel;
    qSecondValue = new QSqlQueryModel;
}

MainWindow::~MainWindow()
{
    if(!db.isOpen()) db.close();


    delete qTable;

    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    static QStringListModel list_of_tables;
    list_of_tables.setStringList(db.tables());
    ui->TableView->setModel(&list_of_tables);

}

void MainWindow::on_TableView_clicked(const QModelIndex &index)
{
    QString record = index.data().toString();
    std::string rec = record.toStdString();
    if(db.open())
        std::cout << "Table name: " << rec << "\n";
    QSqlQuery query;
    QString text = "SELECT * FROM [schoolDatabase].[dbo].[" + record + "]";
    query.prepare(text);
    if(query.exec()) {
        int cols = query.record().count();
        while(query.next()) {
            for (int i=0; i<cols; i++)
                std::cout << query.value(i).toString().toStdString() << " ";
        }
    }
    qTable->setQuery(query);
    ui->tableView->show();
    table_name = record.toStdString();
}

void MainWindow::on_dodaj_butt_clicked()
{
    bool ok = true;
    bool ok1 = true;
    QSqlQuery query1;
    QString ucz_imie = ui->ucz_imie->text();
    QString ucz_naz = ui->ucz_naz->text();
    int ucz_pesel = ui->ucz_pesel->text().toInt(&ok);
    int ucz_klasa = ui->ucz_klasa->text().toInt(&ok1);
    if(ok && ok1 && !ucz_imie.trimmed().isEmpty() && !ucz_naz.trimmed().isEmpty()){
        QSqlQuery query;
        query.prepare("insert into students values(" + QString::number(ucz_pesel) + ", '" + ucz_imie + "', '" + ucz_naz + "', " + QString::number(ucz_klasa) + ")");
        query.exec();
    }
    query1.prepare("SELECT * FROM [schoolDatabase].[dbo].[students]");
    if(query1.exec()) {
        int cols = query1.record().count();
        while(query1.next()) {
            for (int i=0; i<cols; i++)
                std::cout << query1.value(i).toString().toStdString() << " ";
        }
    }
    qTable->setQuery(query1);
    ui->tableView->show();
}

void MainWindow::on_delete_button_clicked()
{
    QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();
    std::vector<int> rows_indexes;
    int here;
    for( int i=0; i<selectedList.count(); i++) {
        //QMessageBox::information(this,"", QString::number(selectedList.at(i).row()));
        here = QString::number(selectedList.at(i).row()).toInt();
        rows_indexes.push_back(here);
    }
    QString data = ui->tableView->model()->index(rows_indexes.at(0), 0).data().toString();
    //QMessageBox::information(this, "", data);
    QSqlQuery query;

    QSqlQuery query1;
    QString prim_key = "DELETE FROM [schoolDatabase].[dbo].[students] where pesel=" + data;
    query.prepare(prim_key);
    if(query.exec()){
        while (query.next()){}
    }

    query1.prepare("SELECT * FROM [schoolDatabase].[dbo].[students]");
    if(query1.exec()) {
        int cols = query1.record().count();
        while(query1.next()) {
            for (int i=0; i<cols; i++)
                std::cout << query1.value(i).toString().toStdString() << " ";
        }
    }
    qTable->setQuery(query1);
    ui->tableView->show();

}

void MainWindow::on_editButton_clicked()
{
    QString str = ui->lineEdit->text();
    if(str.toStdString() =="teachers") {
        QMessageBox::information(this,"", "one");
    }
    QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();
    std::vector<int> rows_indexes;
    int here;
    for( int i=0; i<selectedList.count(); i++) {
        here = QString::number(selectedList.at(i).row()).toInt();
        rows_indexes.push_back(here);
    }
    QString data = ui->tableView->model()->index(rows_indexes.at(0), 0).data().toString();
    QSqlQuery query;

    QSqlQuery query1;
    QString prim_key = "DELETE FROM [schoolDatabase].[dbo].[students] where pesel=" + data;
    if(str.toStdString() =="teachers") {
        prim_key = "DELETE FROM [schoolDatabase].[dbo].[teachers] where teacher_id=" + data;
    }
    query.prepare(prim_key);
    if(query.exec()){
        while (query.next()){}
    }
    QStringList list = str.split(QRegExp("[\r\n\t ]+"), QString::SkipEmptyParts);
    bool ok = true;
    bool ok1 = true;
    QString ucz_imie = list[1];
    QString ucz_naz = list[2];
    int ucz_pesel = list[0].toInt(&ok);
    int ucz_klasa = list[3].toInt(&ok1);
    //QMessageBox::information(this,"", ucz_imie);
    if(ok && ok1 && !ucz_imie.trimmed().isEmpty() && !ucz_naz.trimmed().isEmpty()){
        QSqlQuery query2;
        query2.prepare("insert into students values(" + QString::number(ucz_pesel) + ", '" + ucz_imie + "', '" + ucz_naz + "', " + QString::number(ucz_klasa) + ")");
        if(str.toStdString() =="teachers") {
            query2.prepare("insert into students values(" + QString::number(ucz_pesel) + ", '" + ucz_imie + "', '" + ucz_naz + "', " + QString::number(ucz_klasa) + ")");
        }
        if(query2.exec()){
            while (query2.next()){}
        }
    }
    query1.prepare("SELECT * FROM [schoolDatabase].[dbo].[students]");
    if(str.toStdString()=="teachers") query1.prepare("SELECT * FROM [schoolDatabase].[dbo].[teachers]");
    if(query1.exec()) {
        int cols = query1.record().count();
        while(query1.next()) {
            for (int i=0; i<cols; i++)
                std::cout << query1.value(i).toString().toStdString() << " ";
        }
    }
    qTable->setQuery(query1);
    ui->tableView->show();
}

