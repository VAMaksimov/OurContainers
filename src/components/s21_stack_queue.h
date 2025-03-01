#ifndef CPP2_S21_CONTAINERS_COMPONENTS_S21_STACK_QUEUE_H_
#define CPP2_S21_CONTAINERS_COMPONENTS_S21_STACK_QUEUE_H_

// 1) Related header
// 2) C system headers
// 3) C++ standard library headers
#include <initializer_list>
#include <iostream>
#include <utility>
// 4) other libraries' headers
// 5) project's headers.

namespace s21 {
template <typename T>
class ContainerAdaptor {
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

  bool empty() const { return actual_size_ == 0; }
  size_type_ size() const { return actual_size_; }
  void PrintContainer() const;

  // in C there are ... and va_list for a variable number of parameters, but C++
  // provides a variadic templates.
  // The notation <typename... Args> declares a set of types (“type parameter
  // pack”) that can hold zero or more types. When insert_many_back is called,
  // the compiler determines types for each argument in that parameter pack.
  // Args &&...args are universal (forwarding) references.

  // If T reference is used, the function will not compile with variable
  // number of arguments:
  // void insert_many_back(value_type_ &&...args); expansion
  // pattern ‘s21::ContainerAdaptor<T>::value_type_ contains no parameter packs
  template <typename... Args>
  void insert_many_back(Args &&...args);

  // in this case `protected` keyword is crucial to make the class
  // inheritable and prevent direct access to members
 protected:
  const size_type_ kDefaultCapacity = 16;
  value_type_ *data_;
  size_type_ capacity_;
  size_type_ actual_size_;

