#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h> // Для преобразования
#include <math.h> // Для проверки диапазона чисел с плавающей точкой

#define MIN_VALUE -2000000000
#define MAX_VALUE 2000000000

// Определения глобальных переменных
char *input;
char current_value;
int float_mode = 0;

float sum_dif();   // обрабатывает сложение и вычитание(+, -)
float mult_diff(); // обрабатывает умножение и деление(*, /)
float number();    // получает число или выражение в скобках

int is_valid_char(char c)
{
    return isdigit(c) || c == '(' || c == ')' || c == '*' || c == '+' || c == '-' || c == '/' || isspace(c);
}

int is_valid_expression(const char *str)
{
    int balance = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!is_valid_char(str[i])) {
            return 0;
        }
        if (str[i] == '(') {
            balance++;
        } else if (str[i] == ')') {
            balance--;
            if (balance < 0) {
                return 0;
            }
        }
    }
    return balance == 0;
}

void next()
{
    do {
        current_value = *input++;
        if (current_value == '\0') {
            break;
        }
    } while (isspace(current_value));
}

void validate_number(double value)
{
    if (value < MIN_VALUE || value > MAX_VALUE) {
        fprintf(stderr, "Error: Value out of range (%d to %d).\n", MIN_VALUE, MAX_VALUE);
        exit(1);
    }
}

float sum_dif()
{
    float result = mult_diff();
    while (current_value == '+' || current_value == '-') {
        if (current_value == '+') {
            next();
            result += mult_diff();
        } else {
            next();
            result -= mult_diff();
        }
    }
    return result;
}

float mult_diff()
{
    float result = number();
    while (current_value == '*' || current_value == '/') {
        if (current_value == '*') {
            next();
            result *= number();
        } else {
            next();
            float div = number();
            if (div == 0) {
                fprintf(stderr, "Division by zero is forbidden.\n");
                exit(1);
            }
            if (div < 1e-4) {
                fprintf(stderr, "Division by a number less than 1e-4 is forbidden.\n");
                exit(1);
            }
            result /= div;
        }
    }
    return result;
}

float number() 
{
    float result = 0.0f;

    if (current_value == '(') {
        next();
        result = sum_dif();
        if (current_value != ')') {
            fprintf(stderr, "Invalid expression: missing closing parenthesis.\n");
            exit(1);
        }
        next();
    } else if (isdigit(current_value) || current_value == '.') {
        char *endptr;
        errno = 0; // Сбрасываем errno перед вызовом strtod
        double value = strtod(input - 1, &endptr);
        if (errno == ERANGE || value < MIN_VALUE || value > MAX_VALUE) {
            fprintf(stderr, "Error: Value out of range (%d to %d).\n", MIN_VALUE, MAX_VALUE);
            exit(1);
        }
        result = (float)value;
        input = endptr;
        current_value = *input;
        next();
    } else {
        fprintf(stderr, "Invalid expression: unexpected character '%c'.\n", current_value);
        exit(1);
    }
    
    return result;
}

#ifndef GTEST
int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "--float") == 0) {
        float_mode = 1;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (!is_valid_expression(buffer)) {
            fprintf(stderr, "Invalid characters or unbalanced parentheses in the expression.\n");
            return 1;
        }

        input = buffer;
        next();

        float result = sum_dif();

        if (float_mode) {
            printf("%.4f\n", result);
        } else {
            printf("%d\n", (int)result);
        }
    }

    return 0;
}
#endif
