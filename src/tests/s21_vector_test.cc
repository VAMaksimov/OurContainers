#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "s21_containers.h"

TEST(VectorTest, DefaultConstructor) {
  s21::vector<int> s21_vec_int;
  s21::vector<double> s21_vec_double;
  s21::vector<std::string> s21_vec_string;

  EXPECT_EQ(s21_vec_int.size(), 0U);
  EXPECT_EQ(s21_vec_int.capacity(), 0U);

  EXPECT_EQ(s21_vec_double.size(), 0U);
  EXPECT_EQ(s21_vec_double.capacity(), 0U);

  EXPECT_EQ(s21_vec_string.size(), 0U);
  EXPECT_EQ(s21_vec_string.capacity(), 0U);
}

TEST(VectorTest, SizeConstructor) {
  s21::vector<int> s21_vec_int(5);
  s21::vector<double> s21_vec_double(5);
  s21::vector<std::string> s21_vec_string(5);

  EXPECT_EQ(s21_vec_int.size(), 5U);
  EXPECT_EQ(s21_vec_int.capacity(), 5U);
  EXPECT_NE(&s21_vec_int[0], nullptr);

  EXPECT_EQ(s21_vec_double.size(), 5U);
  EXPECT_EQ(s21_vec_double.capacity(), 5U);
  EXPECT_NE(&s21_vec_double[0], nullptr);

  EXPECT_EQ(s21_vec_string.size(), 5U);
  EXPECT_EQ(s21_vec_string.capacity(), 5U);
  EXPECT_NE(&s21_vec_string[0], nullptr);
}

TEST(VectorTest, InitializerListConstructor) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.size(), 4U);
  EXPECT_EQ(s21_vec_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_int[0], 1);
  EXPECT_EQ(s21_vec_int[1], 4);
  EXPECT_EQ(s21_vec_int[2], 8);
  EXPECT_EQ(s21_vec_int[3], 9);

  EXPECT_EQ(s21_vec_double.size(), 4U);
  EXPECT_EQ(s21_vec_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_double[0], 1.4);
  EXPECT_EQ(s21_vec_double[1], 4.8);
  EXPECT_EQ(s21_vec_double[2], 8.9);
  EXPECT_EQ(s21_vec_double[3], 9.1);

  EXPECT_EQ(s21_vec_string.size(), 4U);
  EXPECT_EQ(s21_vec_string.capacity(), 4U);
  EXPECT_EQ(s21_vec_string[0], "Hello");
  EXPECT_EQ(s21_vec_string[1], ",");
  EXPECT_EQ(s21_vec_string[2], "world");
  EXPECT_EQ(s21_vec_string[3], "!");
}

TEST(VectorTest, CopyConstructor) {
  s21::vector<int> s21_vec_ref_int{1, 4, 8, 9};
  s21::vector<int> s21_vec_res_int(s21_vec_ref_int);

  s21::vector<double> s21_vec_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<double> s21_vec_res_double(s21_vec_ref_double);

  s21::vector<std::string> s21_vec_ref_string{"Hello", ",", "world", "!"};
  s21::vector<std::string> s21_vec_res_string(s21_vec_ref_string);

  EXPECT_EQ(s21_vec_ref_int.size(), s21_vec_res_int.size());
  EXPECT_EQ(s21_vec_ref_int.capacity(), s21_vec_res_int.capacity());
  EXPECT_EQ(s21_vec_ref_int[0], s21_vec_res_int[0]);
  EXPECT_EQ(s21_vec_ref_int[1], s21_vec_res_int[1]);
  EXPECT_EQ(s21_vec_ref_int[2], s21_vec_res_int[2]);
  EXPECT_EQ(s21_vec_ref_int[3], s21_vec_res_int[3]);

  EXPECT_EQ(s21_vec_ref_double.size(), s21_vec_res_double.size());
  EXPECT_EQ(s21_vec_ref_double.capacity(), s21_vec_res_double.capacity());
  EXPECT_EQ(s21_vec_ref_double[0], s21_vec_res_double[0]);
  EXPECT_EQ(s21_vec_ref_double[1], s21_vec_res_double[1]);
  EXPECT_EQ(s21_vec_ref_double[2], s21_vec_res_double[2]);
  EXPECT_EQ(s21_vec_ref_double[3], s21_vec_res_double[3]);

  EXPECT_EQ(s21_vec_ref_string.size(), s21_vec_res_string.size());
  EXPECT_EQ(s21_vec_ref_string.capacity(), s21_vec_res_string.capacity());
  EXPECT_EQ(s21_vec_ref_string[0], s21_vec_res_string[0]);
  EXPECT_EQ(s21_vec_ref_string[1], s21_vec_res_string[1]);
  EXPECT_EQ(s21_vec_ref_string[2], s21_vec_res_string[2]);
  EXPECT_EQ(s21_vec_ref_string[3], s21_vec_res_string[3]);
}

