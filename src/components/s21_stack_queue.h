#ifndef CPP2_S21_CONTAINERS_COMPONENTS_S21_STACK_QUEUE_H_
#define CPP2_S21_CONTAINERS_COMPONENTS_S21_STACK_QUEUE_H_

#include <initializer_list>

namespace s21 {
template <typename T>
class ContainerAdaptor : public Container<T> {
 public:
  using value_type_ = typename Container<T>::value_type_;
  using reference_ = typename Container<T>::reference_;
  using const_reference_ = typename Container<T>::const_reference_;
  using size_type_ = typename Container<T>::size_type_;

  // Main funcs
  ContainerAdaptor();
  ~ContainerAdaptor() { delete[] data_; }

  ContainerAdaptor(std::initializer_list<value_type_> const &items);
  ContainerAdaptor(const ContainerAdaptor &other);
  ContainerAdaptor(ContainerAdaptor &&s);
  operator=(ContainerAdaptor && s);

  // Other funcs
  virtual void push(const_reference_ value) = 0;
  virtual void pop() = 0;

  void swap(ContainerAdaptor &other);

  bool empty() const override { return actual_size_ == 0; }
  size_type_ size() const override { return actual_size_; }

 private:
  const size_type_ kDefaultCapacity = 16;

  void GrowCapacity(size_type_ new_capacity);

  value_type_ *data_;
  size_type_ capacity_;
  size_type_ actual_size_;

 public:
  ContainerAdaptor()
      : data_(new value_type_[kDefaultCapacity]),
        capacity_(kDefaultCapacity),
        actual_size_(0) {};

  ContainerAdaptor(std::initializer_list<value_type_> const &items) {
    data_ = new value_type_[items.size()];
    int i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
      data_[i] = *it;
      i++;
    }
    actual_size_ = items.size();
    capacity_ = items.size();
  }

  ContainerAdaptor(const ContainerAdaptor &other)
      : data_(new value_type_[other.capacity_]),
        capacity_(other.capacity_),
        topIndex_(other.topIndex_) {
    for (size_type_ i = 0; i < topIndex_; ++i) {
      data_[i] = other.data_[i];
    }
  }

  ContainerAdaptor(ContainerAdaptor &&s)
      : capacity_(s.capacity_), actual_size_(s.actual_size_) {
    if (this == &s) return;
    delete[] data_;
    data_ = other.data_;
    other.data_ = nullptr;
  }

  operator=(ContainerAdaptor && s)
      : capacity_(s.capacity_), actual_size_(s.actual_size_) {
    if (this == &s) return;
    delete[] data_;
    data_ = other.data_;
    other.data_ = nullptr;
  }

  swap(ContainerAdaptor &other) {
    std::swap(data_, other.data_);
    std::swap(capacity_, other.capacity_);
    std::swap(actual_size_, other.actual_size_);
  }

 private:
  GrowCapacity(size_type_ new_capacity) {
    if (new_capacity <= capacity_) return;

    value_type_ *buffer = new value_type_[new_capacity];

    for (size_type_ i = 0; i < actual_size_; ++i)
      buffer[i] = std::move(data_[i]);

    delete[] data_;
    data_ = buffer;
    capacity_ = new_capacity;
  }
};

template <typename T>
class Stack : public ContainerAdaptor<T> {
 public:
  using value_type_ = typename ContainerAdaptor<T>::value_type_;
  using reference_ = typename ContainerAdaptor<T>::reference_;
  using const_reference_ = typename ContainerAdaptor<T>::const_reference_;
  using size_type_ = typename ContainerAdaptor<T>::size_type_;

  stack() : ContainerAdaptor<T>() {}
  stack(std::initializer_list<value_type_> const &items)
      : ContainerAdaptor<T>(items) {}
  stack(const ContainerAdaptor<T> &other) : ContainerAdaptor<T>(other) {}
  stack(ContainerAdaptor<T> &&other) : ContainerAdaptor<T>(std::move(other)) {}

  const_reference top() const { return this->data_[this->actual_size_ - 1]; }

  // inserts an element at the top
  void push(const_reference_ value) override {
    if (this->actual_size_ == this->capacity_) {
      this->GrowCapacity(this->capacity_ + this->capacity_ / 2);
    }
    this->data_[this->actual_size_++] = value;
  }

  // removes the top element
  virtual void pop() override {
    if (this->actual_size_ == 0) return;
    this->actual_size_--;
  }
};

template <typename T>
class Queue : public ContainerAdaptor<T> {
 public:
  using value_type_ = typename ContainerAdaptor<T>::value_type_;
  using reference_ = typename ContainerAdaptor<T>::reference_;
  using const_reference_ = typename ContainerAdaptor<T>::const_reference_;
  using size_type_ = typename ContainerAdaptor<T>::size_type_;

  queue() : ContainerAdaptor<T>() {}
  queue(std::initializer_list<value_type_> const &items)
      : ContainerAdaptor<T>(items) {}
  queue(const ContainerAdaptor<T> &other) : ContainerAdaptor<T>(other) {}
  queue(ContainerAdaptor<T> &&other) : ContainerAdaptor<T>(std::move(other)) {}

  // access the first element
  const_reference_ front() { return this->data_[0]; }
  const_reference_ back() { return this->data_[this->actual_size_ - 1]; }

  void push(const_reference_ value) override {
    if (this->actual_size_ == this->capacity_) {
      this->GrowCapacity(this->capacity_ + this->capacity_ / 2);
    }
    this->data_[this->actual_size_++] = value;
  }

  // removes the first element
  void pop() override {
    if (this->actual_size_ == 0) return;
    for (size_type_ i = 1; i < this->actual_size_; ++i) {
      this->data_[i - 1] = std::move(this->data_[i]);
    }
    this->actual_size_--;
  }
};
}  // namespace s21

#endif  // CPP2_S21CONTAINERS_COMPONENTS_S21_STACK_H_