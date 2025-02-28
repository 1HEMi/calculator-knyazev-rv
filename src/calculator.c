#include "calculator.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static void get_next_char(CalculatorState* state);
static double parse_num(CalculatorState* state);
static double parse_mult_div(CalculatorState* state);
static double parse_add_subt(CalculatorState* state);

static void get_next_char(CalculatorState* state)
{
    do {
        state->current_char = getchar();
        if (state->current_char == EOF)
            return;

        if (!strchr("0123456789()*+/-. \t\n\r\v\f", state->current_char)) {
            state->error = 1;
        }
    } while (isspace(state->current_char));
}

static double parse_num(CalculatorState* state)
{
    if (state->error)
        return 0;
    double result = 0;

    if (state->current_char == '(') {
        get_next_char(state);
        result = parse_add_subt(state);
        if (state->current_char != ')') {
            state->error = 1;
            return 0;
        }
        get_next_char(state);
    } else if (isdigit(state->current_char) || state->current_char == '.') {
        int point = 0;
        double fraction = 1.0;

        if (state->current_char == '.') {
            if (!state->float_mode)
                state->error = 1;
            point = 1;
            get_next_char(state);
        }

        while (isdigit(state->current_char) || state->current_char == '.') {
            if (state->current_char == '.') {
                if (point || !state->float_mode)
                    state->error = 1;
                point = 1;
                get_next_char(state);
                continue;
            }

            if (point) {
                fraction *= 0.1;
                result += (state->current_char - '0') * fraction;
            } else {
                result = result * 10 + (state->current_char - '0');
            }
            get_next_char(state);
        }
    } else {
        state->error = 1;
    }
    return result;
}

static double parse_mult_div(CalculatorState* state)
{
    if (state->error)
        return 0;
    double result = parse_num(state);

    while (!state->error && (state->current_char == '*' || state->current_char == '/')) {
        char op = state->current_char;
        get_next_char(state);
        double num = parse_num(state);

        if (op == '*') {
            result *= num;
        } else {
            if (fabs(num) < 1e-4)
                state->error = 1;
            if (state->error)
                break;

            if (state->float_mode) {
                result /= num;
            } else {
                result = trunc(result / num);
            }
        }
    }
    return result;
}

static double parse_add_subt(CalculatorState* state)
{
    if (state->error)
        return 0;
    double result = parse_mult_div(state);

    while (!state->error && (state->current_char == '+' || state->current_char == '-')) {
        char op = state->current_char;
        get_next_char(state);
        double num = parse_mult_div(state);

        op == '+' ? (result += num) : (result -= num);
    }
    return result;
}

void init_calculator(CalculatorState* state)
{
    memset(state, 0, sizeof(CalculatorState));
}

double calculate_expression(CalculatorState* state, const char* input)
{
    FILE* tmp = NULL;
    if (input) {
        tmp = fopen("input.txt", "w+");
        fputs(input, tmp);
        rewind(tmp);
        stdin = tmp;
    }

    get_next_char(state);
    double result = parse_add_subt(state);

    if (!state->error && state->current_char != EOF && state->current_char != '\n') {
        state->error = 1;
    }

    if (input && tmp) {
        fclose(tmp);
        remove("input.txt");
    }

    return result;
}
