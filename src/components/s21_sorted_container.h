#ifndef SRC_COMPONENTS_S21_SORTED_CONTAINER_H
#define SRC_COMPONENTS_S21_SORTED_CONTAINER_H

#include <iostream>

template <typename Key, typename T>
class sorted_container {
 protected:
  struct tnode {
    Key key_;
    T value_;
    struct tnode *parent_;
    struct tnode *left_;
    struct tnode *right_;

    tnode(Key key, T value) : key_{key}, value_{value} {
      parent_ = nullptr;
      left_ = nullptr;
      right_ = nullptr;
    }
  };  // end struct

  using size_type = size_t;
  tnode *root_;
  size_type counter;

  sorted_container() {
    root_ = nullptr;
    counter = 0;
  }

  ~sorted_container() { destroy_tree(root_); }

  void destroy_tree(tnode *my_tree) {
    if (my_tree) {
      destroy_tree(my_tree->left_);
      destroy_tree(my_tree->right_);
      delete my_tree;
      my_tree = nullptr;
    }
  }

  bool tree_empty() {
    bool result = true;
    if (root_) {
      result = false;
    }
    return result;
  }

  void count_nodes(tnode *my_tree) {
    // std::cout << "counter = " << counter << std::endl;
    if (my_tree) {
      counter++;
      count_nodes(my_tree->left_);
      count_nodes(my_tree->right_);
    }
  }

  tnode *insert(tnode *my_tree, Key key, T value) {
    if (my_tree == nullptr) {
      tnode *temp = new tnode(key, value);
      std::cout << "NEW ";
      print_struct(temp);
      return temp;
    }
    if (key < my_tree->key_) {
      std::cout << "LEFT: " << key << " < " << my_tree->key_ << std::endl;
      my_tree->left_ = insert(my_tree->left_, key, value);
      my_tree->left_->parent_ = my_tree;
      std::cout << "LEFT ";
      print_struct(my_tree->left_);
    } else if (key > my_tree->key_) {
      std::cout << "RIGHT: " << key << " > " << my_tree->key_ << std::endl;
      my_tree->right_ = insert(my_tree->right_, key, value);
      my_tree->right_->parent_ = my_tree;
      std::cout << "RIGHT ";
      print_struct(my_tree->right_);
    }
    // print_struct(my_tree);
    return my_tree;
  }

  // sorted_container(const sorted_container &other) {
  //   destroy_tree(root_);
  //   if (other.root_) {
  //     root_ = copy_tree(other.root_, nullptr);
  //   }
  // }

  tnode *copy_tree(tnode *source, tnode *parent) {
    if (source == nullptr) {
      return nullptr;
    }
    tnode *temp = new tnode(source->key_, source->value_);
    temp->parent_ = parent;
    temp->left_ = copy_tree(source->left_, temp);
    temp->right_ = copy_tree(source->right_, temp);
    return temp;
  }

  void print_struct(tnode *tree) {
    if (tree == nullptr) {
      std::cout << "tnode = null" << std::endl;
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

  void print_tree() {
    std::cout << "---------------------" << std::endl;
    std::cout << "TREE: ";
    print_helper(root_);
    std::cout << std::endl;
  }

  void print_helper(tnode *my_tree) {
    if (my_tree) {
      print_helper(my_tree->left_);
      std::cout << my_tree->value_ << " ";
      print_helper(my_tree->right_);
    }
  }

  // size_t counter_nodes(tnode *tree)

};  // end class

#endif