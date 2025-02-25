#include "components/s21_list.h"

#include <gtest/gtest.h>

#include "s21_containers.h"
TEST(Test_List, Default_Constructor) {
  s21::list<int> myList;
  EXPECT_EQ(myList.getSize(), 0);
  EXPECT_EQ(myList.getHead(),
            myList.getTail());  // ptr fake node: ptr head = ptr tail
}

TEST(Test_List, Parameterized_Constructor) {
  s21::list<int> myList(1);
  EXPECT_EQ(myList.getHead(), myList.getTail());
  s21::list<int> myList2(5);
  EXPECT_EQ(myList2.getSize(), 5);
  EXPECT_NE(myList2.getHead(), myList2.getTail());
}

TEST(Test_List, Iterator_Test) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  s21::list<int>::iterator it = myList.begin();

  EXPECT_EQ(*it, 1);
  it++;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(it, myList.end());
}

TEST(Test_List, Iterator_Decrement_Test) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  s21::list<int>::iterator it = myList.end();
  --it;
  EXPECT_EQ(*it, 5);
  --it;
  EXPECT_EQ(*it, 4);
  --it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);

  EXPECT_EQ(it, myList.begin());
  --it;
  EXPECT_EQ(it, myList.end());  // 1-2-3-4-5-nulptr
  --it;
  EXPECT_EQ(*it, 5);
}
TEST(Test_List, Copy_Constructor) {
  s21::list<int> myList1 = {1, 2, 3, 4, 5};
  s21::list<int> myList2(myList1);

  EXPECT_EQ(myList2.getSize(), myList1.getSize());
  EXPECT_NE(myList2.getHead(), myList1.getHead());

  auto it1 = myList1.begin();
  auto it2 = myList2.begin();
  EXPECT_EQ(*it2, *it1);

  it1 = myList1.end();
  it2 = myList2.end();
  --it1;
  --it2;
  EXPECT_EQ(*it2, *it1);
}

TEST(Test_List, MoveNonEmptyList) {
  s21::list<int> original{1, 2, 3};
  s21::list<int> moved(std::move(original));

  EXPECT_EQ(moved.getSize(), 3);
  EXPECT_EQ(*moved.begin(), 1);
  EXPECT_EQ(*++moved.begin(), 2);
  EXPECT_EQ(*++(++moved.begin()), 3);

  EXPECT_EQ(original.getSize(), 0);
  EXPECT_TRUE(original.begin() == original.end());
}

TEST(Test_List, MoveEmptyList) {
  s21::list<int> original;
  s21::list<int> moved(std::move(original));

  EXPECT_EQ(moved.getSize(), 0);
  EXPECT_TRUE(moved.begin() == moved.end());

  EXPECT_EQ(original.getSize(), 0);
  EXPECT_TRUE(original.begin() == original.end());
}

TEST(Test_List, AssignNonEmptyList) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2;
  list2 = list1;

  EXPECT_EQ(list2.getSize(), list1.getSize());
  EXPECT_NE(list2.getHead(), list1.getHead());

  auto it1 = list1.begin();
  auto it2 = list2.begin();
  while (it1 != list1.end() && it2 != list2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(Test_List, AssignEmptyList) {
  s21::list<int> list1;
  s21::list<int> list2 = {1, 2, 3};
  list1 = list2;

  EXPECT_EQ(list1.getSize(), list2.getSize());
  EXPECT_NE(list1.getHead(), list2.getHead());

  auto it1 = list1.begin();
  auto it2 = list2.begin();
  while (it1 != list1.end() && it2 != list2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(Test_List, SelfAssignment) {
  s21::list<int> list1 = {1, 2, 3};
  list1 = list1;

  EXPECT_EQ(list1.getSize(), 3);
  auto it = list1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}
TEST(Test_List, MoveAssignmentOperator) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2;
  list2 = std::move(list1);

  EXPECT_EQ(list2.getSize(), 3);
  EXPECT_EQ(list1.getSize(), 0);
  EXPECT_TRUE(list1.begin() == list1.end());
  EXPECT_NE(list2.getHead(), nullptr);

  auto it2 = list2.begin();
  EXPECT_EQ(*it2, 1);
  ++it2;
  EXPECT_EQ(*it2, 2);
  ++it2;
  EXPECT_EQ(*it2, 3);
}

TEST(Test_List, IterateThroughList) {
  s21::list<int> list = {1, 2, 3, 4, 5};
  s21::list<int>::const_iterator it = list.begin();

  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_TRUE(it == list.end());
}

TEST(Test_List, ConstIteratorEquality) {
  s21::list<int> list = {1, 2, 3};
  s21::list<int>::const_iterator it1 = list.begin();
  s21::list<int>::const_iterator it2 = list.begin();

  EXPECT_TRUE(it1 == it2);
  ++it1;
  EXPECT_FALSE(it1 == it2);
}

TEST(Test_List, ConstIteratorInequality) {
  s21::list<int> list = {1, 2, 3};
  s21::list<int>::const_iterator it1 = list.begin();
  s21::list<int>::const_iterator it2 = list.begin();

  EXPECT_FALSE(it1 != it2);
  ++it1;
  EXPECT_TRUE(it1 != it2);
}

TEST(Test_List, Front_Method) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  EXPECT_EQ(myList.front(), 1);
}

TEST(Test_List, Back_Method) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  EXPECT_EQ(myList.back(), 5);
}

TEST(Test_List, Empty_Method) {
  s21::list<int> myList;
  EXPECT_TRUE(myList.empty());
}

TEST(Test_List, Size_Method) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  EXPECT_EQ(myList.size(), 5);
}

TEST(Test_List, Max_Size_Method) {
  s21::list<int> myList;
  EXPECT_GT(myList.max_size(), 0);
}

TEST(Test_List, Insert_Method_Before_First_Element) {
  s21::list<int> myList = {1, 2, 3};
  auto it = myList.begin();
  myList.insert(it, 0);
  EXPECT_EQ(myList.front(), 0);
  it = myList.begin();
  EXPECT_EQ(*(++it), 1);
  EXPECT_EQ(myList.size(), 4);
}

TEST(Test_List, Insert_Method_Before_Second_Element) {
  s21::list<int> myList = {0, 1, 2, 3};
  auto it = myList.begin();
  ++it;
  myList.insert(it, 1);
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(myList.size(), 5);
}

TEST(Test_List, Insert_Method_Before_Last_Element) {
  s21::list<int> myList = {1, 2, 3, 5};
  auto it = myList.end();
  --it;
  myList.insert(it, 4);
  EXPECT_EQ(myList.back(), 5);
  EXPECT_EQ(*(--it), 4);
  it = myList.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(it, myList.end());
}

TEST(Test_List, Erase_Method) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  auto it = myList.begin();
  myList.erase(it);
  EXPECT_EQ(myList.front(), 2);  // mylist={2, 3, 4, 5};
  EXPECT_EQ(myList.size(), 4);

  it = myList.begin();
  ++it;

  myList.erase(it);
  EXPECT_EQ(myList.front(), 2);  // mylist={2, 4, 5};
  EXPECT_EQ(myList.size(), 3);

  it = myList.end();
  --it;
  myList.erase(it);
  EXPECT_EQ(myList.back(), 4);
  EXPECT_EQ(myList.size(), 2);
}

TEST(Test_List, Push_Back_Method) {
  s21::list<int> myList;
  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);

  EXPECT_EQ(myList.size(), 3);
  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.back(), 3);

  myList.push_back(4);
  EXPECT_EQ(myList.size(), 4);
  EXPECT_EQ(myList.back(), 4);
}
