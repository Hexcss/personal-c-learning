#include "calculator_view.h"
#include <stdio.h>

void display_result(double result) {
    printf("Result: %.2lf\n", result);
}

void display_error() {
    printf("Cannot divide by zero!\n");
}