TEST(VectorTest, MoveConstructor) {
  s21::vector<int> s21_vec_ref_int{1, 4, 8, 9};
  s21::vector<int> s21_vec_res_int = std::move(s21_vec_ref_int);

  EXPECT_EQ(s21_vec_res_int.size(), 4U);
  EXPECT_EQ(s21_vec_res_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_int[0], 1);
  EXPECT_EQ(s21_vec_res_int[1], 4);
  EXPECT_EQ(s21_vec_res_int[2], 8);
  EXPECT_EQ(s21_vec_res_int[3], 9);

  s21::vector<int> empty_vector_int;
  EXPECT_EQ(s21_vec_ref_int.size(), empty_vector_int.size());
  EXPECT_EQ(s21_vec_ref_int.capacity(), empty_vector_int.capacity());

  s21::vector<double> s21_vec_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<double> s21_vec_res_double = std::move(s21_vec_ref_double);

  EXPECT_EQ(s21_vec_res_double.size(), 4U);
  EXPECT_EQ(s21_vec_res_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_double[0], 1.4);
  EXPECT_EQ(s21_vec_res_double[1], 4.8);
  EXPECT_EQ(s21_vec_res_double[2], 8.9);
  EXPECT_EQ(s21_vec_res_double[3], 9.1);

  s21::vector<double> empty_vector_double;
  EXPECT_EQ(s21_vec_ref_double.size(), empty_vector_double.size());
  EXPECT_EQ(s21_vec_ref_double.capacity(), empty_vector_double.capacity());

  s21::vector<std::string> s21_vec_ref_string{"Hello", ",", "world", "!"};
  s21::vector<std::string> s21_vec_res_string = std::move(s21_vec_ref_string);

  EXPECT_EQ(s21_vec_res_string.size(), 4U);
  EXPECT_EQ(s21_vec_res_string.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_string[0], "Hello");
  EXPECT_EQ(s21_vec_res_string[1], ",");
  EXPECT_EQ(s21_vec_res_string[2], "world");
  EXPECT_EQ(s21_vec_res_string[3], "!");

  s21::vector<std::string> empty_vector_string;
  EXPECT_EQ(s21_vec_ref_string.size(), empty_vector_string.size());
  EXPECT_EQ(s21_vec_ref_string.capacity(), empty_vector_string.capacity());
}

