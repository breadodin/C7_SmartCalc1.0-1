#ifndef MAINWINDOW_H
#define MAINWINDOW_H

extern "C" {
#include "../../core/s21_SmartCalc.h"
}

#include <creditcalc.h>
#include <depositcalc.h>
#include <graph.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  Graph *sWindow;
  CreditCalc *tWindow;
  DepositCalc *dWindow;

 private slots:
  void digits_input();
  void on_pushButton_reset_clicked();
  void on_pushButton_result_clicked();
  void on_pushButton_delete_clicked();
  void on_pushButton_GRAPH_clicked();
  void on_pushButton_CREDIT_clicked();
  void on_pushButton_DEPOSIT_clicked();
};

#endif  //  MAINWINDOW_H
