#ifndef SRC_COMPONENTS_S21_SET_H
#define SRC_COMPONENTS_S21_SET_H

#include "s21_sorted_container.h"

namespace s21 {
template <typename Key>
class Set : public SortedContainer<Key, Key> {
 private:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  // using iterator = BinaryTree::iterator;
  // using const_iterator = BinaryTree::const_iterator;
  using size_type = size_t;

 public:
  Set() : SortedContainer<key_type, value_type>() {};
  Set(std::initializer_list<value_type> const &items)
      : SortedContainer<key_type, value_type>() {
    for (auto num : items) {
      std::cout << num << std::endl;
      this->root_ = this->insert(this->root_, num, num);
    }
  }
  Set(const Set &s) {
    this->destroy_tree(this->root_);
    if (s.root_) {
      this->root_ = this->copy_tree(s.root_, nullptr);
    }
  };
  Set(Set &&s);  // move constructor
  ~Set() = default;
  //   operator=(Set && s);

  size_type size() {
    this->print_tree();
    this->count_nodes(this->root_);
    return this->counter;
  }

  bool empty() { return this->tree_empty(); }
};

}  // namespace s21

#endif