TEST(VectorTest, MoveAssignment) {
  s21::vector<int> s21_vec_ref_int{1, 4, 8, 9};
  s21::vector<int> s21_vec_res_int;
  s21_vec_res_int = std::move(s21_vec_ref_int);

  s21::vector<double> s21_vec_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<double> s21_vec_res_double;
  s21_vec_res_double = std::move(s21_vec_ref_double);

  s21::vector<std::string> s21_vec_ref_string{"Hello", ",", "world", "!"};
  s21::vector<std::string> s21_vec_res_string;
  s21_vec_res_string = std::move(s21_vec_ref_string);

  EXPECT_EQ(s21_vec_ref_int.size(), 0U);
  EXPECT_EQ(s21_vec_ref_int.capacity(), 0U);
  EXPECT_EQ(s21_vec_res_int.size(), 4U);
  EXPECT_EQ(s21_vec_res_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_int[0], 1);
  EXPECT_EQ(s21_vec_res_int[1], 4);
  EXPECT_EQ(s21_vec_res_int[2], 8);
  EXPECT_EQ(s21_vec_res_int[3], 9);

  EXPECT_EQ(s21_vec_ref_double.size(), 0U);
  EXPECT_EQ(s21_vec_ref_double.capacity(), 0U);
  EXPECT_EQ(s21_vec_res_double.size(), 4U);
  EXPECT_EQ(s21_vec_res_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_double[0], 1.4);
  EXPECT_EQ(s21_vec_res_double[1], 4.8);
  EXPECT_EQ(s21_vec_res_double[2], 8.9);
  EXPECT_EQ(s21_vec_res_double[3], 9.1);

  EXPECT_EQ(s21_vec_ref_string.size(), 0U);
  EXPECT_EQ(s21_vec_ref_string.capacity(), 0U);
  EXPECT_EQ(s21_vec_res_string.size(), 4U);
  EXPECT_EQ(s21_vec_res_string.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_string[0], "Hello");
  EXPECT_EQ(s21_vec_res_string[1], ",");
  EXPECT_EQ(s21_vec_res_string[2], "world");
  EXPECT_EQ(s21_vec_res_string[3], "!");
}

TEST(VectorTest, At) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.at(0), 1);
  EXPECT_EQ(s21_vec_double.at(0), 1.4);
  EXPECT_EQ(s21_vec_string.at(0), "Hello");
}

TEST(VectorTest, AtOutOfRange) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_THROW(s21_vec_int.at(5), std::out_of_range);
  EXPECT_THROW(s21_vec_double.at(5), std::out_of_range);
  EXPECT_THROW(s21_vec_string.at(5), std::out_of_range);
}

TEST(VectorTest, AtEmptyVector) {
  s21::vector<int> s21_vec_int;
  s21::vector<double> s21_vec_double;
  s21::vector<std::string> s21_vec_string;

  EXPECT_THROW(s21_vec_int.at(5), std::out_of_range);
  EXPECT_THROW(s21_vec_double.at(5), std::out_of_range);
  EXPECT_THROW(s21_vec_string.at(5), std::out_of_range);
}

TEST(VectorTest, OperatorBrackets) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int[3], 9);
  EXPECT_EQ(s21_vec_double[0], 1.4);
  EXPECT_EQ(s21_vec_string[0], "Hello");
}

TEST(VectorTest, Front) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.front(), 1);
  EXPECT_EQ(s21_vec_double.front(), 1.4);
  EXPECT_EQ(s21_vec_string.front(), "Hello");
}

TEST(VectorTest, Back) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.back(), 9);
  EXPECT_EQ(s21_vec_double.back(), 9.1);
  EXPECT_EQ(s21_vec_string.back(), "!");
}

TEST(VectorTest, Data) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.data(), &s21_vec_int[0]);
  EXPECT_EQ(s21_vec_double.data(), &s21_vec_double[0]);
  EXPECT_EQ(s21_vec_string.data(), &s21_vec_string[0]);
}

TEST(VectorTest, Begin) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.begin(), &s21_vec_int[0]);
  EXPECT_EQ(s21_vec_double.begin(), &s21_vec_double[0]);
  EXPECT_EQ(s21_vec_string.begin(), &s21_vec_string[0]);
}

TEST(VectorTest, End) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.end(), &s21_vec_int[0] + 4);
  EXPECT_EQ(s21_vec_double.end(), &s21_vec_double[0] + 4);
  EXPECT_EQ(s21_vec_string.end(), &s21_vec_string[0] + 4);
}

TEST(VectorTest, Empty) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.empty(), 0);
  EXPECT_EQ(s21_vec_double.empty(), 0);
  EXPECT_EQ(s21_vec_string.empty(), 0);
}

