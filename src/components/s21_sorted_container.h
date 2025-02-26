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

  ~sorted_container() {
    destroy_tree(root_);
    root_ = nullptr;
  }

  class iterator {
   private:
    tnode *current_;

   public:
    iterator(tnode *cur_node = nullptr) : current_(cur_node) {}
    // Iterator(tnode *cur_node) {}
    Key &operator*() { return current_->key_; }
    tnode *operator->() { return current_; }
    // Iterator &operator--() {
    //   if(current_->parent_ == nullptr) {
    //     return current_;
    //   }
    //   return current_->parent_;
    // }
    // Iterator &operator++() {
    //   tnode *ptr = current_->right_;
    //   if(current_->right_ == nullptr)
    // }
    // bool operator==(const Iterator &other) const;
    // bool operator!=(const Iterator &other) const;

    // Де референс
    // std::pair<Key, T> &operator*() {
    //   return *reinterpret_cast<std::pair<Key, T> *>(current_);
    // }

    // // Стрелочная нотация
    // std::pair<Key, T> *operator->() {
    //   return reinterpret_cast<std::pair<Key, T> *>(current_);
    // }

    // Префиксный инкремент
    iterator &operator++() {
      if (current_->right_) {
        current_ = current_->right_;
        while (current_->left_) current_ = current_->left_;
      } else {
        tnode *parent = current_->parent_;
        while (parent && current_ == parent->right_) {
          current_ = parent;
          parent = parent->parent_;
        }
        current_ = parent;
      }
      return *this;
    }

    // Постфиксный инкремент
    iterator operator++(int) {
      iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    // Префиксный декремент
    iterator &operator--() {
      if (current_->left_) {
        current_ = current_->left_;
        while (current_->right_) current_ = current_->right_;
      } else {
        tnode *parent = current_->parent_;
        while (parent && current_ == parent->left_) {
          current_ = parent;
          parent = parent->parent_;
        }
        current_ = parent;
      }
      return *this;
    }

    // Постфиксный декремент
    iterator operator--(int) {
      iterator tmp(*this);
      --(*this);
      return tmp;
    }

    // Операторы сравнения
    bool operator==(const iterator &other) const {
      return current_ == other.current_;
    }

    bool operator!=(const iterator &other) const { return !(*this == other); }
  };

 public:
  // Методы для получения итераторов
  iterator begin() {
    tnode *node = root_;
    while (node && node->left_) node = node->left_;
    return iterator(node);
  }

  iterator end() { return iterator(nullptr); }

  // Константные версии
  const iterator begin() const {
    tnode *node = root_;
    while (node && node->left_) node = node->left_;
    return iterator(node);
  }

  const iterator end() const { return iterator(nullptr); }
  // Iterator Begin();
  // Iterator End();
  // const Iterator Begin() const;
  // const Iterator End() const;

  void destroy_tree(tnode *my_tree) {
    if (my_tree != nullptr) {
      destroy_tree(my_tree->left_);
      destroy_tree(my_tree->right_);
      delete my_tree;
      my_tree = nullptr;
    }
  }

  bool tree_empty() {
    bool result = true;
    if (root_ != nullptr) {
      result = false;
    }
    return result;
  }

  void count_nodes(tnode *my_tree) {
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
    return my_tree;
  }

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
};  // end class

#endif