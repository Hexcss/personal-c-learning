#ifndef CALCULATOR_CONTROLLER_H
#define CALCULATOR_CONTROLLER_H

void clear_input_buffer();
void execute_operations(char operation, double *numbers, int count);
int read_numbers(double **numbers);
char read_operation();
char ask_to_continue();

#endif