TEST(VectorTest, EmptyTrue) {
  s21::vector<int> s21_vec_int{};
  s21::vector<double> s21_vec_double{};
  s21::vector<std::string> s21_vec_string{};

  EXPECT_EQ(s21_vec_int.empty(), 1);
  EXPECT_EQ(s21_vec_double.empty(), 1);
  EXPECT_EQ(s21_vec_string.empty(), 1);
}

TEST(VectorTest, Size) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.size(), 4U);
  EXPECT_EQ(s21_vec_double.size(), 4U);
  EXPECT_EQ(s21_vec_string.size(), 4U);
}

TEST(VectorTest, SizeEmpty) {
  s21::vector<int> s21_vec_int{};
  s21::vector<double> s21_vec_double{};
  s21::vector<std::string> s21_vec_string{};

  EXPECT_EQ(s21_vec_int.size(), 0U);
  EXPECT_EQ(s21_vec_double.size(), 0U);
  EXPECT_EQ(s21_vec_string.size(), 0U);
}

TEST(VectorTest, MaxSize) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  std::vector<int> std_vec_int{1, 4, 8, 9};

  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  std::vector<double> std_vec_double{1.4, 4.8, 8.9, 9.1};

  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};
  std::vector<std::string> std_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.max_size(), std_vec_int.max_size());
  EXPECT_EQ(s21_vec_double.max_size(), std_vec_double.max_size());
  EXPECT_EQ(s21_vec_string.max_size(), std_vec_string.max_size());
}

TEST(VectorTest, Reserve) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.reserve(20);
  s21_vec_double.reserve(20);
  s21_vec_string.reserve(20);

  EXPECT_EQ(s21_vec_int.capacity(), 20U);
  EXPECT_EQ(s21_vec_double.capacity(), 20U);
  EXPECT_EQ(s21_vec_string.capacity(), 20U);
}

TEST(VectorTest, ReserveSmaller) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.reserve(2);
  s21_vec_double.reserve(2);
  s21_vec_string.reserve(2);

  EXPECT_EQ(s21_vec_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_string.capacity(), 4U);
}

TEST(VectorTest, Capacity) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_string.capacity(), 4U);
}

TEST(VectorTest, CapacityEmpty) {
  s21::vector<int> s21_vec_int{};
  s21::vector<double> s21_vec_double{};
  s21::vector<std::string> s21_vec_string{};

  EXPECT_EQ(s21_vec_int.capacity(), 0U);
  EXPECT_EQ(s21_vec_double.capacity(), 0U);
  EXPECT_EQ(s21_vec_string.capacity(), 0U);
}

TEST(VectorTest, ShrinkToFit) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.reserve(20);
  s21_vec_double.reserve(20);
  s21_vec_string.reserve(20);

  s21_vec_int.shrink_to_fit();
  s21_vec_double.shrink_to_fit();
  s21_vec_string.shrink_to_fit();

  EXPECT_EQ(s21_vec_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_string.capacity(), 4U);
}

TEST(VectorTest, ShrinkToFitNoEffect) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.shrink_to_fit();
  s21_vec_double.shrink_to_fit();
  s21_vec_string.shrink_to_fit();

  EXPECT_EQ(s21_vec_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_string.capacity(), 4U);
}

TEST(VectorTest, Clear) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.clear();
  s21_vec_double.clear();
  s21_vec_string.clear();

  EXPECT_EQ(s21_vec_int.size(), 0U);
  EXPECT_EQ(s21_vec_int.capacity(), 0U);
  EXPECT_EQ(s21_vec_double.size(), 0U);
  EXPECT_EQ(s21_vec_double.capacity(), 0U);
  EXPECT_EQ(s21_vec_string.size(), 0U);
  EXPECT_EQ(s21_vec_string.capacity(), 0U);
}

