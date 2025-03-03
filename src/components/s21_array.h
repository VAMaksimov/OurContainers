#ifndef S21_CONTAINERS_H_S21_array_H
#define S21_CONTAINERS_H_S21_array_H

#include <initializer_list>

#include "components/s21_sequence_containers.h"

namespace s21 {

template <typename T>
class array : public SequenceContainer<array<T>, T> {
 public:
  // Array Member type
  using value_type = typename SequenceContainer<array<T>, T>::value_type;
  using reference = typename SequenceContainer<array<T>, T>::reference;
  using const_reference =
      typename SequenceContainer<array<T>, T>::const_reference;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = typename SequenceContainer<array<T>, T>::size_type;

  // Array Member functions
  array();
  array(std::initializer_list<value_type> const& items);
  array(const array& other);
  array(array&& other) noexcept;
  ~array();

  // Assignment operators
  array& operator=(array&& other) noexcept;
  array& operator=(const array& other);

  // Array Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  iterator data() noexcept;

  // Array Iterators
  iterator begin() noexcept;
  iterator end() noexcept;

  // Array Capacity
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Array Modifiers
  void swap(array& other) noexcept;
  void fill(const_reference value);

 private:
  value_type* data_;
  size_type size_;
};

/*Array Member functions*/
template <typename T>
array<T>::array() : data_(nullptr), size_(0) {}

template <typename T>
array<T>::array(std::initializer_list<value_type> const& items)
    : size_(items.size()) {
  data_ = new value_type[size_];
  std::copy(items.begin(), items.end(), data_);
}

template <typename T>
array<T>::array(const array& other) : size_(other.size_) {
  data_ = new value_type[size_];
  std::copy(other.data_, other.data_ + size_, data_);
}

template <typename T>
array<T>::array(array&& other) noexcept
    : data_(other.data_), size_(other.size_) {
  other.data_ = nullptr;
  other.size_ = 0;
}

template <typename T>
array<T>::~array() {
  delete[] data_;
}
/*Array Element access*/
template <typename T>
typename array<T>::reference array<T>::operator[](size_type pos) {
  return data_[pos];
}

/*Array Iterators*/

/*Array Capacity*/
template <typename T>
typename array<T>::size_type array<T>::size() const noexcept {
  return size_;
}
/*Array Modifiers*/

}  // namespace s21

#endif  // S21_CONTAINERS_H_S21_ARRAY_H