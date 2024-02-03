#include "controller/calculator_controller.h"
#include <stdio.h>

int main() {
    double *numbers;
    char operation, choice;
    int num_count;

    do {
        num_count = read_numbers(&numbers);
        if (num_count == 0) {
            printf("No valid numbers entered. Please try again.\n");
            continue;
        }

        operation = read_operation();
        if (operation == 'q') {
            free(numbers); 
            break;
        }

        execute_operations(operation, numbers, num_count);
        choice = ask_to_continue();
        if (choice != 'y') {
            free(numbers); 
            break;
        }

    } while (1);

    printf("Calculator exiting. Goodbye!\n");
    return 0;
}
