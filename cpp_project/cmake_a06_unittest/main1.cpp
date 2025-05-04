#include <gtest/gtest.h>

int add(int a, int b) {
    return a + b;
}

TEST(MathTests1, AddPositive) {
EXPECT_EQ(add(2, 3), 5);
}

TEST(MathTests2, AddNegative) {
EXPECT_EQ(add(-2, -3), -5);
}
