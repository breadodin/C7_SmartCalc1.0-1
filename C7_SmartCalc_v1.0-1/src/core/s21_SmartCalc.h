#ifndef S21_SMARTCALC_H
#define S21_SMARTCALC_H

#include <math.h>
#include <stdio.h>
#include <string.h>

#define MAX_INPUT 255
#define MAX_STACK 265

//  types:
//  1 - число
//  2 - арифметика, mod и pow
//  3 - тригонометрия и sqrt
//  4 - скобки
//
//  priority:
//  1 - + -
//  2 - / * mod
//  3 - ^ sin cos... log ln
//
//  errors:
//  1 - некорректный инпут
//  2 - пустые скобки
//  3 - несовпадает кол-во скобок
//  4 - некорректная длина выражения
//  5 - деление на 0 или на корень отрицательного числа
//  6 - nan -> Error

typedef struct {
  int type;
  char operation[5];
  int priority;
  double value;
} elements;

int s21_check_input(const char *s);
void s21_calculator(elements *parser_output, int size, double *result);
int qt_calculator(const char *input, double x_value, double *result);
int convert_to_struct(const char *input, double x_value, elements *result,
                      int *size);
void convert_x(double x_value, int *i, elements *parser_input);
void convert_digit(int *i, const char *input, elements *parser_input, int *err);
void convert_sign(int i, const char *input, elements *parser_input);
int convert_word(int i, const char *input, elements *result, int *err);
void convert_brackets(int i, const char *input, elements *parser_input);
void convert_brackets_u(elements **parser_input);
void sort_station(elements *parser_input, elements *parser_output, int *size);
void sort_brackets(elements *parser_input, elements **parser_output,
                   elements **stack_ptr, int *i, int *count_out);
void fill_struct(elements *fill, elements *in);
void free_struct(elements *elements, int size);
void input_unary(elements *parser_input, int *count);
double calculate(double val1, double val2, char *operation);

//  input check
void check_input_start(const char *s, int *err);
void check_input_arithmetic(const char *s, int *err, int i);
void check_input_brackets(const char *s, int *err, int i);
void sum_brackets(int *err, int open, int close);
void check_correct(const char *s, int *err, int *open, int *close, int *i);

#endif  //  S21_SMARTCALC_H
