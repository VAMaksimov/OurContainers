#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <iostream>

#include "./deque.h"

TEST(Constructors, StandartConstructor) {
  deque<int> deque1;
  deque<char> deque2;
  deque<float> deque3;
  ASSERT_TRUE(deque1.size() == 0);
  ASSERT_TRUE(deque2.size() == 0);
  ASSERT_TRUE(deque3.size() == 0);
}

TEST(Constructors, SizeConstructor) {
  deque<int> deque1(4);
  deque<char> deque2(5);
  deque<float> deque3(30);
  ASSERT_TRUE(deque1.size() == 4);
  ASSERT_TRUE(deque2.size() == 5);
  ASSERT_TRUE(deque3.size() == 30);
}

TEST(Constructors, ElementConstructor) {
  deque<int> deque1 = {1, 2, 4, 6, 7};
  deque<char> deque2 = {'a', 'a', 'a', 'a', 'a'};
  deque<float> deque3 = {1.4, 1.4, 2.2, 4.2, 3.1111};
  ASSERT_TRUE(deque1.size() == 4);
  ASSERT_TRUE(deque2.size() == 5);
  ASSERT_TRUE(deque3.size() == 30);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
  
  