  void GrowCapacity(size_type_ new_capacity);
};  // class ContainerAdaptor

template <typename T>
ContainerAdaptor<T>::ContainerAdaptor()
    : data_(new value_type_[kDefaultCapacity]()),
      capacity_(kDefaultCapacity),
      actual_size_(0){};

template <typename T>
ContainerAdaptor<T>::ContainerAdaptor(
    std::initializer_list<value_type_> const &items) {
  data_ = new value_type_[items.size()]();
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
    : data_(new value_type_[other.capacity_]()),
      capacity_(other.capacity_),
      actual_size_(other.actual_size_) {
  for (size_type_ i = 0; i < actual_size_; ++i) {
    data_[i] = other.data_[i];
  }
}

template <typename T>
ContainerAdaptor<T>::ContainerAdaptor(ContainerAdaptor &&other)
    : capacity_(other.capacity_), actual_size_(other.actual_size_) {
  if (this == &other) return;
  // no delete[] data bc it's constructor, so no memory alloc'd
  data_ = other.data_;
  other.data_ = nullptr;
  other.capacity_ = 0;
  other.actual_size_ = 0;
}

template <typename T>
ContainerAdaptor<T> &ContainerAdaptor<T>::operator=(ContainerAdaptor &&other) {
  if (this == &other) return *this;
  delete[] data_;
  data_ = other.data_;
  capacity_ = other.capacity_;
  actual_size_ = other.actual_size_;
  other.data_ = nullptr;
  other.capacity_ = 0;
  other.actual_size_ = 0;
  return *this;
}

template <typename T>
void ContainerAdaptor<T>::swap(ContainerAdaptor &other) {
  std::swap(data_, other.data_);
  std::swap(capacity_, other.capacity_);
  std::swap(actual_size_, other.actual_size_);
}

template <typename T>
void ContainerAdaptor<T>::PrintContainer() const {
  for (size_type_ i = 0; i < actual_size_; ++i) {
    std::cout << data_[i] << " ";
  }
  std::cout << std::endl;
}

template <typename T>
template <typename... Args>
void ContainerAdaptor<T>::insert_many_back(Args &&...args) {
  // For example args == {a, b, c}
  // The fold expression (push(args), ...) expands to
  // (push(a), push(b), push(c));
  // using the comma operator to evaluate each call in sequence.
  (push(args), ...);
}

template <typename T>
void ContainerAdaptor<T>::GrowCapacity(size_type_ new_capacity) {
  if (new_capacity <= capacity_) return;

  value_type_ *buffer = new value_type_[new_capacity]();

  for (size_type_ i = 0; i < actual_size_; ++i) buffer[i] = std::move(data_[i]);

  delete[] data_;
  data_ = buffer;
  capacity_ = new_capacity;
}

/**
 * @note ContainerAdaptor<T>::ContainerAdaptor tells the
 * compiler to inherit the constructors of the base class. This means if you
 * create a Stack<int> object, it will call the appropriate ContainerAdaptor
 * constructor to initialize its members (e.g., allocating memory for the
 * container). If you don't use this mechanism, you'll need to define your own
 * constructors in Stack which explicitly call the base class constructor in
 * the initializer list.
 *
 * Why const typename ContainerAdaptor<T>::const_reference_ and not simply
 * const T&?
 * The name const_reference_ is defined in the base class. If you were to
 * write const T& directly, you would be bypassing the abstraction provided by
 * ContainerAdaptor. In other words, you might be assuming that the constant
 * reference type is always exactly const T&, which may not necessarily be
 * true as the base class’s typedef could change its definition later.
 * This leaves room for the possibility that the implementation of
 * ContainerAdaptor might change the underlying type without requiring
 * changes in the derived Stack class.
 *
 * In a template class, names that depend on a template parameter (like
 * ContainerAdaptor<T>::const_reference_) aren’t automatically assumed to be
 * types. Adding typename tells the compiler explicitly, “This dependent name
 * represents a type.” Without typename, the compiler would flag an error
 * while parsing the template.
 */
template <typename T>
class Stack : public ContainerAdaptor<T> {
 public:
  using ContainerAdaptor<T>::ContainerAdaptor;
  using const_reference_ = typename ContainerAdaptor<T>::const_reference_;

  void push(const_reference_ value) override;
  void pop() override;

  const_reference_ top() {
    if (this->empty()) throw std::out_of_range("Stack is empty");
    return this->data_[this->actual_size_ - 1];
  }
};  // class Stack

template <typename T>
void Stack<T>::push(const_reference_ value) {
  if (this->actual_size_ == this->capacity_) {
    this->GrowCapacity(this->capacity_ + this->capacity_ / 2);
  }
  this->data_[this->actual_size_++] = value;
}

template <typename T>
void Stack<T>::pop() {
  if (!this->empty()) this->actual_size_--;
}

/**
 * @brief Queue is a specialization of ContainerAdaptor.
 * It inherits all the member functions from the base class ContainerAdaptor.
 * It's a container that stores elements in a first-in-first-out (FIFO) order.
 *
 * @tparam T
 *
 */
template <typename T>
class Queue : public ContainerAdaptor<T> {
 public:
  using ContainerAdaptor<T>::ContainerAdaptor;
  using const_reference_ = typename ContainerAdaptor<T>::const_reference_;
  using size_type_ = typename ContainerAdaptor<T>::size_type_;

  void push(const_reference_ value) override;
  void pop() override;

  // access the first element
  const_reference_ front() {
    if (this->empty()) throw std::out_of_range("Queue is empty");
    return this->data_[0];
  }
  const_reference_ back() {
    if (this->empty()) throw std::out_of_range("Queue is empty");
    return this->data_[this->actual_size_ - 1];
  }
};  // class Queue

template <typename T>
void Queue<T>::push(const_reference_ value) {
  if (this->actual_size_ == this->capacity_) {
    this->GrowCapacity(this->capacity_ + this->capacity_ / 2);
  }
  this->data_[this->actual_size_++] = value;
}

template <typename T>
void Queue<T>::pop() {
  if (this->empty()) return;
  for (size_type_ i = 1; i < this->actual_size_; ++i) {
    this->data_[i - 1] = std::move(this->data_[i]);
  }
  this->actual_size_--;
}
}  // namespace s21

#endif  // CPP2_S21CONTAINERS_COMPONENTS_S21_STACK_H_