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
  virtual ~SequenceContainer() = default;

  // Access to elements
  virtual const_reference front() const = 0;
  virtual const_reference back() const = 0;

  // Capacity
  virtual bool empty() const noexcept = 0;
  virtual size_type size() const noexcept = 0;
  virtual size_type max_size() const noexcept = 0;

  // Modifiers
  virtual void swap(Derived& other) noexcept = 0;
};
}  // namespace s21

#endif  // S21_CONTAINERS_H_S21_SEQUENCE_CONTANERS_H