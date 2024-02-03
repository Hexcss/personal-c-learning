#include "calculator_model.h"
#include "../view/calculator_view.h"

double add(double *numbers, int count) {
    double result = 0;
    for (int i = 0; i < count; i++) {
        result += numbers[i];
    }
    return result;
}

double subtract(double *numbers, int count) {
    if (count == 0) {
        return 0;
    }
    double result = numbers[0];
    for (int i = 1; i < count; i++) {
        result -= numbers[i];
    }
    return result;
}

double multiply(double *numbers, int count) {
    if (count == 0) {
        return 1; 
    }
    double result = numbers[0];
    for (int i = 1; i < count; i++) {
        result *= numbers[i];
    }
    return result;
}

double divide(double *numbers, int count) {
    if (count == 0) {
        return 1; 
    }
    double result = numbers[0];
    for (int i = 1; i < count; i++) {
        if (numbers[i] == 0) {
            display_error();
            return 0; 
        }
        result /= numbers[i];
    }
    return result;
}
