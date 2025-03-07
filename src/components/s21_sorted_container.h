#ifndef COMPONENTS_S21_SORTED_CONTAINER_H
#define COMPONENTS_S21_SORTED_CONTAINER_H

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
    Node *current_ = nullptr;

   public:
    const_iterator(Node *cur_node) : current_(cur_node) {}
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

    bool operator!=(const const_iterator &other) const {
      return !(*this == other);
    }
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

  // void Erase(const_iterator pos) {
  //   if (pos == nullptr) {
  //     return;
  //   }
  //   std::cout << "Delete: " << pos->key_ << std::endl;
  //   Node *parent_erase = pos->parent_;
  //   Node *new_root = nullptr;
  //   if (pos->left_) {
  //     std::cout << "Delete: left" << std::endl;
  //     new_root = pos->left_;
  //     if (pos->right_) {
  //       Node *current = pos->left_;
  //       Node *parent = nullptr;
  //       while (current) {
  //         parent = current;
  //         current = current->right_;
  //       }
  //       parent->right_ = pos->right_;
  //     }
  //   } else if (pos->right_) {
  //     std::cout << "Delete: right" << std::endl;
  //     new_root = pos->right_;
  //   } else if (parent_erase) {
  //     if (pos->key_ < parent_erase->key_) {
  //       parent_erase->left_ = EraseNode(parent_erase->left_);
  //     } else {
  //       std::cout << "Delete: parent" << std::endl;
  //       parent_erase->right_ = EraseNode(parent_erase->right_);
  //     }
  //   } else {
  //     root_ = EraseNode(root_);
  //   }
  //   Node *node_erase = nullptr;
  //   if (new_root && parent_erase) {
  //     node_erase = new_root->parent_;
  //     new_root->parent_ = parent_erase;
  //     if (new_root->key_ < parent_erase->key_) {
  //       parent_erase->left_ = new_root;
  //     } else {
  //       parent_erase->right_ = new_root;
  //     }
  //   } else if (new_root && !parent_erase) {
  //     node_erase = root_;
  //     root_ = new_root;
  //   }
  //   EraseNode(node_erase);
  // }

  void AddSubtree(Node *subroot) {
    if (!subroot) {
      return;
    }
    AddNode(subroot->key_, subroot->value_);
    AddSubtree(subroot->left_);
    AddSubtree(subroot->right_);
  }

  /**
   * 1) Determine which child (may be nullptr) becomes the "main" child
   *
   * 2) If the node had two children, the "other" child is whichever is
   * not'main_child'
   *
   * 3) If current node is on the left side of its parent, each
   * of his children will also go to the left and vice versa
   *
   * 4) If we are erasing the root, make main_child the new root
   *
   * 5) If there is another child, traverse its descendants and add each one
   *
   * 6) If no children exist and this node is not root, simply remove it from
   * parent
   *
   * 7) If erasing a leaf that is root, tree becomes empty
   *
   * 8) Finally, erase the current node from memory
   */
  void Erase(const_iterator pos) {
    if (pos == nullptr) return;

    Node *parent_of_erased = pos->parent_;
    Node *left_child = pos->left_;
    Node *right_child = pos->right_;

    Node *main_child = (left_child ? left_child : right_child);
    Node *other_child =
        (left_child && right_child)
            ? (main_child == left_child ? right_child : left_child)
            : nullptr;

    if (main_child) {
      main_child->parent_ = EraseNode(main_child->parent_);
      if (parent_of_erased) {
        if (pos->key_ < parent_of_erased->key_) {
          parent_of_erased->left_ = main_child;
        } else {
          parent_of_erased->right_ = main_child;
        }
        main_child->parent_ = parent_of_erased;
      } else {
        root_ = main_child;
      }

      if (other_child) {
        AddSubtree(other_child);
      }
    } else {
      if (parent_of_erased) {
        if (pos->key_ < parent_of_erased->key_) {
          parent_of_erased->left_ = EraseNode(parent_of_erased->left_);
        } else {
          parent_of_erased->right_ = EraseNode(parent_of_erased->right_);
        }
      } else {
        root_ = EraseNode(root_);
      }
    }
  }

  Node *EraseNode(Node *current) {
    if (current) {
      delete current;
    }
    return nullptr;
  }

  const_iterator FindNode(Node *current, const Key &key) {
    const_iterator result = const_iterator(root_);
    if (key < current->key_) {
      result = FindNode(current->left_, key);
    } else if (key > current->key_) {
      result = FindNode(current->right_, key);
    } else {
      result = const_iterator(current);
    }
    return result;
  }

  bool Contains(Node *current, const Key &key) {
    if (current == nullptr) {
      return false;
    }
    bool result = false;
    if (key < current->key_) {
      result = Contains(current->left_, key);
    } else if (key > current->key_) {
      result = Contains(current->right_, key);
    } else {
      result = true;
    }
    return result;
  }

  void Swap(Node *other_root) {
    Node *left_child = this->root_->left_;
    if (left_child) left_child->parent_ = other_root->right_;
    Node *right_child = this->root_->right_;
    if (right_child) right_child->parent_ = other_root->left_;
    std::swap(this->root_, other_root);
  }

  void Merge(Node *other) {
    if (other == nullptr) {
      std::cout << "return" << std::endl;
      return;
    }
    std::cout << "Merge: " << other->key_ << std::endl;
    auto move_node = AddNode(other->key_, other->value_);
    if (move_node.second)
      std::cout << "true" << std::endl;
    else
      std::cout << "false" << std::endl;
    Merge(other->left_);
    Merge(other->right_);
    if (move_node.second) {
      std::cout << "********SET*********" << std::endl;
      PrintTree();
      std::cout << "********OTHER*********" << std::endl;
      Node *temp = other;
      while (temp->parent_) {
        temp = temp->parent_;
      }
      PrintHelper(temp);
      Erase(const_iterator(other));
    }
  }

  // void Merge(Node *other) {
  //   if (other == nullptr) {
  //     std::cout << "return" << std::endl;
  //     return;
  //   }
  //   std::cout << "Merge: " << other->key_ << std::endl;
  //   bool move_node = MergeHelper(root_, other, nullptr);
  //   if (move_node)
  //     std::cout << "true" << std::endl;
  //   else
  //     std::cout << "false" << std::endl;
  //   Merge(other->left_);
  //   Merge(other->right_);
  //   if (move_node) {
  //     Erase(const_iterator(other));
  //   }
  // }

  // bool MergeHelper(Node *current, Node *other, Node *parent) {
  //   if (current == nullptr) {
  //     Node *new_node = new Node(other->key_, other->value_);
  //     new_node->parent_ = parent;
  //     if
  //       return true;
  //   }
  //   bool result = false;
  //   // std::cout << "P1" << std::endl;
  //   if (other->key_ < current->key_) {
  //     std::cout << other->key_ << " < " << current->key_ << std::endl;
  //     result = MergeHelper(current->left_, other, current);
  //     if (result) {
  //       current->left_ = other;
  //     }
  //   } else if (other->key_ > current->key_) {
  //     std::cout << other->key_ << " > " << current->key_ << std::endl;
  //     result = MergeHelper(current->right_, other, current);
  //     if (result) {
  //       current->right_ = other;
  //     }
  //   }
  //   return result;
  // }

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
      PrintStruct(my_tree);
      PrintHelper(my_tree->left_);
      // std::cout << my_tree->value_ << " ";
      PrintHelper(my_tree->right_);
    }
  }
};  // class BinaryTree

#endif  // COMPONENTS_S21_SORTED_CONTAINER_H