#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <QLineEdit>
#include <QWidget>

using namespace std;

QString pid;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Kill_clicked()
{

}

void MainWindow::on_pushButton_2_Stop_clicked()
{

}

void MainWindow::on_pushButton_3_Cont_clicked()
{

}
void MainWindow::filtro(){
    QString textoFiltro = ui->lineEdit_4_Filtro->text();

    QString comando;
    comando = " ps -auf | grep " + textoFiltro;

    QByteArray comandoConvertido = comando.toLocal8Bit();
    const char *comandoFinal = comandoConvertido.data();

    system(comandoFinal);
}
void MainWindow::pegarPID(){
    pid = ui->lineEdit_PID->text();
}
