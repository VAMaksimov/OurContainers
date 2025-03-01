#include <iostream>

#include "s21_set.h"

int main() {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {0, 3, 4, 5};

  std::cout << "Set1: ";
  for (const auto& elem : set1) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  std::cout << "Set2: ";
  for (const auto& elem : set2) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  // Объединяем set2 в set1
  set1.merge(set2);

  // Выводим содержимое set1
  for (const auto& elem : set1) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  // Выводим содержимое set2
  for (const auto& elem : set2) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  return 0;
}