#ifndef DEPOSITCALC_H
#define DEPOSITCALC_H

#include <QWidget>

namespace Ui {
class DepositCalc;
}

class DepositCalc : public QWidget {
  Q_OBJECT

 public:
  explicit DepositCalc(QWidget *parent = nullptr);
  ~DepositCalc();

 signals:
  void firstWindow();

 private slots:
  void on_pushButton_back_clicked();

  void on_pushButton_calc_clicked();

 private:
  Ui::DepositCalc *ui;
};

#endif  //  DEPOSITCALC_H
