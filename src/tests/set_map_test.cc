// 1) Related header
#include "components/s21_set.h"
// 2) C system headers
// 3) C++ standard library headers
#include <map>
#include <set>
// 4) other libraries' headers
#include <gtest/gtest.h>
// 5) project's headers.

template <typename T>
void CompareSets(s21::set<T> &ActualSet, std::set<T> &ExpectedSet) {
  EXPECT_EQ(ExpectedSet.size(), ActualSet.size());

  for (auto it = ActualSet.begin(), it2 = ExpectedSet.begin();
       it != ActualSet.end() && it2 != ExpectedSet.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }

  EXPECT_EQ(ActualSet.empty(), ExpectedSet.empty());
}

// template <typename Key, typename Value>
// void CompareMaps(s21::map<Key, Value> &ActualMap, std::map<Key, Value>
// &ExpectedMap) {
//   EXPECT_EQ(ExpectedMap.size(), ActualMap.size());

//   for (auto it = ActualMap.begin(), it2 = ExpectedMap.begin();
//        it != ActualMap.end() && it2 != ExpectedMap.end(); ++it, ++it2) {
//     EXPECT_EQ(it->first, it2->first);
//     EXPECT_EQ(it->second, it2->second);
//   }

//   EXPECT_EQ(ActualMap.empty(), ExpectedMap.empty());
// }

TEST(SetTest, Iterators) {
  // 10 15 20 25 30 40 50 60 70 80 90
  s21::set<int> ActualSet = {50, 25, 10, 30, 60, 80, 15, 40, 70, 90, 20};

  EXPECT_EQ(ActualSet.end(), nullptr);
  auto it = ActualSet.begin();
  EXPECT_EQ(*it, 10);
  it++;
  EXPECT_EQ(*it, 15);
  it++;
  it++;
  EXPECT_EQ(*it, 25);
  it--;
  EXPECT_EQ(*it, 20);
  for (int i = 2; i < 11; i++) it++;
  EXPECT_EQ(it, ActualSet.end());
}

TEST(SetTest, BaseConstructor) {
  s21::set<int> ActualSet;
  std::set<int> ExpectedSet;

  EXPECT_EQ(ExpectedSet.size(), ActualSet.size());
  EXPECT_EQ(ExpectedSet.empty(), ActualSet.empty());
}

TEST(SetTest, InitListConstructor) {
  s21::set<int> ActualSet = {1, 2, 3, 4, 5};
  std::set<int> ExpectedSet = {1, 2, 3, 4, 5};

  CompareSets(ActualSet, ExpectedSet);
}

TEST(SetTest, CopyConstructor) {
  s21::set<int> ActualSet = {5, 4, 3, 2, 1};
  s21::set<int> CopySet(ActualSet);
  std::set<int> ExpectedSet = {5, 4, 3, 2, 1};

  CompareSets(CopySet, ExpectedSet);
  CompareSets(ActualSet, ExpectedSet);
}

TEST(SetTest, MoveConstructor) {
  s21::set<int> ActualSet = {3, 4, 5, 1, 2};
  s21::set<int> MoveSet(std::move(ActualSet));
  std::set<int> ExpectedSet = {3, 4, 5, 1, 2};

  CompareSets(MoveSet, ExpectedSet);

  EXPECT_EQ(ActualSet.empty(), true);
}

TEST(SetTest, MoveOperator) {
  s21::set<int> ActualSet = {2, 3, 5,   4,  1,  1,   4,  6,
                             3, 7, 132, 13, 23, 543, 23, 52};
  s21::set<int> MoveSet;
  MoveSet = std::move(ActualSet);
  std::set<int> ExpectedSet = {2, 3, 5,   4,  1,  1,   4,  6,
                               3, 7, 132, 13, 23, 543, 23, 52};

  CompareSets(MoveSet, ExpectedSet);

  EXPECT_TRUE(ActualSet.empty());
}

// Destructor test is not needed because destructor is called automatically

TEST(SetTest, Clear) {
  s21::set<char> ActualSet = {'k', 'g', 'f', 'd', 'c', 'b', 'a'};
  std::set<char> ExpectedSet = {'k', 'g', 'f', 'd', 'c', 'b', 'a'};

  ActualSet.clear();
  ExpectedSet.clear();

  EXPECT_TRUE(ActualSet.empty());
  CompareSets(ActualSet, ExpectedSet);
}

TEST(SetTest, Insert) {
  s21::set<int> ActualSet;
  std::set<int> ExpectedSet;

  auto [it1, success1] = ActualSet.insert(42);
  EXPECT_TRUE(success1);
  EXPECT_EQ(*it1, 42);

  ExpectedSet.insert(42);
  auto [it2, success2] = ActualSet.insert(42);
  EXPECT_FALSE(success2);
  EXPECT_EQ(*it2, 42);

  ActualSet.insert(1);
  ActualSet.insert(2);

  ExpectedSet.insert(42);
  ExpectedSet.insert(1);
  ExpectedSet.insert(2);

  CompareSets(ActualSet, ExpectedSet);
}

