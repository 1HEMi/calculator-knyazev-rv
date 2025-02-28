#include "calculator.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    CalculatorState state;
    init_calculator(&state);

    if (argc > 1 && strcmp(argv[1], "--float") == 0) {
        state.float_mode = 1;
    }

    double result = calculate_expression(&state, NULL);

    if (state.error)
        return 1;

    if (state.float_mode) {
        printf("%.4f\n", result);
    } else {
        printf("%.0f\n", result);
    }
    return 0;
}
