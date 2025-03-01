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
  class const_iterator {
   private:
    Node *current_;

   public:
    const_iterator(Node *cur_node = nullptr) : current_(cur_node) {}
    const Key &operator*() const { return current_->key_; }
    const Node *operator->() const { return current_; }

    // Префиксный инкремент
    const_iterator &operator++() {
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
    const_iterator operator--(int) {
      const_iterator tmp(*this);
      --(*this);
      return tmp;
    }

    // Операторы сравнения
    bool operator==(const const_iterator &other) const {
      return current_ == other.current_;
    }

    bool operator!=(const const_iterator &other) const { return !(*this == other); }
  };  // end class const_iterator

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

  std::pair<const_iterator, bool> AddNode(const Key &key, const T &value) {
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

  void Erase(const_iterator pos) {
    if (pos == nullptr) {
      return;
    }
    Node *parent_erase = pos->parent_;
    Node *node_erase = nullptr;
    Node *new_root = nullptr;
    if (pos->left_) {
      new_root = pos->left_;
      if (pos->right_) {
        Node *current = pos->left_;
        Node *parent = nullptr;
        while (current) {
          parent = current;
          current = current->right_;
        }
        parent->right_ = pos->right_;
      }
    } else if (pos->right_) {
      new_root = pos->right_;
    } else if (parent_erase) {
      if (pos->key_ < parent_erase->key_) {
        node_erase = parent_erase->left_;
        parent_erase->left_ = EraseNode(parent_erase->left_);
      } else {
        node_erase = parent_erase->right_;
        parent_erase->right_ = EraseNode(parent_erase->right_);
      }
    } else {
      node_erase = root_;
      root_ = EraseNode(root_);
    }
    if (new_root && parent_erase) {
      node_erase = new_root->parent_;
      new_root->parent_ = parent_erase;
      if (new_root->key_ < parent_erase->key_) {
        parent_erase->left_ = new_root;
      } else {
        parent_erase->right_ = new_root;
      }
    } else if (new_root && !parent_erase) {
      node_erase = root_;
      root_ = new_root;
    }
    EraseNode(node_erase);
  }

  Node *EraseNode(Node *current) {
    if (current) {
      delete current;
    }
    return nullptr;
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