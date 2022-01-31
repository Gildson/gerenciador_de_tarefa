#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <QLineEdit>
#include <QWidget>
#include <string.h>
#include <iostream>
#include <fstream>
#include <QString>
#include <QLabel>
#include <sched.h>
#include <QFile>
#include <QTimer>
#include <sys/time.h>
#include <sys/resource.h>
#include <QTextStream>
#include <QStringList>

using namespace std;

QString pid;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    store_processes(ui->lineEdit_4_Filtro->text());
    init_table();
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::update_table);//conectar o sinal para fazer uma acao, que vai ser chamar a funcao de atualizar tabela
    timer->start(1000);// faz o update a cada 1s

}

MainWindow::~MainWindow()
{
    delete ui;
}

//enviar o comando para pegar os processos todos e jogar no txt
void MainWindow::store_processes(QString  input_str){
    if (input_str.isEmpty() or input_str.isNull()){
        system("ps -auf > processos_lista.txt");
    }
    else{
        std::string utf8_text = input_str.toStdString();
        std::string first_char = utf8_text.substr(0,1);
        std::string remaing_chars = utf8_text.substr(1,utf8_text.length());
        std::string command = "ps -auf | grep \"[" + first_char + "]" + remaing_chars + "\" > processos_lista.txt";
        const char * cmd = command.c_str();
        std::cout << cmd << std::endl;

        system(cmd);
    }
}

//pegar os processos todos e deixar no formato para exibir na tabela da aplicacao
QStringList MainWindow::get_processes_info(){
    QFile inputFile("processos_lista.txt");
    QStringList lines;
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          //qDebug() << line;
          lines.append(line);
       }
       inputFile.close();
    }
    return lines;
}

//inicia a tabela sempre com todos os processos
void MainWindow::init_table(){
    QStringList process_info = get_processes_info();
    QStringList headers = process_info.at(0).split(" ", QString::SkipEmptyParts);//pega o header do retorno da funcao ps -auf, e quebra numa lista de strings, cada posicao da lista eh uma coluna e o skip resolve o problema do espacamento


    ui->tableWidget->setColumnCount(headers.count());
    ui->tableWidget->verticalHeader()->setVisible(false);
    //ui->tableWidget->horizontalHeader()->setVisible(false);

    fill_table();
}

void MainWindow::fill_table(){
    QStringList process_info = get_processes_info();
    int n_rows = process_info.count();
    ui->tableWidget->setRowCount(n_rows);
    int n_cols = ui->tableWidget->columnCount();


    for (int row=0; row<n_rows; row++){
        //quebrar a string da linha baseado no espaco
        QStringList data = process_info.at(row).split(" ", QString::SkipEmptyParts);
        for (int col=0; col<n_cols; col++){
            QTableWidgetItem *item = new QTableWidgetItem;
            //nao quebra a string baseada em espaco para a ultima coluna, onde tem o comando, agrupa tudo numa só
            if (col == n_cols-1){
                QString last_col;
                for (int cmd_word_index=col; cmd_word_index<data.count(); cmd_word_index++){
                    last_col.append(data.at(cmd_word_index) + " ");
                }
                item->setText(last_col);
            }
            else{
                item->setText(data.at(col));
            }
            ui->tableWidget->setItem(row, col, item);
        }
    }
}

void MainWindow::update_table(){
    store_processes(ui->lineEdit_4_Filtro->text());
    fill_table();
}


void MainWindow::on_pushButton_Kill_clicked()
{
    pid = pegarPID();
    QByteArray pid_array = pid.toLocal8Bit();
    const char *pid_str = pid_array.data();
    int pid_int = atoi(pid_str);
    pid_t pidConvertido = (pid_t) pid_int;

    kill(pidConvertido,SIGKILL);

}

void MainWindow::on_pushButton_2_Stop_clicked()
{
    pid = pegarPID();
    QByteArray pid_array = pid.toLocal8Bit();
    const char *pid_str = pid_array.data();
    int pid_int = atoi(pid_str);
    pid_t pidConvertido =  (pid_t) pid_int;

    kill(pidConvertido,SIGSTOP);
}

void MainWindow::on_pushButton_3_Cont_clicked()
{
    pid = pegarPID();
    QByteArray pid_array = pid.toLocal8Bit();
    const char *pid_str = pid_array.data();
    int pid_int = atoi(pid_str);
    pid_t pidConvertido =  (pid_t) pid_int;

    kill(pidConvertido,SIGCONT);
}


QString MainWindow::pegarPID(){
    pid = ui->lineEdit_PID->text();
    return pid;
}


void MainWindow::on_pushButton_5_GoPriority_clicked()
{
    pid = pegarPID();
    QByteArray pid_array = pid.toLocal8Bit();
    const char *pid_str = pid_array.data();
    int pid_int = atoi(pid_str);
    pid_t pidConvertido =  (pid_t) pid_int;

    QString priority_number = ui->lineEdit_2_Prioridade->text();
    QByteArray priority_number_array = priority_number.toLocal8Bit();
    const char *priority_number_str = priority_number_array.data();
    int priority_number_int = atoi(priority_number_str);

    setpriority(PRIO_PROCESS, pidConvertido, priority_number_int);// setpriority(int which, int who)  setpriority(int which, int who, int prio);

}



void MainWindow::on_pushButton_6_GoCPU_clicked()
{
    pid = pegarPID();
    QByteArray pid_array = pid.toLocal8Bit();
    const char *pid_str = pid_array.data();
    int pid_int = atoi(pid_str);
    pid_t pidConvertido =  (pid_t) pid_int;

    QString cpu_number = ui->lineEdit_3_CPU->text();
    QByteArray cpu_number_array = cpu_number.toLocal8Bit();
    const char *cpu_number_str = cpu_number_array.data();
    int cpu_number_int = atoi(cpu_number_str);

    cpu_set_t  mask;  // máscara para habilitação de CPUs

    CPU_SET(cpu_number_int, &mask);    // alocar na CPU que o cara digitar

    int result = sched_setaffinity(pidConvertido, sizeof(mask), &mask);//(piddoprocesso, tamanho mask, mascara)



}

