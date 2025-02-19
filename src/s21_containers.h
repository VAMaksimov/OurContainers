#ifndef CPP2_S21CONTAINERS_S21_CONTAINERS_H_
#define CPP2_S21CONTAINERS_S21_CONTAINERS_H_

// 1) Related header
// 2) C system headers
// 3) C++ standard library headers
// 4) other libraries' headers
// 5) project's headers.
#include "components/s21_stack.h"
// #include "components/s21_map.h"

namespace s21 {
template <typename T>
class Container {
 public:
  using value_type_ = T;
  using reference_ = T &;
  using const_reference_ = const T &;
  // defines the type of the container size (standard type is size_t)
  using size_type_ = unsigned long long;

  // Compiler provides the constructor and/or destructor automatically when
  // `= default` is used
  Container() = default;
  // If a derived class is permitted to override a base class’s methods,
  // the virtual keyword is used. By adding virtual to a method’s definition,
  // it is declared that a derived class’s implementation should be used if one
  // is supplied.
  // Within the implementation, the override keyword to the
  // method’s declaration is added
  virtual ~Container() = default;

  // Writing = 0 after a member function inside a class declaration
  // marks that function as pure virtual. A pure virtual function indicates that
  // the class is abstract and cannot be instantiated directly
  virtual bool empty() const = 0;
  virtual size_type size() const = 0;
};

template <typename T>
class Stack : public Container<T> {
 public:
  using value_type_ = typename Container<T>::value_type_;
  using reference_ = typename Container<T>::reference_;
  using const_reference_ = typename Container<T>::const_reference_;
  using size_type_ = typename Container<T>::size_type_;

  Stack()
      : data_(new value_type_[kDefaultCapacity]),
        capacity_(kDefaultCapacity),
        top_index_(0) {}
  ~Stack() { delete[] data_; }

  Stack(std::initializer_list<value_type> const &items) {
    data_ = new value_type_[items.size()];
    int i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
      data_[i] = *it;
      i++;
    }
    top_index_ = items.size();
    capacity_ = items.size();
  }

  Stack(const Stack &other)
      : data_(new value_type_[other.capacity_]),
        capacity_(other.capacity_),
        topIndex_(other.topIndex_) {
    for (size_type_ i = 0; i < topIndex_; ++i) {
      data_[i] = other.data_[i];
    }
  }

  Stack(Stack &&s) : capacity_(s.capacity_), top_index_(s.top_index_) {
    if (this == &s) return;
    delete[] data_;
    data_ = other.data_;
    other.data_ = nullptr;
  }

  operator=(Stack && s) : capacity_(s.capacity_), top_index_(s.top_index_) {
    if (this == &s) return;
    delete[] data_;
    data_ = other.data_;
    other.data_ = nullptr;
  }

  bool empty() const override { return top_index_ == 0; }
  size_type_ size() const override { return top_index_; }

 private:
  const size_type_ kDefaultCapacity = 16;

  void GrowCapacity(size_type_ new_capacity) {
    if (new_capacity <= capacity_) return;

    value_type_ *buffer = new value_type_[new_capacity];

    for (size_type_ i = 0; i < top_index_; ++i) buffer[i] = std::move(data_[i]);

    delete[] data_;
    data_ = buffer;
    capacity_ = new_capacity;
  }

  value_type_ *data_;
  // Current allocated capacity
  size_type_ capacity_;
  // Index of the top element (size of current stack)
  size_type_ top_index_;
};
}  // namespace s21

#endif  // CPP2_S21CONTAINERS_S21_CONTAINERS_H_