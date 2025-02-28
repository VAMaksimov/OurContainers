#ifndef CPP2_S21_CONTAINERS_COMPONENTS_S21_SORTED_CONTAINER_H
#define CPP2_S21_CONTAINERS_COMPONENTS_S21_SORTED_CONTAINER_H

#include <iostream>

namespace s21 {
template <typename Key, typename T>
class SortedContainer {
 protected:
  struct TNode {
    Key key_;
    T value_;
    struct TNode *parent_;
    struct TNode *left_;
    struct TNode *right_;

    TNode(Key key, T value) : key_{key}, value_{value} {
      parent_ = nullptr;
      left_ = nullptr;
      right_ = nullptr;
    }
  };  // struct TNode

  TNode *root_;
  using size_type_ = unsigned long long;
  size_type_ counter_;

  SortedContainer();
  ~SortedContainer() { DestroyTree(root_); }

  void DestroyTree(TNode *my_tree);
  bool TreeIsEmpty() { return root_ == nullptr; }
  void CountNodes(TNode *my_tree);

  TNode *Insert(TNode *my_tree, Key key, T value);
  TNode *CopyTree(TNode *source, TNode *parent);

  void PrintStruct(TNode *tree);
  void PrintTree();
  void PrintHelper(TNode *my_tree);

  // SortedContainer(const SortedContainer &other) {
  //   DestroyTree(root_);
  //   if (other.root_) {
  //     root_ = CopyTree(other.root_, nullptr);
  //   }
  // }

  // size_t counter_nodes(TNode *tree)
};  // class SortedContainer

template <typename Key, typename T>
SortedContainer<Key, T>::SortedContainer() {
  root_ = nullptr;
  counter_ = 0;
}

template <typename Key, typename T>
void SortedContainer<Key, T>::DestroyTree(TNode *my_tree) {
  if (my_tree == nullptr) return;
  DestroyTree(my_tree->left_);
  DestroyTree(my_tree->right_);
  delete my_tree;
  my_tree = nullptr;
}

template <typename Key, typename T>
void SortedContainer<Key, T>::CountNodes(TNode *my_tree) {
  if (my_tree == nullptr) return;
  // std::cout << "counter_ = " << counter_ << std::endl;
  counter_++;
  CountNodes(my_tree->left_);
  CountNodes(my_tree->right_);
}

template <typename Key, typename T>
// The typename keyword is necessary to tell the compiler that TNode is a type
// rather than a variable
typename SortedContainer<Key, T>::TNode *SortedContainer<Key, T>::Insert(
    TNode *my_tree, Key key, T value) {
  if (my_tree == nullptr) {
    TNode *temp = new TNode(key, value);
    std::cout << "NEW ";
    PrintStruct(temp);
    return temp;
  }
  if (key < my_tree->key_) {
    std::cout << "LEFT: " << key << " < " << my_tree->key_ << std::endl;
    my_tree->left_ = Insert(my_tree->left_, key, value);
    my_tree->left_->parent_ = my_tree;
    std::cout << "LEFT ";
    PrintStruct(my_tree->left_);
  } else if (key > my_tree->key_) {
    std::cout << "RIGHT: " << key << " > " << my_tree->key_ << std::endl;
    my_tree->right_ = Insert(my_tree->right_, key, value);
    my_tree->right_->parent_ = my_tree;
    std::cout << "RIGHT ";
    PrintStruct(my_tree->right_);
  }
  // PrintStruct(my_tree);
  return m
}

template <typename Key, typename T>
typename SortedContainer<Key, T>::TNode *SortedContainer<Key, T>::CopyTree(
    TNode *source, TNode *parent) {
  if (source == nullptr) return nullptr;
  TNode *temp = new TNode(source->key_, source->value_);
  temp->parent_ = parent;
  temp->left_ = CopyTree(source->left_, temp);
  temp->right_ = CopyTree(source->right_, temp);
  return temp;
}

template <typename Key, typename T>
void SortedContainer<Key, T>::PrintStruct(TNode *tree) {
  if (tree == nullptr) {
    std::cout << "TNode = null" << std::endl;
    return;
  }
  std::cout << "Structure:" << std::endl;
  std::cout << "key = " << tree->key_ << std::endl;
  std::cout << "value = " << tree->value_ << std::endl;
  std::cout << "&parent = " << tree->parent_ << std::endl;
  std::cout << "&left = " << tree->left_ << std::endl;
  std::cout << "&right = " << tree->right_ << std::endl;
  std::cout << "---------------------" << std::endl;
}

template <typename Key, typename T>
void SortedContainer<Key, T>::PrintTree() {
  std::cout << "---------------------" << std::endl;
  std::cout << "TREE: ";
  PrintHelper(root_);
  std::cout << std::endl;
}

template <typename Key, typename T>
void SortedContainer<Key, T>::PrintHelper(TNode *my_tree) {
  if (my_tree == nullptr) return;
  PrintHelper(my_tree->left_);
  std::cout << my_tree->value_ << " ";
  PrintHelper(my_tree->right_);
}
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_COMPONENTS_S21_SORTED_CONTAINER_H