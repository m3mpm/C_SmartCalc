#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// добавил библиотеки
#include <iostream>
#include <QString>
#include <QByteArray>
#include <QKeyEvent>
#include <QVector>
#include <QtMath>
#include <QTableWidget>
#include <qtablewidget.h>

// добавление функции из си
extern "C" {
#include "calc_logic.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void digits_numbers();
    void on_pushButton_erase_clicked();
    void on_pushButton_dot_clicked();
    void math_operations_div();
    void math_operations_multi();
    void math_operations_exp();
    void math_operations_plus();
    void math_operations_minus();
    void functions();
    void brackets();
    void on_pushButton_clear_clicked();
    void on_pushButton_getResult_clicked();

    void on_pushButton_graph_clicked();

    void on_pushButton_comeBackToCalc1_clicked();

    void on_pushButton_clearGraph_clicked();

    void on_pushButton_buildGraph_clicked();


    void on_pushButton_creditCalc_clicked();

    void on_pushButton_creditGetResult_clicked();

    void on_pushButton_comeBackToCalc2_clicked();

    void on_pushButton_creditClear_clicked();

    void on_pushButton_popolnit_snyant_clicked();

    void on_pushButton_getResultDeposit_clicked();

    void on_pushButton_depositCalc_clicked();

    void on_pushButton_clearDeposit_clicked();

    void on_pushButton_comeBackToCalc3_clicked();

protected:
    void keyPressEvent( QKeyEvent *event );

    double calculateNalog(double input_procentNalogCb, double input_procentNalog, double yearProfit_i);

};
#endif // MAINWINDOW_H
