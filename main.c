#include <stdio.h>
#include <ctype.h>

int current_char;

void get_next_char() {
    do {
        current_char = getchar();
    } while (current_char == ' ');
}

int parse_num();
int parse_mult_div();
int parse_add_subt();

int parse_num() {
    int result;
    if (current_char == '(') {
        get_next_char();
        result = parse_add_subt();
        if (current_char == ')') {
            get_next_char();
        }
    } else if (isdigit(current_char)) {
        result = 0;
        while (isdigit(current_char)) {
            result = result * 10 + (current_char - '0');
            get_next_char();
        }
    }
    return result;
}

int parse_mult_div() {
    int result = parse_num();
    while (current_char == '*' || current_char == '/') {
        char operator = current_char;
        get_next_char();
        int num = parse_num();
        if (operator == '*') {
            result *= num;
        } else {
            result /= num;
        }
    }
    return result;
}

int parse_add_subt() {
    int result = parse_mult_div();
    while (current_char == '+' || current_char == '-') {
        char operator = current_char;
        get_next_char();
        int symb = parse_mult_div();
        if (operator == '+') {
            result += symb;
        } else {
            result -= symb;
        }
    }
    return result;
}

int main() {
    get_next_char();
    int result = parse_add_subt();
    printf("%d\n", result);
    return 0;
}
