#ifndef S21_CONTAINERS_H_S21_SEQUENCE_CONTANERS_H
#define S21_CONTAINERS_H_S21_SEQUENCE_CONTANERS_H

#include <initializer_list>
#include <iostream>
#include <limits>
namespace s21 {

template <typename Derived, typename T>
class SequenceContainer {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
};
}  // namespace s21

#endif  // S21_CONTAINERS_H_S21_SEQUENCE_CONTANERS_H