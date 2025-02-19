#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* input;
char current_value;

int sum_dif(); //обрабатывает сложение и вычитание(+, -)
int mult_diff(); //обрабатывает умножение и деление(*, / )
int number(); //получает число или выражение в скобках

void next() {
    do {
        current_value = *input++;
    } while (isspace(current_value));
}

int sum_dif() {
    int result = mult_diff();
    while (current_value == '+' || current_value == '-') {
        if (current_value == '+') {
            next();
            result += mult_diff();
        }
        else {
            next();
            result -= mult_diff();
        }
    }
    return result;
}

int mult_diff() {
    int result = number();
    while (current_value == '*' || current_value == '/') {
        if (current_value == '*') {
            next();
            result *= number();
        }
        else {
            next();
            int div = number();
            result /= div;
        }
    }
    return result;
}

int number() {
    int result = 0;
    if (current_value == '(') {
        next();
        result = sum_dif();
        next();
    }
    else {
        result = strtol(input - 1, &input, 10);
        current_value = *input;
        next();
    }
    return result;
}

int main() {
    char buffer[1024];
    fgets(buffer, sizeof(buffer), stdin);
    input = buffer;
    next();
    int result = sum_dif();
    printf("%d\n", result);
    return 0;
}

