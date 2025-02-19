// 1) Related header
#include "components/s21_stack_queue.h"
// 2) C system headers
// 3) C++ standard library headers
// 4) other libraries' headers
// 5) project's headers.
#include "s21_containers.h"

namespace s21 {

template <typename T>
ContainerAdaptor<T>::ContainerAdaptor()
    : data_(new value_type_[kDefaultCapacity]),
      capacity_(kDefaultCapacity),
      top_index_(0){};

template <typename T>
ContainerAdaptor<T>::ContainerAdaptor(
    std::initializer_list<value_type_> const &items) {
  data_ = new value_type_[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    data_[i] = *it;
    i++;
  }
  top_index_ = items.size();
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
ContainerAdaptor<T>::ContainerAdaptor(ContainerAdaptor &&s)
    : capacity_(s.capacity_), top_index_(s.top_index_) {
  if (this == &s) return;
  delete[] data_;
  data_ = other.data_;
  other.data_ = nullptr;
}

template <typename T>
ContainerAdaptor<T>::operator=(ContainerAdaptor && s)
    : capacity_(s.capacity_), top_index_(s.top_index_) {
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
}  // namespace s21
