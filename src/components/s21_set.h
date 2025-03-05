#ifndef SRC_COMPONENTS_S21_SET_H
#define SRC_COMPONENTS_S21_SET_H

#include "s21_sorted_container.h"

namespace s21 {
template <typename Key>
class set : public BinaryTree<Key, Key> {
 private:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using const_iterator =
      typename BinaryTree<key_type, value_type>::const_iterator;
  using size_type = size_t;

 public:
  set() : BinaryTree<key_type, value_type>() {};
  set(std::initializer_list<value_type> const &items)
      : BinaryTree<key_type, value_type>() {
    for (auto num : items) {
      std::cout << num << " ";
      this->AddNode(num, num);
    }
    std::cout << std::endl;
  }
  set(const set &s) : BinaryTree<key_type, value_type>() {
    this->DestroyTree(this->root_);
    this->root_ = this->CopyTree(s.root_, nullptr);
  };
  set(set &&s) noexcept : BinaryTree<key_type, value_type>() {
    this->root_ = s.root_;
    s.root_ = nullptr;
  }
  ~set() {
    this->DestroyTree(this->root_);
    this->root_ = nullptr;
  }
  set &operator=(const set &s) {
    if (this != &s) {
      this->DestroyTree(this->root_);
      this->root_ = this->CopyTree(s.root_, nullptr);
    }
    return *this;
  }

  set &operator=(set &&s) noexcept {
    if (this != &s) {
      this->DestroyTree(this->root_);
      this->root_ = s.root_;
      s.root_ = nullptr;
    }
    return *this;
  }

  const_iterator begin() const {
    return BinaryTree<key_type, value_type>::Begin();
  }
  const_iterator end() const { return BinaryTree<key_type, value_type>::End(); }

  size_type size() {
    this->counter_ = 0;
    this->CountNodes(this->root_);
    return this->counter_;
  }

  bool empty() { return this->TreeEmpty(); }

  void clear() {
    this->DestroyTree(this->root_);
    this->root_ = nullptr;
  }

  std::pair<const_iterator, bool> insert(const value_type &value) {
    return this->AddNode(value, value);
  }

  void erase(const_iterator pos) { this->Erase(pos, this->root_); }
  const_iterator find(const key_type &key) {
    return this->FindNode(this->root_, key);
  }

  bool contains(const key_type &key) {
    return this->Contains(this->root_, key);
  }
  void swap(set &other) { std::swap(this->root_, other.root_); }
  void merge(set &other) { this->Merge(other.root_); }
  size_type max_size() { return this->MaxSize(); }
};

}  // namespace s21

#endif