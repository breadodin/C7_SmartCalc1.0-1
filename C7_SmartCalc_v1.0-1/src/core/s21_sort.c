#include "s21_SmartCalc.h"

void sort_station(elements *parser_input, elements *parser_output, int *size) {
  int count_out = *size, size_in = *size, count_in = 0, i = 0;
  elements stack_tmp[MAX_STACK] = {0};
  elements *stack_ptr = stack_tmp;
  while (count_in++ < *size) {
    if (parser_input->type == 1) {
      fill_struct(parser_output, parser_input);
      parser_output++;
    }
    if (parser_input->type == 2 || parser_input->type == 3) {
      while (i > 0) {
        stack_ptr--;
        if (parser_input->priority <= stack_ptr->priority) {
          fill_struct(parser_output, stack_ptr);
          parser_output++;
          i--;
        } else {
          stack_ptr++;
          break;
        }
      }
      fill_struct(stack_ptr, parser_input);
      stack_ptr++;
      i++;
    }
    if (parser_input->type == 4) {
      sort_brackets(parser_input, &parser_output, &stack_ptr, &i, &count_out);
    }
    parser_input++;
  }
  while (i > 0) {
    stack_ptr--;
    fill_struct(parser_output, stack_ptr);
    parser_output++;
    i--;
  }
  *size = count_out;
  free_struct(parser_input - size_in, size_in);
}

void sort_brackets(elements *parser_input, elements **parser_output,
                   elements **stack_ptr, int *i, int *count_out) {
  if (parser_input->operation[0] == '(') {
    (*count_out)--;
    fill_struct(*stack_ptr, parser_input);
    (*stack_ptr)++;
    (*i)++;
  }
  if (parser_input->operation[0] == ')') {
    (*count_out)--;
    while (*i > 0) {
      (*stack_ptr)--;
      if ((*stack_ptr)->operation[0] == '(') {
        (*i)--;
        break;
      } else {
        fill_struct(*parser_output, *stack_ptr);
        (*parser_output)++;
        (*i)--;
      }
    }
  }
}

void fill_struct(elements *fill, elements *in) {
  fill->type = in->type;
  fill->operation[0] = in->operation[0];
  fill->operation[1] = in->operation[1];
  fill->operation[2] = in->operation[2];
  fill->operation[3] = in->operation[3];
  fill->operation[4] = in->operation[4];
  fill->priority = in->priority;
  fill->value = in->value;
}

void free_struct(elements *elements, int size) {
  for (int k = 0; k < size; k++) {
    elements[k].type = 0;
    elements[k].priority = 0;
    elements[k].operation[0] = '\0';
    elements[k].operation[1] = '\0';
    elements[k].operation[2] = '\0';
    elements[k].operation[3] = '\0';
    elements[k].operation[4] = '\0';
    elements[k].value = 0;
  }
}
