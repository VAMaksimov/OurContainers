#ifndef S21_CONTAINERS_H_S21_VECTOR_H
#define S21_CONTAINERS_H_S21_VECTOR_H

#include "components/s21_sequence_containers.h"

/**
 * @file s21_vector.h
 * @brief Implementation of vector container for s21_containers library
 * @details This project was initially started by peer barleysp, who later left
 * the project. Peer countesz was responsible for debugging, adding tests, and
 * implementing the insert_many and insert_many_back functions. Duplicate
 * functions and iterator implementation through a class were removed from the
 * original implementation as they were deemed unnecessary.
 * @author barleysp, countesz
 * @date 2025
 */

namespace s21 {
template <typename T>
class vector : public SequenceContainer<vector<T>, T> {
 private:
  // Vector Member type
  using value_type = typename SequenceContainer<list<T>, T>::value_type;
  using reference = typename SequenceContainer<list<T>, T>::reference;
  using const_reference =
      typename SequenceContainer<list<T>, T>::const_reference;
  using size_type = typename SequenceContainer<list<T>, T>::size_type;

  using iterator = T*;
  using const_iterator = const T*;

  using const_pointer = const value_type*;
  using pointer = value_type*;

  pointer data_ptr;
  size_type Size;
  size_type Capacity;

  void reallocate(size_type new_capacity);

 public:
  // Vector Member functions
  vector();  // default constructor, creates empty vector
  explicit vector(
      size_type n);  // parameterized constructor, creates the vector of size n
  vector(std::initializer_list<value_type> const&
             items);        // initializer list constructor, creates vector
                            // initizialized using std::initializer_list
  vector(const vector& v);  // copy constructor
  vector(vector&& v);       // move constructor
  vector& operator=(vector&& v);  // assignment operator overload for moving
                                  // object, by countesz

  // Destructor
  ~vector();  // destructor

  // Vector Element access
  reference at(size_type pos);  // access specified element with bounds checking
  reference operator[](size_type pos);     // access specified element
  const_reference front() const override;  // access the first element
  const_reference back() const override;   // access the last element
  pointer data();  // direct access to the underlying array

  // Vector Iterators
  iterator begin();  // returns an iterator to the beginning
  iterator end();    // returns an iterator to the end

  // not specified in the spec
  const_iterator cbegin() const;
  const_iterator cend() const;

  // Vector Capacity
  bool empty()
      const noexcept override;  // checks whether the container is empty
  size_type size() const noexcept override;  // returns the number of elements
  size_type max_size() const noexcept
      override;  // returns the maximum possible number of elements
  void reserve(
      size_type size);  // allocate storage of size elements and copies current
                        // array elements to a newely allocated array
  size_type capacity() const;  // returns the number of elements that can be
                               // held in currently allocated storage
  void shrink_to_fit();        // reduces memory usage by freeing unused memory

  // Vector Modifiers
  void clear();  // clears the contents
  iterator insert(
      iterator pos,
      const_reference value);  // inserts elements into concrete pos and returns
                               // the iterator that points to the new element
  void erase(iterator pos);    // erases element at pos
  void push_back(const_reference value);       // adds an element to the end
  void pop_back();                             // removes the last element
  void swap(vector& other) noexcept override;  // swaps the contents

  // Methods insert_many
  template <typename... Args>
  iterator insert_many(
      const_iterator pos,
      Args&&... args);  // inserts multiple elements at position , by countesz
  template <typename... Args>
  void insert_many_back(
      Args&&... args);  // adds multiple elements to the end, by countesz
};

// Vector Member functions implementation

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
  if (pos >= Size || Size == 0) {
    throw std::out_of_range("Index out range");
  }
  return data_ptr[pos];
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    size_type pos) {
  return data_ptr[pos];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::front() const {
  return data_ptr[0];
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
bool vector<value_type>::empty() const noexcept {
  return Size == 0;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size()
    const noexcept {
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
void vector<value_type>::swap(vector& other) noexcept {
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
    vector temp(std::move(v));
    swap(temp);
  }
  return *this;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size()
    const noexcept {
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

/*Insert_many methods*/

template <typename value_type>
template <typename... Args>
typename vector<value_type>::iterator vector<value_type>::insert_many(
    const_iterator pos, Args&&... args) {
  s21::vector<value_type> tmp{args...};
  iterator position = const_cast<iterator>(pos);
  size_type index = position - begin();

  for (size_type i = 0; i < tmp.size(); ++i) {
    position = insert(position, tmp[i]) + 1;
  }

  return begin() + index;
}

template <typename value_type>
template <typename... Args>
void vector<value_type>::insert_many_back(Args&&... args) {
  (push_back(std::forward<Args>(args)), ...);
}

}  // namespace s21
#endif  // S21_CONTAINERS_H_S21_VECTOR_H
