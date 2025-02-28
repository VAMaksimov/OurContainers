#ifndef SRC_COMPONENTS_S21_SORTED_CONTAINER_H
#define SRC_COMPONENTS_S21_SORTED_CONTAINER_H

#include <iostream>
#include <utility>

template <typename Key, typename T>
class BinaryTree {
 protected:
  struct Node {
    const Key key_;
    T value_;
    struct Node *parent_;
    struct Node *left_;
    struct Node *right_;

    Node(Key key, T value) : key_{key}, value_{value} {
      parent_ = nullptr;
      left_ = nullptr;
      right_ = nullptr;
    }
  };  // end struct Node

  using size_type = size_t;
  Node *root_;
  size_type counter_;

  BinaryTree() {
    root_ = nullptr;
    counter_ = 0;
  }

  ~BinaryTree() {
    DestroyTree(root_);
    root_ = nullptr;
  }

 public:
  class iterator {
   private:
    Node *current_;

   public:
    iterator(Node *cur_node = nullptr) : current_(cur_node) {}
    const Key &operator*() { return current_->key_; }
    // Node *operator->() { return current_; }

    // Префиксный инкремент
    iterator &operator++() {
      if (current_->right_) {
        current_ = current_->right_;
        while (current_->left_) current_ = current_->left_;
      } else {
        Node *parent = current_->parent_;
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
        Node *parent = current_->parent_;
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
  };  // end class iterator

  class const_iterator {
   private:
    const Node *current_;

   public:
    const_iterator(const Node *cur_node = nullptr) : current_(cur_node) {}
    const Key &operator*() const { return current_->key_; }

    // Префиксный инкремент
    const_iterator &operator++() {
      if (current_->right_) {
        current_ = current_->right_;
        while (current_->left_) current_ = current_->left_;
      } else {
        const Node *parent = current_->parent_;
        while (parent && current_ == parent->right_) {
          current_ = parent;
          parent = parent->parent_;
        }
        current_ = parent;
      }
      return *this;
    }

    // Постфиксный инкремент
    const_iterator operator++(int) {
      const_iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    // Префиксный декремент
    const_iterator &operator--() {
      if (current_->left_) {
        current_ = current_->left_;
        while (current_->right_) current_ = current_->right_;
      } else {
        const Node *parent = current_->parent_;
        while (parent && current_ == parent->left_) {
          current_ = parent;
          parent = parent->parent_;
        }
        current_ = parent;
      }
      return *this;
    }

    // Постфиксный декремент
    const_iterator operator--(int) {
      const_iterator tmp(*this);
      --(*this);
      return tmp;
    }

    // Операторы сравнения
    bool operator==(const const_iterator &other) const {
      return current_ == other.current_;
    }

    bool operator!=(const const_iterator &other) const {
      return !(*this == other);
    }
  };  // end class const_iterator

  iterator Begin() {
    Node *my_tree = root_;
    while (my_tree && my_tree->left_) my_tree = my_tree->left_;
    return iterator(my_tree);
  }

  iterator End() { return iterator(nullptr); }

  const_iterator Begin() const {
    Node *my_tree = root_;
    while (my_tree && my_tree->left_) my_tree = my_tree->left_;
    return const_iterator(my_tree);
  }

  const_iterator End() const { return const_iterator(nullptr); }

 protected:
  void DestroyTree(Node *my_tree) {
    if (my_tree != nullptr) {
      DestroyTree(my_tree->left_);
      DestroyTree(my_tree->right_);
      delete my_tree;
      my_tree = nullptr;
    }
  }

  bool TreeEmpty() {
    bool result = true;
    if (root_ != nullptr) {
      result = false;
    }
    return result;
  }

  void CountNodes(Node *my_tree) {
    if (my_tree) {
      counter_++;
      CountNodes(my_tree->left_);
      CountNodes(my_tree->right_);
    }
  }

  std::pair<iterator, bool> AddNode(const Key &key, const T &value) {
    if (root_ == nullptr) {
      root_ = new Node(key, value);
      return {root_, true};
    }
    Node *current = root_;
    Node *parent = nullptr;
    while (current != nullptr) {
      parent = current;
      if (key < current->key_) {
        current = current->left_;
      } else if (key > current->key_) {
        current = current->right_;
      } else {
        return {current, false};
      }
    }
    Node *new_node = new Node(key, value);
    new_node->parent_ = parent;
    if (key < parent->key_) {
      parent->left_ = new_node;
    } else {
      parent->right_ = new_node;
    }
    return {new_node, true};
  }

  void Erase(iterator pos) {
    if (pos == nullptr) {
      return;
    }
    if (pos->left_) {
      std::cout << "HELLO" << std::endl;
    }
  }

  Node *CopyTree(Node *source, Node *parent) {
    if (source == nullptr) {
      return nullptr;
    }
    Node *temp = new Node(source->key_, source->value_);
    temp->parent_ = parent;
    temp->left_ = CopyTree(source->left_, temp);
    temp->right_ = CopyTree(source->right_, temp);
    return temp;
  }

  void PrintStruct(Node *tree) {
    if (tree == nullptr) {
      std::cout << "Node = null" << std::endl;
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

  void PrintTree() {
    std::cout << "---------------------" << std::endl;
    std::cout << "TREE: ";
    PrintHelper(root_);
    std::cout << std::endl;
  }

  void PrintHelper(Node *my_tree) {
    if (my_tree) {
      PrintHelper(my_tree->left_);
      std::cout << my_tree->value_ << " ";
      PrintHelper(my_tree->right_);
    }
  }
};  // end class

#endif