TEST(VectorTest, Insert) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "", "!"};

  auto pos_int = s21_vec_int.begin() + 2;
  auto pos_double = s21_vec_double.begin() + 2;
  auto pos_string = s21_vec_string.begin() + 2;

  s21_vec_int.insert(pos_int, 2);
  s21_vec_double.insert(pos_double, 2.0);
  s21_vec_string.insert(pos_string, "world");

  EXPECT_EQ(s21_vec_int[2], 2);
  EXPECT_EQ(s21_vec_double[2], 2.0);
  EXPECT_EQ(s21_vec_string[2], "world");
}

TEST(VectorTest, InsertBegin) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "", "!"};

  auto pos_int = s21_vec_int.begin();
  auto pos_double = s21_vec_double.begin();
  auto pos_string = s21_vec_string.begin();

  s21_vec_int.insert(pos_int, 2);
  s21_vec_double.insert(pos_double, 2.0);
  s21_vec_string.insert(pos_string, "world");

  EXPECT_EQ(s21_vec_int[0], 2);
  EXPECT_EQ(s21_vec_double[0], 2.0);
  EXPECT_EQ(s21_vec_string[0], "world");
}

TEST(VectorTest, InsertEnd) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "", "!"};

  auto pos_int = s21_vec_int.end();
  auto pos_double = s21_vec_double.end();
  auto pos_string = s21_vec_string.end();

  s21_vec_int.insert(pos_int, 2);
  s21_vec_double.insert(pos_double, 2.0);
  s21_vec_string.insert(pos_string, "world");

  EXPECT_EQ(s21_vec_int[4], 2);
  EXPECT_EQ(s21_vec_double[4], 2.0);
  EXPECT_EQ(s21_vec_string[4], "world");
}

TEST(VectorTest, Erase) {
  s21::vector<int> s21_vec_int{1, 4, 1, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 1.0, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "", "world", "!"};

  auto pos_int = s21_vec_int.begin() + 2;
  auto pos_double = s21_vec_double.begin() + 2;
  auto pos_string = s21_vec_string.begin() + 2;

  s21_vec_int.erase(pos_int);
  s21_vec_double.erase(pos_double);
  s21_vec_string.erase(pos_string);

  EXPECT_EQ(s21_vec_int[2], 8);
  EXPECT_EQ(s21_vec_double[2], 8.9);
  EXPECT_EQ(s21_vec_string[2], "world");
}

TEST(VectorTest, EraseBegin) {
  s21::vector<int> s21_vec_int{1, 1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.0, 1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"", "Hello", ",", "world", "!"};

  auto pos_int = s21_vec_int.begin();
  auto pos_double = s21_vec_double.begin();
  auto pos_string = s21_vec_string.begin();

  s21_vec_int.erase(pos_int);
  s21_vec_double.erase(pos_double);
  s21_vec_string.erase(pos_string);

  EXPECT_EQ(s21_vec_int[0], 1);
  EXPECT_EQ(s21_vec_double[0], 1.4);
  EXPECT_EQ(s21_vec_string[0], "Hello");
}

TEST(VectorTest, PushBack) {
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_double.push_back(10.0);
  s21_vec_string.push_back("!!");

  EXPECT_EQ(*(s21_vec_double.end() - 1), 10.0);
  EXPECT_EQ(*(s21_vec_string.end() - 1), "!!");
}

TEST(VectorTest, PushBackReserved) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.reserve(20);
  s21_vec_double.reserve(20);
  s21_vec_string.reserve(20);

  s21_vec_int.push_back(10);
  s21_vec_double.push_back(10.0);
  s21_vec_string.push_back("!!");

  EXPECT_EQ(*(s21_vec_int.end() - 1), 10);
  EXPECT_EQ(*(s21_vec_double.end() - 1), 10.0);
  EXPECT_EQ(*(s21_vec_string.end() - 1), "!!");
}