TEST(SetTest, Erase) {
  s21::set<float> ActualSet = {4.00001, 34.1, 543.1, 7.76543};
  std::set<float> ExpectedSet = {4.00001, 34.1, 543.1, 7.76543};

  // Find and erase element 3
  auto it = ActualSet.find(34.1);
  ActualSet.erase(it);

  ExpectedSet.erase(34.1);

  CompareSets(ActualSet, ExpectedSet);

  EXPECT_FALSE(ActualSet.contains(34.1));

  it = ActualSet.find(4.00001);
  ActualSet.erase(it);
  it = ActualSet.find(7.76543);
  ActualSet.erase(it);

  ExpectedSet.erase(4.00001);
  ExpectedSet.erase(7.76543);

  CompareSets(ActualSet, ExpectedSet);
}

TEST(SetTest, EraseLargeSet) {
  s21::set<int> ActualSet = {50, 25, 75, 10, 35, 60, 80, 15, 40, 70, 90, 20};
  std::set<int> ExpectedSet = {50, 10, 35, 60, 80, 15, 40, 90, 20};

  auto it = ActualSet.find(70);
  ActualSet.erase(it);
  it = ActualSet.find(75);
  ActualSet.erase(it);
  it = ActualSet.find(25);
  ActualSet.erase(it);

  CompareSets(ActualSet, ExpectedSet);
}

TEST(SetTest, Swap) {
  s21::set<int> ActualSet1 = {1, 2, 3};
  s21::set<int> ActualSet2 = {4, 5, 6, 7};

  std::set<int> ExpectedSet1 = {1, 2, 3};
  std::set<int> ExpectedSet2 = {4, 5, 6, 7};

  ActualSet1.swap(ActualSet2);

  CompareSets(ActualSet1, ExpectedSet2);
  CompareSets(ActualSet2, ExpectedSet1);
}

TEST(SetTest, Merge) {
  s21::set<int> ActualSet1 = {1, 3, 5};
  s21::set<int> ActualSet2 = {2, 3, 4, 6};

  std::set<int> ExpectedSet1 = {1, 2, 3, 4, 5, 6};
  std::set<int> ExpectedSet2 = {3};  // Only duplicate remains

  ActualSet1.merge(ActualSet2);

  CompareSets(ActualSet1, ExpectedSet1);
  CompareSets(ActualSet2, ExpectedSet2);
}

TEST(SetTest, Find) {
  s21::set<int> ActualSet = {4, 4, 1, 6, 3, 9};

  auto it1 = ActualSet.find(3);
  EXPECT_NE(it1, ActualSet.end());
  EXPECT_EQ(*it1, 3);

  auto it2 = ActualSet.find(10);
  EXPECT_EQ(it2, ActualSet.end());
}

TEST(SetTest, FindString) {
  s21::set<std::string> ActualSet = {"Hello", "World"};

  auto it1 = ActualSet.find("World");
  EXPECT_NE(it1, ActualSet.end());
  EXPECT_EQ(*it1, "World");

  auto it2 = ActualSet.find("Goodbye");
  EXPECT_EQ(it2, ActualSet.end());
}

TEST(SetTest, Contains) {
  s21::set<int> ActualSet = {1, 2, 3, 4, 5};

  EXPECT_TRUE(ActualSet.contains(1));
  EXPECT_TRUE(ActualSet.contains(3));
  EXPECT_TRUE(ActualSet.contains(5));

  EXPECT_FALSE(ActualSet.contains(0));
  EXPECT_FALSE(ActualSet.contains(6));
  EXPECT_FALSE(ActualSet.contains(-1));
}

// TEST(MapTest, At) {
//   s21::map<int, std::string> ActualMap = {{1, "one"}, {2, "two"}};

//   EXPECT_EQ(ActualMap.at(1), "one");
//   EXPECT_EQ(ActualMap.at(2), "two");

//   // Modify element through at()
//   ActualMap.at(2) = "TWO";
//   EXPECT_EQ(ActualMap.at(2), "TWO");

//   EXPECT_ANY_THROW(ActualMap.at(4));
// }

// TEST(MapTest, SquareBracketOperator) {
//   s21::map<int, std::string> ActualMap;
//   std::map<int, std::string> ExpectedMap;

//   ActualMap[1] = "one";
//   ActualMap[2] = "two";

//   ExpectedMap[1] = "one";
//   ExpectedMap[2] = "two";

//   EXPECT_EQ(ActualMap[1], "one");
//   EXPECT_EQ(ActualMap[2], "two");

//   // Modify existing element
//   ActualMap[2] = "TWO";
//   ExpectedMap[2] = "TWO";

//   CompareMaps(ActualMap, ExpectedMap);
// }

// TEST(MapTest, BeginEnd) {
//   s21::map<int, std::string> ActualMap = {{1, "one"}, {2, "two"}, {3,
//   "three"}};

