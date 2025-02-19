#ifndef CPP2_S21CONTAINERS_COMPONENTS_S21_STACK_H_
#define CPP2_S21CONTAINERS_COMPONENTS_S21_STACK_H_

namespace s21 {
template <typename T>
class ContainerAdaptor : public Container<T> {
 public:
  using value_type_ = typename Container<T>::value_type_;
  using reference_ = typename Container<T>::reference_;
  using const_reference_ = typename Container<T>::const_reference_;
  using size_type_ = typename Container<T>::size_type_;

  // Main funcs
  ContainerAdaptor()
      : data_(new value_type_[kDefaultCapacity]),
        capacity_(kDefaultCapacity),
        top_index_(0) {}
  ~ContainerAdaptor() { delete[] data_; }

  ContainerAdaptor(std::initializer_list<value_type> const &items) {
    data_ = new value_type_[items.size()];
    int i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
      data_[i] = *it;
      i++;
    }
    top_index_ = items.size();
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

  ContainerAdaptor(ContainerAdaptor &&s) : capacity_(s.capacity_), top_index_(s.top_index_) {
    if (this == &s) return;
    delete[] data_;
    data_ = other.data_;
    other.data_ = nullptr;
  }

  operator=(ContainerAdaptor && s) : capacity_(s.capacity_), top_index_(s.top_index_) {
    if (this == &s) return;
    delete[] data_;
    data_ = other.data_;
    other.data_ = nullptr;
  }

  // Other funcs
  virtual void push(const_reference_ value) = 0;
  virtual void pop() = 0;

  void swap(ContainerAdaptor &other) {
    std::swap(data_, other.data_);
    std::swap(capacity_, other.capacity_);
    std::swap(top_index_, other.top_index_);
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
  size_type_ capacity_;
  size_type_ top_index_;
};

template <typename T>
class Stack : public ContainerAdaptor<T> {
 public:
  using value_type_ = typename ContainerAdaptor<T>::value_type_;
  using reference_ = typename ContainerAdaptor<T>::reference_;
  using const_reference_ = typename ContainerAdaptor<T>::const_reference_;
  using size_type_ = typename ContainerAdaptor<T>::size_type_;
 
  // Main funcs
  Stack() : ContainerAdaptor<T>() {}
  ~Stack() : 
};
}

#endif  // CPP2_S21CONTAINERS_COMPONENTS_S21_STACK_H_