#include <gtest/gtest.h>

#include <array>

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

TEST(ArrayTest, MaxSize) {
  s21::array<int, 5> arr;
  std::array<int, 5> std_arr;
  EXPECT_EQ(arr.max_size(), std_arr.max_size());
}

TEST(ArrayTest, Empty) {
  s21::array<int, 0> arr;
  EXPECT_TRUE(arr.empty());
  s21::array<int, 3> arr_2 = {1, 2, 3};
  EXPECT_FALSE(arr_2.empty());
}

TEST(ArrayTest, Size) {
  s21::array<int, 5> arr = {1, 2, 3};
  EXPECT_EQ(arr.size(), 5);
}

TEST(ArrayTest, Fill) {
  s21::array<int, 5> arr;
  arr.fill(10);
  EXPECT_EQ(arr.at(0), 10);
  EXPECT_EQ(arr.at(1), 10);
  EXPECT_EQ(arr.at(2), 10);
  EXPECT_EQ(arr.at(3), 10);
  EXPECT_EQ(arr.at(4), 10);

  arr.fill(20);
  EXPECT_EQ(arr.at(0), 20);
  EXPECT_EQ(arr.at(1), 20);
  EXPECT_EQ(arr.at(2), 20);
  EXPECT_EQ(arr.at(3), 20);
  EXPECT_EQ(arr.at(4), 20);
}

TEST(ArrayTest, DifferentTypes) {
  s21::array<int, 3> arr_int = {1, 2, 3};
  EXPECT_EQ(arr_int.size(), 3);
  EXPECT_EQ(arr_int[0], 1);
  EXPECT_EQ(arr_int[2], 3);

  s21::array<double, 3> arr_double = {1.1, 2.2, 3.3};
  EXPECT_DOUBLE_EQ(arr_double[0], 1.1);
  EXPECT_DOUBLE_EQ(arr_double[1], 2.2);
  EXPECT_DOUBLE_EQ(arr_double[2], 3.3);

  s21::array<char, 4> arr_char = {'a', 'b', 'c', 'd'};
  EXPECT_EQ(arr_char[0], 'a');
  EXPECT_EQ(arr_char[3], 'd');

  s21::array<std::string, 3> arr_string = {"Hello", "world", "!"};
  EXPECT_EQ(arr_string[0], "Hello");
  EXPECT_EQ(arr_string[1], "world");
  EXPECT_EQ(arr_string[2], "!");

  s21::array<bool, 2> arr_bool = {true, false};
  EXPECT_TRUE(arr_bool[0]);
  EXPECT_FALSE(arr_bool[1]);
}

TEST(ArrayTest, SwapDifferentTypes) {
  s21::array<int, 3> arr_int1 = {1, 2, 3};
  s21::array<int, 3> arr_int2 = {4, 5, 6};
  arr_int1.swap(arr_int2);
  EXPECT_EQ(arr_int1[0], 4);
  EXPECT_EQ(arr_int2[0], 1);

  s21::array<double, 2> arr_double1 = {1.1, 2.2};
  s21::array<double, 2> arr_double2 = {3.3, 4.4};
  arr_double1.swap(arr_double2);
  EXPECT_DOUBLE_EQ(arr_double1[0], 3.3);
  EXPECT_DOUBLE_EQ(arr_double2[0], 1.1);

  s21::array<std::string, 2> arr_string1 = {"Hello", "world"};
  s21::array<std::string, 2> arr_string2 = {"Goodbye", "planet"};
  arr_string1.swap(arr_string2);
  EXPECT_EQ(arr_string1[0], "Goodbye");
  EXPECT_EQ(arr_string2[0], "Hello");
}
