#ifndef VECTOR
#define VECTOR

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace s21 {
template <typename T>
class vector {
 private:
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  using pointer = value_type*;
  using const_pointer = const value_type*;

  pointer data_ptr;
  size_type Size;
  size_type Capacity;

  void reallocate(size_type new_capacity);

 public:
  class VectorIterator;
  class VectorConstIterator;

  using iterator = VectorIterator;
  using const_iterator = VectorConstIterator;

  // Конструкторы
  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& v);
  vector(vector&& v);
  vector& operator=(vector&& v);

  // Деструктор
  ~vector();

  // Методы
  reference at(size_type pos);
  reference operator[](size_type pos);
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  pointer data();
  const_pointer data() const;
  bool empty() const;
  size_type size() const;
  size_type max_size();
  size_type capacity() const;
  void reserve(size_type size);
  void shrink_to_fit();
  void clear();
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);
  void erase(iterator pos);

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;
  iterator insert(iterator pos, const_reference value);

  class VectorIterator {
   private:
    pointer current;

   public:
    VectorIterator(pointer ptr) : current(ptr) {}

    reference operator*() { return *current; }

    VectorIterator& operator++() {
      ++current;
      return *this;
    }

    VectorIterator operator++(int) {
      VectorIterator temp = *this;
      ++(*this);
      return temp;
    }

    VectorIterator& operator--() {
      --current;
      return *this;
    }

    VectorIterator operator--(int) {
      VectorIterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const VectorIterator& other) const {
      return current == other.current;
    }

    bool operator!=(const VectorIterator& other) const {
      return current != other.current;
    }
  };

  class VectorConstIterator {
   private:
    const_pointer current;

   public:
    VectorConstIterator(const_pointer ptr) : current(ptr) {}

    const_reference operator*() const { return *current; }

    VectorConstIterator& operator++() {
      ++current;
      return *this;
    }

    VectorConstIterator operator++(int) {
      VectorConstIterator temp = *this;
      ++(*this);
      return temp;
    }

    VectorConstIterator& operator--() {
      --current;
      return *this;
    }

    VectorConstIterator operator--(int) {
      VectorConstIterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const VectorConstIterator& other) const {
      return current == other.current;
    }

    bool operator!=(const VectorConstIterator& other) const {
      return current != other.current;
    }
  };
};

// Реализация методов

template <typename value_type>
void vector<value_type>::reallocate(size_type new_capacity) {
  pointer new_data = new value_type[new_capacity];
  std::copy(data_ptr, data_ptr + Size, new_data);
  delete[] data_ptr;
  data_ptr = new_data;
  Capacity = new_capacity;
}

template <typename value_type>
vector<value_type>::vector() : data_ptr(nullptr), Size(0), Capacity(0) {}

template <typename value_type>
vector<value_type>::vector(size_type n)
    : data_ptr(new value_type[n]), Size(n), Capacity(n) {
  std::fill(data_ptr, data_ptr + n, value_type());
}

template <typename value_type>
vector<value_type>::vector(const vector& v)
    : data_ptr(new value_type[v.Capacity]), Size(v.Size), Capacity(v.Capacity) {
  std::copy(v.data_ptr, v.data_ptr + v.Size, data_ptr);
}

template <typename value_type>
vector<value_type>::vector(vector&& v)
    : data_ptr(v.data_ptr), Size(v.Size), Capacity(v.Capacity) {
  v.data_ptr = nullptr;
  v.Size = 0;
  v.Capacity = 0;
}

template <typename value_type>
vector<value_type>::vector(std::initializer_list<value_type> const& items)
    : data_ptr(new value_type[items.size()]),
      Size(items.size()),
      Capacity(items.size()) {
  std::copy(items.begin(), items.end(), data_ptr);
}

template <typename value_type>
vector<value_type>::~vector() {
  clear();
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::at(size_type pos) {
  if (pos >= Size) {
    throw std::out_of_range("Index out of range");
  }
  return data_ptr[pos];
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    size_type pos) {
  return data_ptr[pos];
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::front() {
  return data_ptr[0];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::front() const {
  return data_ptr[0];
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::back() {
  return data_ptr[Size - 1];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::back() const {
  return data_ptr[Size - 1];
}

template <typename value_type>
typename vector<value_type>::pointer vector<value_type>::data() {
  return data_ptr;
}

template <typename value_type>
typename vector<value_type>::const_pointer vector<value_type>::data() const {
  return data_ptr;
}

template <typename value_type>
bool vector<value_type>::empty() const {
  return Size == 0;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size() const {
  return Size;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity() const {
  return Capacity;
}

template <typename value_type>
void vector<value_type>::reserve(size_type new_cap) {
  if (new_cap > Capacity) {
    reallocate(new_cap);
  }
}

template <typename value_type>
void vector<value_type>::shrink_to_fit() {
  if (Capacity > Size) {
    reallocate(Size);
  }
}

template <typename value_type>
void vector<value_type>::clear() {
  delete[] data_ptr;
  data_ptr = nullptr;
  Size = 0;
  Capacity = 0;
}

template <typename value_type>
void vector<value_type>::push_back(const_reference value) {
  if (Size == Capacity) {
    reserve(Capacity == 0 ? 1 : Capacity * 2);
  }
  data_ptr[Size++] = value;
}

template <typename value_type>
void vector<value_type>::pop_back() {
  if (Size > 0) {
    --Size;
  }
}

template <typename value_type>
void vector<value_type>::swap(vector& other) {
  std::swap(data_ptr, other.data_ptr);
  std::swap(Size, other.Size);
  std::swap(Capacity, other.Capacity);
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::begin() {
  return iterator(data_ptr);
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::end() {
  return iterator(data_ptr + Size);
}

template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::cbegin() const {
  return const_iterator(data_ptr);
}

template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::cend() const {
  return const_iterator(data_ptr + Size);
}

template <typename value_type>
vector<value_type>& vector<value_type>::operator=(vector&& v) {
  if (this != &v) {
    delete[] data_ptr;

    data_ptr = v.data_ptr;
    Size = v.Size;
    Capacity = v.Capacity;

    v.data_ptr = nullptr;
    v.Size = 0;
    v.Capacity = 0;
  }
  return *this;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size() {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const_reference value) {
  size_type index = pos - begin();

  if (Size == Capacity) {
    reserve(Capacity == 0 ? 1 : Capacity * 2);
  }

  for (size_type i = Size; i > index; --i) {
    data_ptr[i] = data_ptr[i - 1];
  }

  data_ptr[index] = value;
  ++Size;

  return begin() + index;
}

template <typename value_type>
void vector<value_type>::erase(iterator pos) {
  size_type index = pos - begin();

  for (size_type i = index; i < Size - 1; ++i) {
    data_ptr[i] = data_ptr[i + 1];
  }

  --Size;
}
}  // namespace s21
#endif  // VECTOR
