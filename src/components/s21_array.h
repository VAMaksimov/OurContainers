#ifndef S21_CONTAINERS_H_S21_array_H
#define S21_CONTAINERS_H_S21_array_H

#include <initializer_list>

#include "components/s21_sequence_containers.h"

namespace s21 {

template <typename T, std::size_t N>
class array : public SequenceContainer<array<T, N>, T> {
 public:
  // Array Member type
  using value_type = typename SequenceContainer<array<T, N>, T>::value_type;
  using reference = typename SequenceContainer<array<T, N>, T>::reference;
  using const_reference =
      typename SequenceContainer<array<T, N>, T>::const_reference;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = typename SequenceContainer<array<T, N>, T>::size_type;

  // Array Member functions
  array();
  array(std::initializer_list<value_type> const& items);
  array(const array& other);
  array(array&& other) noexcept;
  ~array() = default;

  // Assignment operators
  array& operator=(array&& other) noexcept;
  array& operator=(const array& other);

  // Array Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const override;
  const_reference back() const override;
  iterator data() noexcept;

  // Array Iterators
  iterator begin() noexcept;
  iterator end() noexcept;

  // Array Capacity
  bool empty() const noexcept override;
  constexpr size_type size() const noexcept override;
  constexpr size_type max_size() const noexcept override;

  // Array Modifiers
  void swap(array& other) noexcept override;
  void fill(const_reference value);

 private:
  value_type data_[N];
};

/*Array Member functions*/
template <typename T, std::size_t N>
inline array<T, N>::array() {}

template <typename T, std::size_t N>
inline array<T, N>::array(std::initializer_list<value_type> const& items) {
  std::copy(items.begin(), items.end(), data_);
}

template <typename T, std::size_t N>
inline array<T, N>::array(const array& other) {
  std::copy(other.data_, other.data_ + N, data_);
}

template <typename T, std::size_t N>
inline array<T, N>::array(array&& other) noexcept {
  std::move(other.begin(), other.end(), data_);
}

template <typename T, std::size_t N>
inline array<T, N>& array<T, N>::operator=(array&& other) noexcept {
  if (this != &other) {
    swap(other);
  }
  return *this;
}

template <typename T, std::size_t N>
inline array<T, N>& array<T, N>::operator=(const array& other) {
  if (this != &other) {
    std::copy(other.data_, other.data_ + N, data_);
  }
  return *this;
}

/*Array Element access*/
template <typename T, std::size_t N>
inline typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

template <typename T, std::size_t N>
inline typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T, std::size_t N>
inline typename array<T, N>::const_reference array<T, N>::front() const {
  return data_[0];
}

template <typename T, std::size_t N>
inline typename array<T, N>::const_reference array<T, N>::back() const {
  return data_[N - 1];
}

template <typename T, std::size_t N>
inline typename array<T, N>::iterator array<T, N>::data() noexcept {
  return data_;
}

/*Array Iterators*/
template <typename T, std::size_t N>
inline typename array<T, N>::iterator array<T, N>::begin() noexcept {
  return data_;
}

template <typename T, std::size_t N>
inline typename array<T, N>::iterator array<T, N>::end() noexcept {
  return data_ + N;
}

/*Array Capacity*/
template <typename T, std::size_t N>
inline bool array<T, N>::empty() const noexcept {
  return N == 0;
}

template <typename T, std::size_t N>
inline constexpr typename array<T, N>::size_type array<T, N>::size()
    const noexcept {
  return N;
}
template <typename T, std::size_t N>
inline constexpr typename array<T, N>::size_type array<T, N>::max_size()
    const noexcept {
  return size();
}
/*Array Modifiers*/
template <typename T, std::size_t N>
inline void array<T, N>::swap(array& other) noexcept {
  if constexpr (N > 0) {
    std::swap(data_, other.data_);
  }
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = value;
  }
}

}  // namespace s21

#endif  // S21_CONTAINERS_H_S21_ARRAY_H