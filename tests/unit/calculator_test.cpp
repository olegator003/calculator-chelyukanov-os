#include <gtest/gtest.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Включаем заголовочный файл с функциями калькулятора
extern "C" {
float sum_dif();
float mult_diff();
float number();
void next();
int is_valid_expression(const char *str); // Добавляем объявление функции
extern char *input;
extern char current_value;
extern int float_mode;
}

void next();

// Тесты для функции is_valid_expression
TEST(ExpressionValidationTest, ValidExpression) {
    EXPECT_TRUE(is_valid_expression("2 + 3 * (4 - 1)"));
    EXPECT_TRUE(is_valid_expression("(2 + 3) * 4"));
}

TEST(ExpressionValidationTest, InvalidExpression) {
    EXPECT_FALSE(is_valid_expression("2 + 3 * (4 - 1"));
    EXPECT_FALSE(is_valid_expression("2 + 3 * 4)"));
    EXPECT_FALSE(is_valid_expression("2 + 3 * a"));
}

// Тесты для функции number
TEST(NumberTest, SimpleNumber) {
    input = (char*)"123";
    next();
    EXPECT_FLOAT_EQ(number(), 123.0f);
}

TEST(NumberTest, FloatingPointNumber) {
    input = (char*)"12.34";
    next();
    EXPECT_FLOAT_EQ(number(), 12.34f);
}

TEST(NumberTest, ExpressionInParentheses) {
    input = (char*)"(2 + 3)";
    next();
    EXPECT_FLOAT_EQ(sum_dif(), 5.0f);
}

// Тесты для функции mult_diff
TEST(MultDiffTest, Multiplication) {
    input = (char*)"2 * 3";
    next();
    EXPECT_FLOAT_EQ(mult_diff(), 6.0f);
}

TEST(MultDiffTest, Division) {
    input = (char*)"6 / 2";
    next();
    EXPECT_FLOAT_EQ(mult_diff(), 3.0f);
}

TEST(MultDiffTest, DivisionBySmallNumber) {
    input = (char*)"1 / 0.0001";
    next();
    EXPECT_EXIT(mult_diff(), ::testing::ExitedWithCode(1), "Division by a number less than 1e-4 is forbidden.");
}

// Тесты для функции sum_dif
TEST(SumDifTest, Addition) {
    input = (char*)"2 + 3";
    next();
    EXPECT_FLOAT_EQ(sum_dif(), 5.0f);
}

TEST(SumDifTest, Subtraction) {
    input = (char*)"5 - 3";
    next();
    EXPECT_FLOAT_EQ(sum_dif(), 2.0f);
}

TEST(SumDifTest, MixedOperations) {
    input = (char*)"2 + 3 * 4 - 1";
    next();
    EXPECT_FLOAT_EQ(sum_dif(), 13.0f);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

