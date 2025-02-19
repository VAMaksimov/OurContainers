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

  bool empty() const override { return top_index_ == 0; }
  size_type_ size() const override { return top_index_; }

 private:
  const size_type_ kDefaultCapacity = 16;

  void GrowCapacity(size_type_ new_capacity);

  value_type_ *data_;
  size_type_ capacity_;
  size_type_ top_index_;

 public:
  operator=(ContainerAdaptor && s)
      : capacity_(s.capacity_), top_index_(s.top_index_) {
    if (this == &s) return;
    delete[] data_;
    data_ = other.data_;
    other.data_ = nullptr;
  }
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
};
}  // namespace s21

#endif  // CPP2_S21CONTAINERS_COMPONENTS_S21_STACK_H_