#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void LerTXTPrintarTabela();

    void ListarPrintarProcessos();

    void store_processes(QString  input_str);

    QStringList get_processes_info();

    void init_table();

    void fill_table();


    void update_table();

private slots:

    void on_pushButton_Kill_clicked();

    void on_pushButton_2_Stop_clicked();

    void on_pushButton_3_Cont_clicked();

    //void on_pushButton_4_Go_clicked();

    //void filtro();

    QString pegarPID();


    void on_pushButton_5_GoPriority_clicked();

    void on_pushButton_6_GoCPU_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
