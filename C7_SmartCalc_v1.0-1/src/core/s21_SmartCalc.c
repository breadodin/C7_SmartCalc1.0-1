#include "s21_SmartCalc.h"

int qt_calculator(const char *input, double x_value, double *result) {
  int err = 0;
  err = s21_check_input(input);
  if (err == 0) {
    elements calc_input[MAX_STACK] = {0};
    elements *parser_input = calc_input;
    elements calc_output[MAX_STACK] = {0};
    elements *parser_output = calc_output;
    int size = 0;
    err = convert_to_struct(input, x_value, parser_input, &size);
    if (err == 0) {
      sort_station(parser_input, parser_output, &size);
      s21_calculator(parser_output, size, result);
      if (*result != *result) err = 6;
    }
  }
  return err;
}

void s21_calculator(elements *parser_output, int size, double *result) {
  int size_in = size;
  double stack_calc[MAX_STACK] = {0};
  if (parser_output != NULL) {
    for (int i = 0; i < size; i++) {
      if (parser_output->type == 1) {
        stack_calc[i] = parser_output->value;
      }
      if (parser_output->type == 2) {
        double val2 = stack_calc[i - 1];
        double val1 = stack_calc[i - 2];
        stack_calc[i - 1] = 0;
        stack_calc[i - 2] = 0;
        char operation_calc[5];
        for (int k = 0; k < 5; k++) {
          operation_calc[k] = parser_output->operation[k];
        }
        i = i - 2;
        size = size - 2;
        double res = calculate(val1, val2, operation_calc);
        stack_calc[i] = res;
      }
      if (parser_output->type == 3) {
        double val2 = stack_calc[i - 1];
        double val1 = 0;
        stack_calc[i - 1] = 0;
        char operation_calc[5];
        for (int k = 0; k < 5; k++) {
          operation_calc[k] = parser_output->operation[k];
        }
        i--;
        size--;
        double res = calculate(val1, val2, operation_calc);
        stack_calc[i] = res;
      }
      parser_output++;
    }
    *result = stack_calc[0];
    if (*result != *result) *result = NAN;
  }
  free_struct(parser_output - size_in, size_in);
  for (int k = 0; k < MAX_STACK; k++) {
    stack_calc[k] = 0;
  }
}

double calculate(double val1, double val2, char *operation) {
  double result = 0.0;
  if (operation[0] == '+')
    result = val1 + val2;
  else if (operation[0] == '-')
    result = val1 - val2;
  else if (operation[0] == '*')
    result = val1 * val2;
  else if (operation[0] == '/')
    result = val1 / val2;
  else if (operation[0] == '^')
    result = pow(val1, val2);
  else if (!strcmp(operation, "mod"))
    result = fmod(val1, val2);
  else if (!strcmp(operation, "sin"))
    result = sin(val2);
  else if (!strcmp(operation, "cos"))
    result = cos(val2);
  else if (!strcmp(operation, "tan"))
    result = tan(val2);
  else if (!strcmp(operation, "acos"))
    result = acos(val2);
  else if (!strcmp(operation, "asin"))
    result = asin(val2);
  else if (!strcmp(operation, "atan"))
    result = atan(val2);
  else if (!strcmp(operation, "sqrt"))
    result = sqrt(val2);
  else if (!strcmp(operation, "ln"))
    result = log(val2);
  else if (!strcmp(operation, "log"))
    result = log10(val2);
  return result;
}
