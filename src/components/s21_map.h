#ifndef SRC_COMPONENTS_S21_SET_H
#define SRC_COMPONENTS_S21_SET_H

#include "s21_sorted_container.h"

namespace s21 {
template <typename Key, typename Value>
class map : public BinaryTree<Key, Value> {
 private:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using const_iterator =
      typename BinaryTree<key_type, value_type>::const_iterator;
  using size_type = size_t;

 public:
  map() : BinaryTree<key_type, mapped_type>(){};
  map(std::initializer_list<value_type> const &key_value_pairs) {
    for (const auto &kvp : key_value_pairs) this->insert(kvp);
  }
  map(const map &s) : BinaryTree<key_type, mapped_type>() {
    this->DestroyTree(this->root_);
    this->root_ = this->CopyTree(s.root_, nullptr);
  };
  map(map &&s) noexcept : BinaryTree<key_type, mapped_type>() {
    this->root_ = s.root_;
    s.root_ = nullptr;
  }
  ~map() {
    this->DestroyTree(this->root_);
    this->root_ = nullptr;
  }
  map &operator=(const map &s) {
    if (this != &s) {
      this->DestroyTree(this->root_);
      this->root_ = this->CopyTree(s.root_, nullptr);
    }
    return *this;
  }

  map &operator=(map &&s) noexcept {
    if (this != &s) {
      this->DestroyTree(this->root_);
      this->root_ = s.root_;
      s.root_ = nullptr;
    }
    return *this;
  }

  mapped_type &at(const key_type &key) { return this->FindNode(key)->value_; }

  mapped_type &operator[](const key_type &key) {
    return this->FindNode(key)->value_;
  }

  const_iterator begin() const {
    return BinaryTree<key_type, mapped_type>::Begin();
  }
  const_iterator end() const {
    return BinaryTree<key_type, mapped_type>::End();
  }

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

  std::pair<const_iterator, bool> insert(const value_type &kvp) {
    return this->AddNode(kvp.first, kvp.second);
  }
  std::pair<const_iterator, bool> insert(const key_type &key,
                                         const mapped_type &value) {
    return this->AddNode(key, value);
  }
  std::pair<const_iterator, bool> insert_or_assign(const key_type &key,
                                                   const mapped_type &value) {
    if (this->contains(key)) {
      this->at(key) = value;
      return {this->find(key), false};
    }
    return this->insert(key, value);
  }

  void erase(const_iterator pos) { this->Erase(pos); }

  bool contains(const key_type &key) { return this->FindNode(key); }
};

}  // namespace s21

#endif