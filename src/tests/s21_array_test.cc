#include <gtest/gtest.h>

#include "s21_containersplus.h"

TEST(ArrayTest, DefaultConstructor) {
  s21::array<int> arr;
  EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, InitializerListConstructor) {
  s21::array<int> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.size(), 5);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[4], 5);
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<int> arr1 = {1, 2, 3};
  s21::array<int> arr2(arr1);
  EXPECT_EQ(arr2.size(), 3);
  EXPECT_EQ(arr2[1], 2);
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<int> arr1 = {1, 2, 3};
  s21::array<int> arr2(std::move(arr1));
  EXPECT_EQ(arr2.size(), 3);
  EXPECT_EQ(arr1.size(), 0);  // arr1 should be empty after move
}

TEST(ArrayTest, CopyAssignmentOperator) {
  s21::array<int> arr1 = {1, 2, 3};
  s21::array<int> arr2;
  arr2 = arr1;  // Используем оператор присваивания копированием
  EXPECT_EQ(arr2.size(), 3);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(ArrayTest, MoveAssignmentOperator) {
  s21::array<int> arr1 = {1, 2, 3};
  s21::array<int> arr2;
  arr2 = std::move(arr1);  // Используем оператор присваивания перемещением
  EXPECT_EQ(arr2.size(), 3);
  EXPECT_EQ(arr1.size(), 0);  // arr1 должен быть пустым после перемещения
}
