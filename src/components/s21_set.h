#ifndef SRC_COMPONENTS_S21_SET_H
#define SRC_COMPONENTS_S21_SET_H

#include "s21_sorted_container.h"

namespace s21 {
template <typename Key>
class set : public sorted_container<Key, Key> {
 private:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename sorted_container<key_type, value_type>::iterator;
  // using const_iterator =
  //     typename sorted_container<key_type, value_type>::const_iterator;
  using size_type = size_t;

 public:
  set() : sorted_container<key_type, value_type>() {};
  set(std::initializer_list<value_type> const &items)
      : sorted_container<key_type, value_type>() {
    for (auto num : items) {
      std::cout << num << std::endl;
      this->root_ = this->insert(this->root_, num, num);
    }
  }
  set(const set &s) : sorted_container<key_type, value_type>() {
    this->destroy_tree(this->root_);
    this->root_ = this->copy_tree(s.root_, nullptr);
  };
  set(set &&s) noexcept : sorted_container<key_type, value_type>() {
    this->root_ = s.root_;
    s.root_ = nullptr;
  }
  ~set() {
    this->destroy_tree(this->root_);
    this->root_ = nullptr;
  }
  set &operator=(const set &s) {
    if (this != &s) {
      this->destroy_tree(this->root_);
      this->root_ = this->copy_tree(s.root_, nullptr);
    }
    return *this;
  }

  set &operator=(set &&s) noexcept {
    if (this != &s) {
      this->destroy_tree(this->root_);
      this->root_ = s.root_;
      s.root_ = nullptr;
    }
    return *this;
  }

  size_type size() {
    this->counter = 0;
    this->print_tree();
    this->count_nodes(this->root_);
    return this->counter;
  }

  bool empty() { return this->tree_empty(); }

  iterator begin() { return sorted_container<key_type, value_type>::begin(); }
  iterator end() { return sorted_container<key_type, value_type>::end(); }
  iterator begin() const {
    return sorted_container<key_type, value_type>::begin();
  }
  iterator end() const { return sorted_container<key_type, value_type>::end(); }
};

}  // namespace s21

#endif