#ifndef S21_CONTAINERS_H_S21_SEQUENCE_CONTANERS_H
#define S21_CONTAINERS_H_S21_SEQUENCE_CONTANERS_H

#include <initializer_list>
#include <iostream>
#include <limits>

/**
 * @file s21_sequence_containers.h
 * @brief Base class for sequence containers in the s21 containers library
 *
 * @details This file defines a base class template for sequence containers.
 * It attempts to establish a common interface for various sequence containers
 * like vector, list, and array. The class defines common type aliases and
 * declares pure virtual methods that derived classes must implement.
 *
 * In practice, this approach has limitations as different container types
 * have unique interfaces and behaviors that don't always fit into a common
 * base class. While this design provides some uniformity, many
 * container-specific operations still need to be implemented separately in each
 * derived class.
 * @author countesz
 * @date 2025
 */

namespace s21 {

template <typename Derived, typename T>
class SequenceContainer {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

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