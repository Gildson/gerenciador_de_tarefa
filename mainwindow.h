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

private slots:
    void on_pushButton_Kill_clicked();

    void on_pushButton_2_Stop_clicked();

    void on_pushButton_3_Cont_clicked();

    void filtro();

    void pegarPID();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
