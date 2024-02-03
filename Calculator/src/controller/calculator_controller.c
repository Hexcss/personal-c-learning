#include "calculator_controller.h"
#include "../model/calculator_model.h"
#include "../view/calculator_view.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBERS 100

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { } 
}

int read_numbers(double **numbers) {
    size_t capacity = 10;
    size_t size = 0;
    double *array = malloc(capacity * sizeof(double));
    if (array == NULL) {
        perror("Unable to allocate memory");
        exit(EXIT_FAILURE);
    }
    
    printf("Enter numbers (end with 'q'): ");
    
    double temp;
    while (scanf("%lf", &temp) == 1) {
        if (size >= capacity) {
            capacity *= 2;
            double *temp_array = realloc(array, capacity * sizeof(double));
            if (temp_array == NULL) {
                free(array);
                perror("Unable to allocate more memory");
                exit(EXIT_FAILURE);
            }
            array = temp_array;
        }
        array[size++] = temp;
    }
    clear_input_buffer(); // Clear buffer after number input

    *numbers = array;
    return size;
}

char read_operation() {
    char operation;
    printf("Enter an operation (+, -, *, /) or 'q' to quit: ");
    scanf(" %c", &operation);
    return operation;
}

void execute_operations(char operation, double *numbers, int count) {
    double result;
    switch(operation) {
        case '+':
            result = add(numbers, count);
            display_result(result);
            break;
        case '-':
            result = subtract(numbers, count);
            display_result(result);
            break;
        case '*':
            result = multiply(numbers, count);
            display_result(result);
            break;
        case '/':
            result = divide(numbers, count);
            display_result(result);
            break;
        default:
            printf("Invalid operation '%c'. Please try again.\n", operation);
    }
}

char ask_to_continue() {
    printf("Would you like to perform another operation? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    return choice;
}