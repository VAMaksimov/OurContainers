#include <gtest/gtest.h>

#include "../src/s21_containers.h"
using namespace s21;

TEST(StackTest, PrintStack) {
  double ar[]{1.1, 2, 3, 8.9, 4.005, 5.666, 6, -5, 7.000001, 8, 9, 999};
  Stack<double> my_stack(ar);
  my_stack.PrintContainer();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}