#include <iostream>
#include <set>

// #include "s21_set.h"

int main() {
  std::set<char> MySet = {0, 1, 3, 2, 7};
  // s21::set<int> MySet2 = {1, 2, 3, 5};
  // s21::set<int> copy(std::move(MySet2));
  // std::set<int> copy(std::move(MySet));
  // s21::set<int> MySet3;
  // std::set<int> MySet2;

  // MySet.begin()
  // MySet3 = MySet2;
  // std::cout << "Size = " << MySet2.size() << std::endl;

  // Обычный обход
  for (auto it = MySet.begin(); it != MySet.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  std::cout << "Begin & erase:" << std::endl;

  MySet.find(3);
  // std::cout << "Max size = " << MySet.max_size() << std::endl;
  std::cout << "+++++++++++++" << std::endl;

  // MySet.insert(5);
  // MySet.insert(10);
  // MySet2.insert(5);
  // MySet2.insert(10);
  if (MySet.empty()) {
    std::cout << "Tree MySet pusto" << std::endl;
  } else {
    std::cout << "Tree MySet ne pusto" << std::endl;
    std::cout << MySet.size() << std::endl;
  }
  // MySet.clear();
  // if (MySet.empty()) {
  //   std::cout << "Tree MySet pusto" << std::endl;
  // } else {
  //   std::cout << "Tree MySet ne pusto" << std::endl;
  //   std::cout << MySet.size() << std::endl;
  // }
  // for (auto it = MySet.begin(); it != MySet.end(); ++it) {
  //   std::cout << *it << " ";
  // }
  // std::cout << std::endl;
  // if (MySet3.empty()) {
  //   std::cout << "Tree MySet3 pusto" << std::endl;
  // } else {
  //   std::cout << "Tree MySet3 ne pusto" << std::endl;
  //   std::cout << MySet3.size() << std::endl;
  // }
  // std::cout << "~set" << std::endl;
  // copy.~set();
  // if (copy.empty()) {
  //   std::cout << "Tree COPY pusto" << std::endl;
  // } else {
  //   std::cout << "Tree COPY ne pusto" << std::endl;
  //   std::cout << copy.size() << std::endl;
  // }
  // std::cout << MySet.max_size();
}