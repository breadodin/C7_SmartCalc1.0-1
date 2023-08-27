#include <check.h>

#include "../s21_SmartCalc.h"

START_TEST(check_input) {
  int err = 0;
  char string[] = "1+2+3-log(6)*sqrt(10)+ln(10)";
  err = s21_check_input(string);
  ck_assert_int_eq(0, err);

  char string_1[] = "1+2+3*ln()";
  err = s21_check_input(string_1);
  ck_assert_int_eq(2, err);

  char string_2[] = "1.123123+2mod4+(3*7)+sqrt(7)";
  err = s21_check_input(string_2);
  ck_assert_int_eq(0, err);

  char string_3[] = "1+2mod4+3*(7+1)+acos(1/2)+5^2";
  err = s21_check_input(string_3);
  ck_assert_int_eq(0, err);

  char string_4[] = "1+2mod4+3*(7+1d)+asin(1/2)";
  err = s21_check_input(string_4);
  ck_assert_int_eq(1, err);

  char string_5[] = "^1+2mod4+3*(7+1)+atan(1/2)";
  err = s21_check_input(string_5);
  ck_assert_int_eq(1, err);

  char string_6[] = "cos(1/2)+2mod4+3*(7+1)+sin(0)";
  err = s21_check_input(string_6);
  ck_assert_int_eq(0, err);

  char string_7[] = "tan(1/2)+2mod4+3*(7+1)+asin(0)+atan(0)";
  err = s21_check_input(string_7);
  ck_assert_int_eq(0, err);

  char string_8[] = "123456789+";
  err = s21_check_input(string_8);
  ck_assert_int_eq(1, err);

  char string_9[] = "1/2+aco(3)-lo(6)+l(8)-asi(5)+at(3)+tcos(213)^";
  err = s21_check_input(string_9);
  ck_assert_int_eq(1, err);

  char string_10[] = "";
  err = s21_check_input(string_10);
  ck_assert_int_eq(4, err);

  char string_11[] = "!1+4-f+d/";
  err = s21_check_input(string_11);
  ck_assert_int_eq(1, err);

  char string_12[] = "1+4/";
  err = s21_check_input(string_12);
  ck_assert_int_eq(1, err);

  char string_13[] = "1+4*";
  err = s21_check_input(string_13);
  ck_assert_int_eq(1, err);

  char string_14[] = "1+5-4*)";
  err = s21_check_input(string_14);
  ck_assert_int_eq(1, err);

  char string_15[] = "1+((5-4)/410";
  err = s21_check_input(string_15);
  ck_assert_int_eq(3, err);

  char string_16[] = "4mid2+(5-4)";
  err = s21_check_input(string_16);
  ck_assert_int_eq(1, err);

  char string_17[] = "00+(5-4)";
  err = s21_check_input(string_17);
  ck_assert_int_eq(1, err);

  char string_18[] = "*0+(5-4)";
  err = s21_check_input(string_18);
  ck_assert_int_eq(1, err);

  char string_19[] = "1/0 + 2";
  err = s21_check_input(string_19);
  ck_assert_int_eq(5, err);

  char string_20[] = "1+";
  err = s21_check_input(string_20);
  ck_assert_int_eq(1, err);
}
END_TEST

