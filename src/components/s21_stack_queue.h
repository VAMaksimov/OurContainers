#ifndef CPP2_S21_CONTAINERS_COMPONENTS_S21_STACK_QUEUE_H_
#define CPP2_S21_CONTAINERS_COMPONENTS_S21_STACK_QUEUE_H_

// 1) Related header
// 2) C system headers
// 3) C++ standard library headers
#include <initializer_list>
// 4) other libraries' headers
// 5) project's headers.
#include "../s21_containers.h"

namespace s21 {
template <typename T>
class ContainerAdaptor : public Container<T> {
 public:
  using value_type_ = T;
  using reference_ = T &;
  using const_reference_ = const T &;
  using size_type_ = unsigned long long;

  // Main funcs
  ContainerAdaptor();
  ~ContainerAdaptor() { delete[] data_; }

  ContainerAdaptor(std::initializer_list<value_type_> const &items);
  ContainerAdaptor(const ContainerAdaptor &other);
  ContainerAdaptor(ContainerAdaptor &&s);
  ContainerAdaptor &operator=(ContainerAdaptor &&s);

  // Other funcs
  virtual void push(const_reference_ value) = 0;
  virtual void pop() = 0;

  void swap(ContainerAdaptor &other);

  bool empty() const override { return actual_size_ == 0; }
  size_type_ size() const override { return actual_size_; }
  void PrintContainer();

 private:
  const size_type_ kDefaultCapacity = 16;
  value_type_ *data_;
  size_type_ capacity_;
  size_type_ actual_size_;

  void GrowCapacity(size_type_ new_capacity);
};

template <typename T>
ContainerAdaptor<T>::ContainerAdaptor()
    : data_(new value_type_[kDefaultCapacity]),
      capacity_(kDefaultCapacity),
      actual_size_(0){};

template <typename T>
ContainerAdaptor<T>::ContainerAdaptor(
    std::initializer_list<value_type_> const &items) {
  data_ = new value_type_[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    data_[i] = *it;
    i++;
  }
  actual_size_ = items.size();
  capacity_ = items.size();
}

template <typename T>
ContainerAdaptor<T>::ContainerAdaptor(const ContainerAdaptor &other)
    : data_(new value_type_[other.capacity_]),
      capacity_(other.capacity_),
      topIndex_(other.topIndex_) {
  for (size_type_ i = 0; i < topIndex_; ++i) {
    data_[i] = other.data_[i];
  }
}

template <typename T>
ContainerAdaptor<T>::ContainerAdaptor(ContainerAdaptor &&other)
    : capacity_(other.capacity_), actual_size_(other.actual_size_) {
  if (this == &other) return;
  delete[] data_;
  data_ = other.data_;
  other.data_ = nullptr;
}

template <typename T>
ContainerAdaptor<T> &ContainerAdaptor<T>::operator=(ContainerAdaptor &&other) {
  if (this == &other) return;
  delete[] data_;
  data_ = other.data_;
  other.data_ = nullptr;
  capacity_ = other.capacity_;
  actual_size_ = other.actual_size_;
}

template <typename T>
void ContainerAdaptor<T>::swap(ContainerAdaptor &other) {
  std::swap(data_, other.data_);
  std::swap(capacity_, other.capacity_);
  std::swap(actual_size_, other.actual_size_);
}

template <typename T>
void ContainerAdaptor<T>::PrintContainer() {
  for (size_type_ i = 0; i < actual_size_; ++i) {
    std::cout << data_[i] << " ";
  }
  std::cout << std::endl;
}

template <typename T>
void ContainerAdaptor<T>::GrowCapacity(size_type_ new_capacity) {
  if (new_capacity <= capacity_) return;

  value_type_ *buffer = new value_type_[new_capacity];

  for (size_type_ i = 0; i < actual_size_; ++i) buffer[i] = std::move(data_[i]);

  delete[] data_;
  data_ = buffer;
  capacity_ = new_capacity;
}

template <typename T>
class Stack : public ContainerAdaptor<T> {
 public:
  using value_type_ = T;
  using reference_ = T &;
  using const_reference_ = const T &;
  using size_type_ = unsigned long long;

  Stack() : ContainerAdaptor<T>() {}
  Stack(std::initializer_list<value_type_> const &items)
      : ContainerAdaptor<T>(items) {}
  Stack(const ContainerAdaptor<T> &other) : ContainerAdaptor<T>(other) {}
  Stack(ContainerAdaptor<T> &&other) : ContainerAdaptor<T>(std::move(other)) {}

  const_reference_ top() const { return this->data_[this->actual_size_ - 1]; }

  void push(const_reference_ value) override;
  virtual void pop() override;
};

// inserts an element at the top
template <typename T>
void Stack<T>::push(const_reference_ value) {
  if (this->actual_size_ == this->capacity_) {
    this->GrowCapacity(this->capacity_ + this->capacity_ / 2);
  }
  this->data_[this->actual_size_++] = value;
}

// removes the top element
template <typename T>
void Stack<T>::pop() {
  if (this->actual_size_ == 0) return;
  this->actual_size_--;
}

template <typename T>
class Queue : public ContainerAdaptor<T> {
 public:
  using value_type_ = T;
  using reference_ = T &;
  using const_reference_ = const T &;
  using size_type_ = unsigned long long;

  Queue() : ContainerAdaptor<T>() {}
  Queue(std::initializer_list<value_type_> const &items)
      : ContainerAdaptor<T>(items) {}
  Queue(const ContainerAdaptor<T> &other) : ContainerAdaptor<T>(other) {}
  Queue(ContainerAdaptor<T> &&other) : ContainerAdaptor<T>(std::move(other)) {}

  // access the first element
  const_reference_ front() { return this->data_[0]; }
  const_reference_ back() { return this->data_[this->actual_size_ - 1]; }

  void push(const_reference_ value) override;
  void pop() override;
};

template <typename T>
void Queue<T>::push(const_reference_ value) {
  if (this->actual_size_ == this->capacity_) {
    this->GrowCapacity(this->capacity_ + this->capacity_ / 2);
  }
  this->data_[this->actual_size_++] = value;
}

// removes the first element
template <typename T>
void Queue<T>::pop() {
  if (this->actual_size_ == 0) return;
  for (size_type_ i = 1; i < this->actual_size_; ++i) {
    this->data_[i - 1] = std::move(this->data_[i]);
  }
  this->actual_size_--;
}
}  // namespace s21

#endif  // CPP2_S21CONTAINERS_COMPONENTS_S21_STACK_H_