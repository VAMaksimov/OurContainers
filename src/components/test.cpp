#include <iostream>

#include "s21_set.h"
// #include <set>

int main() {
  // std::set<int> MySet = {0};
  // s21::set<int> MySet2 = {1, 2, 3};
  s21::set<int> MySet2;
  // std::cout << "Size = " << MySet2.size() << std::endl;

  // MySet.insert(5);
  // MySet.insert(10);
  // MySet2.insert(5);
  // MySet2.insert(10);
  if(MySet2.empty()) std::cout << "Tree pusto" << std::endl;
  else
  std::cout << "Tree ne pusto. Size = " << MySet2.size() << std::endl;
  // std::cout << MySet.max_size();
}