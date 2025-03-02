#ifndef S21_CONTAINERS_H_S21_ARRAY_H
#define S21_CONTAINERS_H_S21_ARRAY_H

#include <initializer_list>

namespace s21 {

template <typename T>
class Array {
 public:
  // Member types
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  // Constructors and destructor
  Array();
  explicit Array(std::initializer_list<value_type> const& items);
  Array(const Array& other);
  Array(Array&& other) noexcept;
  ~Array();

  // Assignment operators
  Array& operator=(Array&& other) noexcept;
  Array& operator=(const Array& other);

  // Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  iterator data() noexcept;

  // Iterators
  iterator begin() noexcept;
  iterator end() noexcept;

  // Capacity
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Modifiers
  void swap(Array& other) noexcept;
  void fill(const_reference value);

 private:
  value_type* data_;
  size_type size_;
};

}  // namespace s21

#endif  // S21_CONTAINERS_H_S21_ARRAY_H