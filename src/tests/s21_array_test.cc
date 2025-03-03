#include <gtest/gtest.h>

#include "s21_containersplus.h"

TEST(ArrayTest, DefaultConstructor) {
  s21::array<int, 10> arr;
  EXPECT_EQ(arr.size(), 10);
}

TEST(ArrayTest, InitializerListConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.size(), 5);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[4], 5);
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2(arr1);
  EXPECT_EQ(arr2.size(), 3);
  EXPECT_EQ(arr2[1], 2);
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2(std::move(arr1));
  EXPECT_EQ(arr2.size(), 3);
}

TEST(ArrayTest, CopyAssignmentOperator) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2;
  arr2 = arr1;  // Use assignment operator for copying
  EXPECT_EQ(arr2.size(), 3);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(ArrayTest, MoveAssignmentOperator) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2;
  arr2 = std::move(arr1);
  EXPECT_EQ(arr2.size(), 3);
}

TEST(ArrayTest, Front) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.front(), 1);
}

TEST(ArrayTest, Back) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.back(), 5);
}

TEST(ArrayTest, Data) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int* data = arr.data();
  EXPECT_EQ(data[0], 1);
  EXPECT_EQ(data[4], 5);
}

TEST(ArrayTest, At) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.at(0), 1);
  EXPECT_EQ(arr.at(4), 5);
  EXPECT_THROW(arr.at(5), std::out_of_range);
}

TEST(ArrayTest, Begin) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(*arr.begin(), 1);
}

TEST(ArrayTest, End) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(*(arr.end() - 1), 5);
}
