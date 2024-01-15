#include<gtest/gtest.h>
#include"calculator.cpp"

TEST(CalculatorTest, Add){
    Calculator<int> calculator;
    EXPECT_EQ(calculator.add(3, 4), 7);
    EXPECT_EQ(calculator.add(-1, 1), 0);
    EXPECT_EQ(calculator.add(0, 0), 0);
}
TEST(CalculatorTest, Multiply){
    Calculator<int> calculator;
    EXPECT_EQ(calculator.multiply(2, 4), 8);
    EXPECT_EQ(calculator.multiply(-1, 1), -1);
    EXPECT_EQ(calculator.multiply(0, 0), 0);
}
TEST(CalculatorTest, MixedOperations){
    Calculator<int> calculator;
    EXPECT_EQ(calculator.add(2, calculator.multiply(3, 4)), 14);
    EXPECT_EQ(calculator.multiply(calculator.add(1, 2), 3), 9);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