START_TEST(calculator) {
  elements calc_input[MAX_STACK] = {0};
  elements *parser_input = calc_input;
  elements calc_output[MAX_STACK] = {0};
  elements *parser_output = calc_output;
  double res_21 = 0.0;
  double res_original = 0.0;
  int n;

  char input[] = "-cos(1)+3";
  convert_to_struct(input, 0, parser_input, &n);
  sort_station(parser_input, parser_output, &n);
  s21_calculator(parser_output, n, &res_21);
  res_original = -cos(1) + 3;
  ck_assert_double_eq(res_original, res_21);

  char input_1[] = "-0.1+0.2";
  convert_to_struct(input_1, 0, parser_input, &n);
  sort_station(parser_input, parser_output, &n);
  s21_calculator(parser_output, n, &res_21);
  res_original = -0.1 + 0.2;
  ck_assert_double_eq(res_original, res_21);

  char input_2[] =
      "15.4121212121212/(7.1-(1.1+1.1))*3-(2+(1+1))*15.4/"
      "(7-(200.1+1))*3-(2+(1+1))*(15.0/"
      "(7-(1.1+1))*3.4-(2+(1+1))+15.23456789101112/(7.5-(1+1))*3.5-(2+(1+1)))";
  convert_to_struct(input_2, 0, parser_input, &n);
  sort_station(parser_input, parser_output, &n);
  s21_calculator(parser_output, n, &res_21);
  res_original = 15.4121212121212 / (7.1 - (1.1 + 1.1)) * 3 -
                 (2 + (1 + 1)) * 15.4 / (7 - (200.1 + 1)) * 3 -
                 (2 + (1 + 1)) * (15.0 / (7 - (1.1 + 1)) * 3.4 - (2 + (1 + 1)) +
                                  15.23456789101112 / (7.5 - (1 + 1)) * 3.5 -
                                  (2 + (1 + 1)));
  ck_assert_double_eq(res_original, res_21);

  char input_3[] = "2^(2.1+1)-11mod2";
  convert_to_struct(input_3, 0, parser_input, &n);
  sort_station(parser_input, parser_output, &n);
  s21_calculator(parser_output, n, &res_21);
  res_original = pow(2, (2.1 + 1)) - fmod(11, 2);
  ck_assert_double_eq(res_original, res_21);

  char input_4[] = "sin(0.5)-cos(1)+tan(0.5)+acos(0.5)-asin(1)-atan(1)";
  convert_to_struct(input_4, 0, parser_input, &n);
  sort_station(parser_input, parser_output, &n);
  s21_calculator(parser_output, n, &res_21);
  res_original = sin(0.5) - cos(1) + tan(0.5) + acos(0.5) - asin(1) - atan(1);
  ck_assert_double_eq(res_original, res_21);

  char input_5[] = "sqrt(4.123456789)+3-1.12";
  convert_to_struct(input_5, 0, parser_input, &n);
  sort_station(parser_input, parser_output, &n);
  s21_calculator(parser_output, n, &res_21);
  res_original = sqrt(4.123456789) + 3 - 1.12;
  ck_assert_double_eq(res_original, res_21);

  char input_6[] = "log(+10.2)-ln(10.2)";
  convert_to_struct(input_6, 0, parser_input, &n);
  sort_station(parser_input, parser_output, &n);
  s21_calculator(parser_output, n, &res_21);
  res_original = log10(10.2) - log(10.2);
  ck_assert_double_eq(res_original, res_21);

  char input_7[] = "11+(-2)^5";
  convert_to_struct(input_7, 0, parser_input, &n);
  sort_station(parser_input, parser_output, &n);
  s21_calculator(parser_output, n, &res_21);
  res_original = 11 + pow(-2, 5);
  ck_assert_double_eq(res_original, res_21);

  char input_8[] = "log(10.2)+ln(10.2)";
  convert_to_struct(input_8, 0, parser_input, &n);
  sort_station(parser_input, parser_output, &n);
  s21_calculator(parser_output, n, &res_21);
  res_original = log10(10.2) + log(10.2);
  ck_assert_double_eq(res_original, res_21);

  char input_9[] = "sqrt(+4+1)+(-3+1)";
  convert_to_struct(input_9, 0, parser_input, &n);
  sort_station(parser_input, parser_output, &n);
  s21_calculator(parser_output, n, &res_21);
  res_original = sqrt(4 + 1) + (-3 + 1);
  ck_assert_double_eq(res_original, res_21);

  char input_10[] = "sqrt(3+1)-(-3+1)";
  convert_to_struct(input_10, 0, parser_input, &n);
  sort_station(parser_input, parser_output, &n);
  s21_calculator(parser_output, n, &res_21);
  res_original = sqrt(3 + 1) - (-3 + 1);
  ck_assert_double_eq(res_original, res_21);

  char input_11[] = "+1.1122-(-1)";
  convert_to_struct(input_11, 0, parser_input, &n);
  sort_station(parser_input, parser_output, &n);
  s21_calculator(parser_output, n, &res_21);
  res_original = +1.1122 - (-1);
  ck_assert_double_eq(res_original, res_21);

  char input_12[] = "sin(x)";
  convert_to_struct(input_12, 1.1, parser_input, &n);
  sort_station(parser_input, parser_output, &n);
  s21_calculator(parser_output, n, &res_21);
  res_original = sin(1.1);
  ck_assert_double_eq(res_original, res_21);

  char input_21[] = "2^(2.1+1)-11mid2";
  int err = convert_to_struct(input_21, 0, parser_input, &n);
  ck_assert_int_eq(1, err);

  char input_22[] = "2^(2.1+1)-11mid2";
  double res = 0.0;
  err = qt_calculator(input_22, 0, &res);
  ck_assert_int_eq(1, err);

  char input_23[] = "2^(2.1+1)+(";
  res = 0.0;
  err = qt_calculator(input_23, 0, &res);
  ck_assert_int_eq(3, err);

  char input_24[] = "2^(2.1+1)+()";
  res = 0.0;
  err = qt_calculator(input_24, 0, &res);
  ck_assert_int_eq(2, err);

  char input_25[] = "2^(2.1+1)+2-(3+1)";
  res = 0.0;
  err = qt_calculator(input_25, 0, &res);
  ck_assert_int_eq(0, err);

  char input_26[] = "cos(x)";
  res = 0.0;
  err = qt_calculator(input_26, 1, &res);
  ck_assert_int_eq(0, err);
}
END_TEST

Suite *s21_SmartCalc_tests_create() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_SmartCalc");
  tc_core = tcase_create("tests");
  tcase_add_test(tc_core, check_input);
  tcase_add_test(tc_core, calculator);
  suite_add_tcase(s, tc_core);
  return s;
}
int main() {
  Suite *s = s21_SmartCalc_tests_create();
  SRunner *s21_SmartCalc_runner = srunner_create(s);
  int number_failed;
  srunner_run_all(s21_SmartCalc_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(s21_SmartCalc_runner);
  srunner_free(s21_SmartCalc_runner);

  return number_failed == 0 ? 0 : 1;
}