//   auto it = ActualMap.begin();
//   EXPECT_EQ(it->first, 1);
//   EXPECT_EQ(it->second, "one");
//   it++;
//   EXPECT_EQ(it->first, 2);
//   EXPECT_EQ(it->second, "two");
//   it++;
//   it++;
//   EXPECT_EQ(it, ActualMap.end());

//   // Test empty map
//   s21::map<int, std::string> EmptyMap;
//   EXPECT_EQ(EmptyMap.begin(), EmptyMap.end());
// }

// TEST(MapTest, Clear) {
//   s21::map<int, std::string> ActualMap = {{1, "one"}, {2, "two"}};
//   std::map<int, std::string> ExpectedMap = {{1, "one"}, {2, "two"}};

//   ActualMap.clear();
//   ExpectedMap.clear();

//   EXPECT_EQ(ActualMap.empty(), true);
//   CompareMaps(ActualMap, ExpectedMap);
// }

// TEST(MapTest, Insert) {
//   s21::map<int, std::string> ActualMap;
//   std::map<int, std::string> ExpectedMap;

//   // Insert using value_type
//   auto [it1, success1] = ActualMap.insert({1, "one"});
//   EXPECT_TRUE(success1);
//   EXPECT_EQ(it1->first, 1);
//   EXPECT_EQ(it1->second, "one");
//   ExpectedMap.insert({1, "one"});

//   // Insert duplicate element
//   auto [it2, success2] = ActualMap.insert({1, "ONE"});
//   EXPECT_FALSE(success2);
//   EXPECT_EQ(it2->second, "one");

//   // Insert using key and value
//   auto [it3, success3] = ActualMap.insert(2, "two");
//   EXPECT_TRUE(success3);
//   EXPECT_EQ(it3->first, 2);
//   EXPECT_EQ(it3->second, "two");
//   ExpectedMap.insert({2, "two"});

//   CompareMaps(ActualMap, ExpectedMap);
// }

// TEST(MapTest, InsertOrAssign) {
//   s21::map<int, std::string> ActualMap = {{1, "one"}, {2, "two"}};
//   std::map<int, std::string> ExpectedMap = {{1, "one"}, {2, "two"}};

//   // Insert new element
//   auto [it1, success1] = ActualMap.insert_or_assign(3, "three");
//   EXPECT_TRUE(success1);
//   EXPECT_EQ(it1->first, 3);
//   EXPECT_EQ(it1->second, "three");
//   ExpectedMap.insert_or_assign(3, "three");

//   // Assign to existing element
//   auto [it2, success2] = ActualMap.insert_or_assign(2, "TWO");
//   EXPECT_FALSE(success2);
//   EXPECT_EQ(it2->first, 2);
//   EXPECT_EQ(it2->second, "TWO");
//   ExpectedMap.insert_or_assign(2, "TWO");

//   CompareMaps(ActualMap, ExpectedMap);
// }

// TEST(MapTest, Erase) {
//   s21::map<int, std::string> ActualMap = {{1, "one"}, {2, "two"}, {3,
//   "three"}, {4, "four"}}; std::map<int, std::string> ExpectedMap = {{1,
//   "one"}, {2, "two"}, {3, "three"}, {4, "four"}};

//   // Find and erase element with key 3
//   auto it = ActualMap.find(3);
//   ActualMap.erase(it);
//   ExpectedMap.erase(3);

//   CompareMaps(ActualMap, ExpectedMap);

//   EXPECT_FALSE(ActualMap.contains(3));

//   // Erase first and last elements
//   it = ActualMap.find(1);
//   ActualMap.erase(it);
//   it = ActualMap.find(4);
//   ActualMap.erase(it);

//   ExpectedMap.erase(1);
//   ExpectedMap.erase(4);

//   CompareMaps(ActualMap, ExpectedMap);
// }

// TEST(MapTest, Swap) {
//   s21::map<int, std::string> ActualMap1 = {{1, "one"}, {2, "two"}};
//   s21::map<int, std::string> ActualMap2 = {{3, "three"}, {4, "four"}, {5,
//   "five"}};

//   std::map<int, std::string> ExpectedMap1 = {{1, "one"}, {2, "two"}};
//   std::map<int, std::string> ExpectedMap2 = {{3, "three"}, {4, "four"}, {5,
//   "five"}};

//   ActualMap1.swap(ActualMap2);

//   CompareMaps(ActualMap1, ExpectedMap2);
//   CompareMaps(ActualMap2, ExpectedMap1);
// }

// TEST(MapTest, Contains) {
//   s21::map<int, std::string> ActualMap = {{1, "one"}, {2, "two"}, {3,
//   "three"}};

//   EXPECT_TRUE(ActualMap.contains(1));
//   EXPECT_TRUE(ActualMap.contains(2));
//   EXPECT_TRUE(ActualMap.contains(3));

//   EXPECT_FALSE(ActualMap.contains(0));
//   EXPECT_FALSE(ActualMap.contains(4));
//   EXPECT_FALSE(ActualMap.contains(-1));
// }
