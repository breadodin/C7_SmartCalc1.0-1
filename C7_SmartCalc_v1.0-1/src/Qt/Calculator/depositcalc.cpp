
#include "depositcalc.h"

#include <math.h>

#include <QDateTime>

#include "ui_depositcalc.h"

DepositCalc::DepositCalc(QWidget *parent)
    : QWidget(parent), ui(new Ui::DepositCalc) {
  ui->setupUi(this);
}

DepositCalc::~DepositCalc() { delete ui; }

void DepositCalc::on_pushButton_back_clicked() {
  this->close();
  emit firstWindow();
}

void DepositCalc::on_pushButton_calc_clicked() {
  bool ok1, ok2, ok3, ok4, ok5;
  double sum = ui->line_sum->text().toDouble(&ok1);
  int time = ui->line_time->text().toInt(&ok2);
  double per = ui->line_per->text().toDouble(&ok3);
  int period = 1;
  int divisor = 1;

  if (ui->radioButton_year->isChecked()) {
    time *= 12;
  }

  if (ui->periodBox->currentText() == "Ежемесячно") {
    period = 12;
    divisor = 1;
  } else if (ui->periodBox->currentText() == "Ежеквартально") {
    period = 4;
    divisor = 3;
  } else if (ui->periodBox->currentText() == "Ежегодно") {
    period = 1;
    divisor = 12;
  }

  double monthlyDeposit = ui->line_monthly_deposit->text().toDouble(&ok4);
  double monthlyWithdrawal = ui->line_monthly_withdrawal->text().toDouble(&ok5);

  if (ok1 && ok2 && ok3 && ok4 && ok5 && time > 0 && per >= 0.01) {
    double taxRate = 0.13;
    double keyRate = 0.0425;
    double exemptedIncome = 1000000 * keyRate;

    double interest = 0.0;
    double totalInterest = 0.0;
    double finalAmount = sum;

    if (ui->capitalizationCheck->isChecked()) {
      per /= 100;
      double principal = sum;

      for (int i = 0; i < time / divisor; ++i) {
        double monthlyInterest =
            (principal * per / period) + monthlyDeposit - monthlyWithdrawal;
        principal += monthlyInterest;
        totalInterest += monthlyInterest;
      }
      interest = totalInterest;
      finalAmount += totalInterest;
    } else {
      interest = ((sum * per * time) / (100 * period)) / divisor;
      finalAmount += (monthlyDeposit * period);
      finalAmount -= (monthlyWithdrawal * period);
    }

    double taxableIncome = interest - exemptedIncome;
    if (taxableIncome < 0) {
      taxableIncome = 0;
    }

    double tax = taxableIncome * taxRate;
    double finalInterest = interest - tax;

    if (ui->capitalizationCheck->isChecked()) {
      finalAmount -= tax;
    }

    ui->per_->setText(QString::number(finalInterest, 'f', 2));
    ui->tax_->setText(QString::number(tax, 'f', 2));
    ui->sum_->setText(QString::number(finalAmount, 'f', 2));
  } else {
    ui->per_->setText("ERROR");
    ui->tax_->setText("please enter");
    ui->sum_->setText("only numbers");
  }
}