TEST(VectorTest, PopBack) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.pop_back();
  s21_vec_double.pop_back();
  s21_vec_string.pop_back();

  EXPECT_EQ(s21_vec_int.size(), 3U);
  EXPECT_EQ(s21_vec_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_double.size(), 3U);
  EXPECT_EQ(s21_vec_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_string.size(), 3U);
  EXPECT_EQ(s21_vec_string.capacity(), 4U);
}

TEST(VectorTest, Swap) {
  s21::vector<int> s21_vec_ref_int{1, 4, 8, 9};
  s21::vector<int> s21_vec_res_int{0, 0, 0};

  s21::vector<double> s21_vec_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<double> s21_vec_res_double{0.0, 0.0, 0.0};

  s21::vector<std::string> s21_vec_ref_string{"Hello", ",", "world", "!"};
  s21::vector<std::string> s21_vec_res_string{"", "", ""};

  s21_vec_ref_int.swap(s21_vec_res_int);
  s21_vec_ref_double.swap(s21_vec_res_double);
  s21_vec_ref_string.swap(s21_vec_res_string);

  EXPECT_EQ(s21_vec_res_int.size(), 4U);
  EXPECT_EQ(s21_vec_res_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_int[2], 8);

  EXPECT_EQ(s21_vec_res_double.size(), 4U);
  EXPECT_EQ(s21_vec_res_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_double[2], 8.9);

  EXPECT_EQ(s21_vec_res_string.size(), 4U);
  EXPECT_EQ(s21_vec_res_string.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_string[2], "world");
}

TEST(VectorTest, ConstIteratorAccess) {
  s21::vector<int> original{10, 20, 30};
  const auto& vec = original;

  ASSERT_EQ(*vec.cbegin(), 10);
  ASSERT_EQ(*(vec.cend() - 1), 30);

  original.push_back(40);
  ASSERT_EQ(*(vec.cend() - 1), 40);
  ASSERT_EQ(vec.cend() - vec.cbegin(), 4);
}
TEST(VectorTest, ConstFrontBack) {
  const s21::vector<int> s21_vec_int{1, 4, 8, 9};
  const s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  const s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.front(), 1);
  EXPECT_EQ(s21_vec_double.front(), 1.4);
  EXPECT_EQ(s21_vec_string.front(), "Hello");

  EXPECT_EQ(s21_vec_int.back(), 9);
  EXPECT_EQ(s21_vec_double.back(), 9.1);
  EXPECT_EQ(s21_vec_string.back(), "!");
}

TEST(VectorTest, InsertManyFront) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  auto pos_int = s21_vec_int.begin();
  auto pos_double = s21_vec_double.begin();
  auto pos_string = s21_vec_string.begin();

  s21_vec_int.insert_many(pos_int, 10, 20, 30);
  s21_vec_double.insert_many(pos_double, 10.1, 20.2, 30.3);
  s21_vec_string.insert_many(pos_string, "One", "Two", "Three");

  EXPECT_EQ(s21_vec_int.size(), 7U);
  EXPECT_EQ(s21_vec_int[0], 10);
  EXPECT_EQ(s21_vec_int[1], 20);
  EXPECT_EQ(s21_vec_int[2], 30);
  EXPECT_EQ(s21_vec_int[3], 1);

  EXPECT_EQ(s21_vec_double.size(), 7U);
  EXPECT_EQ(s21_vec_double[0], 10.1);
  EXPECT_EQ(s21_vec_double[1], 20.2);
  EXPECT_EQ(s21_vec_double[2], 30.3);
  EXPECT_EQ(s21_vec_double[3], 1.4);

  EXPECT_EQ(s21_vec_string.size(), 7U);
  EXPECT_EQ(s21_vec_string[0], "One");
  EXPECT_EQ(s21_vec_string[1], "Two");
  EXPECT_EQ(s21_vec_string[2], "Three");
  EXPECT_EQ(s21_vec_string[3], "Hello");
}

