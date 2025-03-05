#include <iostream>
#include <set>

#include "s21_set.h"

int main() {
  s21::set<int> set1 = {1, 2, 3};
  // s21::set<int> set2 = {0, 3, 4, 5};

  std::set<int> ExpectedSet1 = {1, 2, 3};
  // std::set<int> ExpectedSet2 = {0, 3, 4, 5};

  // выводим на экран
  std::cout << "Set1: ";
  for (const auto& elem : set1) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  // std::cout << "Set2: ";
  // for (const auto& elem : set2) {
  //   std::cout << elem << " ";
  // }
  // std::cout << std::endl;

  // Объединяем set2 в set1
  // set1.merge(set2);
  std::cout << "S21: " << set1.max_size() << std::endl;
  std::cout << "SET: " << ExpectedSet1.max_size() << std::endl;

  // Выводим содержимое set1
  // std::cout << "Set1: ";
  // for (const auto& elem : set1) {
  //   std::cout << elem << " ";
  // }
  // std::cout << std::endl;

  // std::cout << "Set2: ";
  // for (const auto& elem : set2) {
  //   std::cout << elem << " ";
  // }
  // std::cout << std::endl;

  // std::cout << "ORIGINAL:" << std::endl;
  // std::cout << "ExpectedSet1: ";
  // for (const auto& elem : ExpectedSet1) {
  //   std::cout << elem << " ";
  // }
  // std::cout << std::endl;

  // std::cout << "ExpectedSet2: ";
  // for (const auto& elem : ExpectedSet2) {
  //   std::cout << elem << " ";
  // }
  // std::cout << std::endl;

  return 0;
}