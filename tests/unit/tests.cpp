#include <gtest/gtest.h>
#include "calculator.h"

extern "C" {
void init_calculator(CalculatorState* state);
double calculate_expression(CalculatorState* state, const char* input);
}

class CalculatorTest : public ::testing::Test {
protected:
    CalculatorState state;

    void SetUp() override
    {
        init_calculator(&state);
    }
};

TEST_F(CalculatorTest, BasicAddition)
{
    state.float_mode = 0;
    double result = calculate_expression(&state, "2+3");
    EXPECT_NEAR(result, 5, 1e-4);
    EXPECT_EQ(state.error, 0);
}

TEST_F(CalculatorTest, DivisionIntegerMode)
{
    state.float_mode = 0;
    double result = calculate_expression(&state, "10/3");
    EXPECT_NEAR(result, 3, 1e-4);
    EXPECT_EQ(state.error, 0);
}

TEST_F(CalculatorTest, DivisionFloatMode)
{
    state.float_mode = 1;
    double result = calculate_expression(&state, "10/3");
    EXPECT_NEAR(result, 3.3333, 1e-4);
    EXPECT_EQ(state.error, 0);
}

TEST_F(CalculatorTest, Parentheses)
{
    state.float_mode = 0;
    double result = calculate_expression(&state, "(2+3)*4");
    EXPECT_EQ(state.error, 0) << "Error code: " << state.error;
    EXPECT_NEAR(result, 20, 1e-4);
}

TEST_F(CalculatorTest, InvalidCharacter)
{
    state.float_mode = 0;
    calculate_expression(&state, "2+a");
    EXPECT_EQ(state.error, 1);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