TEST(VectorTest, InsertManyMiddle) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  auto pos_int = s21_vec_int.begin() + 2;
  auto pos_double = s21_vec_double.begin() + 2;
  auto pos_string = s21_vec_string.begin() + 2;

  auto result_int = s21_vec_int.insert_many(pos_int, 10, 20, 30);
  auto result_double = s21_vec_double.insert_many(pos_double, 10.1, 20.2, 30.3);
  auto result_string =
      s21_vec_string.insert_many(pos_string, "One", "Two", "Three");

  EXPECT_EQ(result_int, s21_vec_int.begin() + 2);
  EXPECT_EQ(result_double, s21_vec_double.begin() + 2);
  EXPECT_EQ(result_string, s21_vec_string.begin() + 2);

  EXPECT_EQ(s21_vec_int.size(), 7U);
  EXPECT_EQ(s21_vec_int[0], 1);
  EXPECT_EQ(s21_vec_int[1], 4);
  EXPECT_EQ(s21_vec_int[2], 10);
  EXPECT_EQ(s21_vec_int[3], 20);
  EXPECT_EQ(s21_vec_int[4], 30);
  EXPECT_EQ(s21_vec_int[5], 8);
  EXPECT_EQ(s21_vec_int[6], 9);

  EXPECT_EQ(s21_vec_double.size(), 7U);
  EXPECT_EQ(s21_vec_double[0], 1.4);
  EXPECT_EQ(s21_vec_double[1], 4.8);
  EXPECT_EQ(s21_vec_double[2], 10.1);
  EXPECT_EQ(s21_vec_double[3], 20.2);
  EXPECT_EQ(s21_vec_double[4], 30.3);
  EXPECT_EQ(s21_vec_double[5], 8.9);
  EXPECT_EQ(s21_vec_double[6], 9.1);

  EXPECT_EQ(s21_vec_string.size(), 7U);
  EXPECT_EQ(s21_vec_string[0], "Hello");
  EXPECT_EQ(s21_vec_string[1], ",");
  EXPECT_EQ(s21_vec_string[2], "One");
  EXPECT_EQ(s21_vec_string[3], "Two");
  EXPECT_EQ(s21_vec_string[4], "Three");
  EXPECT_EQ(s21_vec_string[5], "world");
  EXPECT_EQ(s21_vec_string[6], "!");
}

TEST(VectorTest, InsertManyBack) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.insert_many_back(10, 20, 30);
  s21_vec_double.insert_many_back(10.1, 20.2, 30.3);
  s21_vec_string.insert_many_back("One", "Two", "Three");

  EXPECT_EQ(s21_vec_int.size(), 7U);
  EXPECT_EQ(s21_vec_int[0], 1);
  EXPECT_EQ(s21_vec_int[1], 4);
  EXPECT_EQ(s21_vec_int[2], 8);
  EXPECT_EQ(s21_vec_int[3], 9);
  EXPECT_EQ(s21_vec_int[4], 10);
  EXPECT_EQ(s21_vec_int[5], 20);
  EXPECT_EQ(s21_vec_int[6], 30);

  EXPECT_EQ(s21_vec_double.size(), 7U);
  EXPECT_EQ(s21_vec_double[0], 1.4);
  EXPECT_EQ(s21_vec_double[1], 4.8);
  EXPECT_EQ(s21_vec_double[2], 8.9);
  EXPECT_EQ(s21_vec_double[3], 9.1);
  EXPECT_EQ(s21_vec_double[4], 10.1);
  EXPECT_EQ(s21_vec_double[5], 20.2);
  EXPECT_EQ(s21_vec_double[6], 30.3);

  EXPECT_EQ(s21_vec_string.size(), 7U);
  EXPECT_EQ(s21_vec_string[0], "Hello");
  EXPECT_EQ(s21_vec_string[1], ",");
  EXPECT_EQ(s21_vec_string[2], "world");
  EXPECT_EQ(s21_vec_string[3], "!");
  EXPECT_EQ(s21_vec_string[4], "One");
  EXPECT_EQ(s21_vec_string[5], "Two");
  EXPECT_EQ(s21_vec_string[6], "Three");
}
