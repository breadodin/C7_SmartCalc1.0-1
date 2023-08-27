#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  sWindow = new Graph();
  connect(sWindow, &Graph::firstWindow, this, &MainWindow::show);
  tWindow = new CreditCalc();
  connect(tWindow, &CreditCalc::firstWindow, this, &MainWindow::show);
  dWindow = new DepositCalc();
  connect(dWindow, &DepositCalc::firstWindow, this, &MainWindow::show);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_double, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_left_b, SIGNAL(clicked()), this, SLOT(digits_input()));
  connect(ui->pushButton_right_b, SIGNAL(clicked()), this,
          SLOT(digits_input()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_input() {
  QPushButton *button = (QPushButton *)sender();
  QString input_text = button->text();
  if (ui->result_show->text() == "0" && input_text != ".") {
    ui->result_show->setText(input_text);
  } else {
    ui->result_show->setText(ui->result_show->text() + input_text);
  }
  if (input_text == "sqrt" || input_text == "cos" || input_text == "sin" ||
      input_text == "tan" || input_text == "acos" || input_text == "asin" ||
      input_text == "atan" || input_text == "log" || input_text == "ln") {
    ui->result_show->setText(ui->result_show->text() + "(");
  }
  if (input_text == "=") {
    on_pushButton_result_clicked();
  }
  if (input_text == "<") {
    on_pushButton_delete_clicked();
  }
}

void MainWindow::on_pushButton_reset_clicked() {
  ui->result_show->setText("0");
}
void MainWindow::on_pushButton_result_clicked() {
  int err = 0;
  double result = 0.0;
  QString result_string;
  QString screen_result = ui->result_show->text();
  QByteArray mass_chars = screen_result.toLocal8Bit();
  char *ptr_mass_chars = mass_chars.data();

  err = qt_calculator(ptr_mass_chars, 0, &result);
  if (err == 0) {
    QString result_string = QString::number(result, 'g', 15);
    ui->result_show->setText(result_string);
  } else {
    ui->result_show->setText("ERROR");
  }
}

void MainWindow::on_pushButton_delete_clicked() {
  QString screen_result = ui->result_show->text();
  screen_result.chop(1);
  ui->result_show->setText(screen_result);
}

void MainWindow::on_pushButton_GRAPH_clicked() {
  sWindow->show();
  this->close();
}

void MainWindow::on_pushButton_CREDIT_clicked() {
  tWindow->show();
  this->close();
}

void MainWindow::on_pushButton_DEPOSIT_clicked() {
  dWindow->show();
  this->close();
}
