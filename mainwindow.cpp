#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QTableWidget>
#include <QTableWidgetItem>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui -> btn_ok ,&QPushButton::clicked,this,&MainWindow::get_data);
    connect(ui ->btn_ok ,&QPushButton::clicked,this,&MainWindow::print);

}


MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::get_data()
{

    QString name ;
    QString firstname ;
    QString age ;


    name  = ui -> lineEdit -> text();
    firstname = ui -> lineEdit_2 -> text();
    age = ui -> lineEdit_3 -> text();


    QFile file(filename);


    if(file.open(QIODevice::Append| QIODevice::Text))
    {
        QTextStream out(&file);

        out << name << ";";
        out << firstname << ";";
        out << age << "\n";

        ui -> lineEdit-> clear();
        ui -> lineEdit_2 -> clear();
        ui -> lineEdit_3 -> clear();

    }

}

void MainWindow::print()
{
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(3);
        ui->tableWidget->setHorizontalHeaderLabels({"Nom", "Prénom", "Âge"});

        QFile file(filename);
        QString line;
        QString colonne;
        int row;

        if(file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QTextStream in(&file);

            while(!in.atEnd())
            {
                line = in.readLine();
                QStringList colonnes = line.split(";");

                if (colonnes.size() >= 3)
                {
                    row = ui->tableWidget->rowCount();
                    ui->tableWidget->insertRow(row);

                    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(colonnes[0]));
                    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(colonnes[1]));
                    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(colonnes[2]));

                }
            }
        }

        file.close();
}

