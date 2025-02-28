#ifndef CALCULATOR_H
#define CALCULATOR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int current_char;
    int error;
    int float_mode;
} CalculatorState;

void init_calculator(CalculatorState* state);
double calculate_expression(CalculatorState* state, const char* input);

#ifdef __cplusplus
}
#endif

#endif
