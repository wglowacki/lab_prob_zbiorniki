#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QtSql>
#include <QListWidgetItem>
#include <iostream>
#include <QtGui>
#include <QPoint>

extern QSqlDatabase db;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_pushButton_clicked();

    void on_TableView_clicked(const QModelIndex &index);

    void on_dodaj_butt_clicked();

    void on_delete_button_clicked();

    void on_pushButton_2_clicked();

    void on_editButton_clicked();

private:
    Ui::MainWindow *ui;

    QSqlQueryModel *qTable, *qFirstValue, *qSecondValue;


public:
    QSqlDatabase db;
    std::string table_name;

};

#endif // MAINWINDOW_H
