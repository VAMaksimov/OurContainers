#ifndef S21_CONTAINERS_H_S21_LIST_H
#define S21_CONTAINERS_H_S21_LIST_H

#include "components/s21_sequence_containers.h"

namespace s21 {

template <typename T>
class list : public SequenceContaner<list<T>, T> {
 public:
  // List Member type
  using value_type = typename SequenceContaner<list<T>, T>::value_type;
  using reference = typename SequenceContaner<list<T>, T>::reference;
  using const_reference =
      typename SequenceContaner<list<T>, T>::const_reference;
  using size_type = typename SequenceContaner<list<T>, T>::size_type;

  struct Node_ {
    value_type value;
    Node_* next;
    Node_* prev;

    // Constructor for a dummy node
    explicit Node_(Node_* nextNode = nullptr, Node_* prevNode = nullptr)
        : value(), next(nextNode), prev(prevNode) {}

    // Constructor for a real node
    explicit Node_(value_type val, Node_* nextNode = nullptr,
                   Node_* prevNode = nullptr)
        : value(val), next(nextNode), prev(prevNode) {}
  };

  // List Functions
  list() noexcept;
  explicit list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& other) noexcept;
  list(list&& other) noexcept;
  ~list();

  // Assignment operators
  list<T>& operator=(list<T>&& other) noexcept;
  list<T>& operator=(const list<T>& other) noexcept;

  // Access and modification methods
  Node_* getHead() const { return fake->next; }
  Node_* getTail() const { return fake->prev; }

  // List Iterators
  class ListIterator {
   public:
    ListIterator() = default;
    explicit ListIterator(Node_* node) : current(node) {}
    ListIterator& operator++() {
      current = current->next;
      return *this;
    }
    ListIterator operator++(int) {
      ListIterator temp = *this;
      ++(*this);
      return temp;
    }
    ListIterator& operator--() {
      current = current->prev;
      return *this;
    }
    ListIterator operator--(int) {
      ListIterator temp = *this;
      --(*this);
      return temp;
    }
    reference operator*() { return current->value; }
    bool operator==(const ListIterator& other) const {
      return current == other.current;
    }
    bool operator!=(const ListIterator& other) const {
      return current != other.current;
    }
    Node_* getNode() const { return current; }

   protected:
    Node_* current;
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator() : ListIterator(nullptr) {}
    explicit ListConstIterator(Node_* node) : ListIterator(node) {}
    ListConstIterator(const ListIterator& other) : ListIterator(other) {}
    const_reference operator*() { return this->current->value; }
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  iterator begin() const noexcept { return iterator(fake->next); }
  iterator end() const noexcept { return iterator(fake); }

  // List Element access
  const_reference front() const;
  const_reference back() const;

  // List Capacity
  bool empty() const;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // List Modifiers
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other) noexcept;
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse() noexcept;
  void unique();
  void sort();

 private:
  Node_* fake;
  size_type size_;

  void initFakeNode();

  // Utils
  Node_* createNode(const_reference value, Node_* next, Node_* prev) {
    return new Node_(value, next, prev);
  }
  void copyFrom(const list& other);

  // for merge() and splice()
  void transferNode(iterator pos, list& other, iterator src);
  void appendRemaining(list& other);

  void extractNodes(list& other, Node_*& first, Node_*& last,
                    size_type& movedSize);
  void linkNodes(Node_* posPrev, Node_* posNext, Node_* first, Node_* last,
                 size_type movedSize);
};

/*List Functions*/

template <typename T>
inline void list<T>::initFakeNode() {
  fake = new Node_();
  fake->next = fake;
  fake->prev = fake;
}

template <typename T>
void list<T>::copyFrom(const list& other) {
  for (Node_* current = other.fake->next; current != other.fake;
       current = current->next) {
    push_back(current->value);
  }
}

template <typename T>
list<T>::list() noexcept : size_(0) {
  initFakeNode();
}

template <typename T>
list<T>::list(size_type n) : size_(0) {
  initFakeNode();
  for (size_type i = 0; i < n; ++i) {
    push_back(value_type());
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items) : size_(0) {
  initFakeNode();
  for (const auto& item : items) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(const list& other) noexcept : size_(0) {
  initFakeNode();
  copyFrom(other);
}

template <typename T>
list<T>::list(list&& other) noexcept {
  if (other.fake != nullptr) {
    fake = other.fake;
    size_ = other.size_;
    other.fake = nullptr;
    other.size_ = 0;
    other.initFakeNode();
  }
}

template <typename T>
list<T>::~list() {
  clear();
  delete fake;
}

template <typename T>
list<T>& list<T>::operator=(list<T>&& other) noexcept {
  if (this != &other) {
    clear();
    delete fake;
    if (other.fake != nullptr) {
      fake = other.fake;
      size_ = other.size_;
      other.fake = nullptr;
      other.size_ = 0;
      other.initFakeNode();
    }
  }
  return *this;
}

template <typename T>
list<T>& list<T>::operator=(const list<T>& other) noexcept {
  if (this != &other) {
    clear();
    copyFrom(other);
  }
  return *this;
}

// List Element access
template <typename T>
inline typename list<T>::const_reference list<T>::front() const {
  return fake->next->value;
}

template <typename T>
inline typename list<T>::const_reference list<T>::back() const {
  return fake->prev->value;
}

// List Capacity
template <typename T>
inline bool list<T>::empty() const {
  return size_ == 0;
}

template <typename T>
inline typename list<T>::size_type list<T>::size() const noexcept {
  return size_;
}

template <typename T>
inline typename list<T>::size_type list<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max();
}

/*List Modifiers*/

template <typename T>
void list<T>::clear() noexcept {
  while (fake->next != fake) {
    Node_* temp = fake->next;
    fake->next = temp->next;
    delete temp;
  }
  fake->prev = fake;
  size_ = 0;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node_* posNode = pos.getNode();
  Node_* newNode = createNode(value, posNode, posNode->prev);
  posNode->prev->next = newNode;
  posNode->prev = newNode;
  ++size_;
  return iterator(newNode);
}

template <typename T>
void list<T>::erase(iterator pos) {
  Node_* posNode = pos.getNode();
  posNode->prev->next = posNode->next;
  posNode->next->prev = posNode->prev;
  delete posNode;
  --size_;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node_* newNode = createNode(value, fake, fake->prev);
  fake->prev->next = newNode;
  fake->prev = newNode;
  ++size_;
}

template <typename T>
void list<T>::pop_back() {
  if (!empty()) {
    Node_* last = fake->prev;
    last->prev->next = fake;
    fake->prev = last->prev;
    delete last;
    --size_;
  }
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node_* newNode = createNode(value, fake->next, fake);
  fake->next->prev = newNode;
  fake->next = newNode;
  ++size_;
}

template <typename T>
void list<T>::pop_front() {
  if (!empty()) {
    Node_* first = fake->next;
    fake->next = first->next;
    first->next->prev = fake;
    delete first;
    --size_;
  }
}

template <typename T>
void list<T>::swap(list& other) noexcept {
  std::swap(fake, other.fake);
  std::swap(size_, other.size_);
}

// template <typename T>
// void list<T>::merge(list& other) {
//   if (this == &other || other.empty()) return;

//   iterator it1 = begin();
//   iterator it2 = other.begin();
//   while (it1 != end() && it2 != other.end()) {
//     if (*it2 < *it1) {
//       iterator nextIt2 = it2;
//       ++nextIt2;
//       Node_* node = it2.getNode();
//       node->prev->next = node->next;
//       node->next->prev = node->prev;
//       --other.size_;
//       Node_* posNode = it1.getNode();
//       node->next = posNode;
//       node->prev = posNode->prev;
//       posNode->prev->next = node;
//       posNode->prev = node;
//       ++size_;
//       it2 = nextIt2;
//     } else {
//       ++it1;
//     }
//   }
//   if (!other.empty()) {
//     Node_* firstOther = other.fake->next;
//     Node_* lastOther = other.fake->prev;
//     Node_* lastThis = fake->prev;
//     lastThis->next = firstOther;
//     firstOther->prev = lastThis;
//     lastOther->next = fake;
//     fake->prev = lastOther;
//     size_ += other.size_;
//     other.size_ = 0;
//     other.fake->next = other.fake;
//     other.fake->prev = other.fake;
//   }
// }

template <typename T>
void list<T>::merge(list& other) {
  if (this == &other || other.empty()) return;

  iterator it1 = begin();
  iterator it2 = other.begin();

  while (it1 != end() && it2 != other.end()) {
    if (*it2 < *it1) {
      iterator next_it2 = it2;
      ++next_it2;
      transferNode(it1, other, it2);
      it2 = next_it2;
    } else {
      ++it1;
    }
  }

  if (!other.empty()) {
    appendRemaining(other);  // append lost elements
  }
}

template <typename T>
void list<T>::transferNode(iterator pos, list& other, iterator src) {
  Node_* srcNode = src.getNode();

  srcNode->prev->next = srcNode->next;
  srcNode->next->prev = srcNode->prev;
  --other.size_;

  Node_* posNode = pos.getNode();
  srcNode->prev = posNode->prev;
  srcNode->next = posNode;
  posNode->prev->next = srcNode;
  posNode->prev = srcNode;
  ++size_;
}

template <typename T>
void list<T>::appendRemaining(list& other) {
  if (other.empty()) return;

  Node_* first;
  Node_* last;
  size_type movedSize;
  extractNodes(other, first, last, movedSize);
  linkNodes(fake->prev, fake, first, last, movedSize);
}

template <typename T>
void list<T>::extractNodes(list& other, Node_*& first, Node_*& last,
                           size_type& movedSize) {
  first = other.fake->next;
  last = other.fake->prev;
  movedSize = other.size_;

  // Reset source list
  other.fake->next = other.fake;
  other.fake->prev = other.fake;
  other.size_ = 0;
}

template <typename T>
void list<T>::linkNodes(Node_* posPrev, Node_* posNext, Node_* first,
                        Node_* last, size_type movedSize) {
  posPrev->next = first;
  first->prev = posPrev;
  last->next = posNext;
  posNext->prev = last;
  size_ += movedSize;
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
  if (other.empty()) return;

  Node_* first;
  Node_* last;
  size_type movedSize;
  extractNodes(other, first, last, movedSize);
  Node_* posNode = pos.getNode();
  linkNodes(posNode->prev, posNode, first, last, movedSize);
}

template <typename T>
void list<T>::reverse() noexcept {
  if (empty()) return;
  Node_* current = fake;
  do {
    Node_* tmp = current->next;
    current->next = current->prev;
    current->prev = tmp;
    current = tmp;
  } while (current != fake);
}

template <typename T>
void list<T>::unique() {
  if (empty()) return;
  iterator it = begin();
  while (it != end()) {
    iterator nextIt = it;
    ++nextIt;
    if (nextIt != end() && *it == *nextIt)
      erase(nextIt);
    else
      ++it;
  }
}

template <typename T>
void list<T>::sort() {
  if (empty() || size_ == 1) return;
  for (size_type i = 0; i < size_ - 1; ++i) {
    iterator it = begin();
    for (size_type j = 0; j < size_ - 1 - i; ++j) {
      iterator nextIt = it;
      ++nextIt;
      if (*nextIt < *it) {
        std::swap(*it, *nextIt);
      }
      ++it;
    }
  }
}

}  // namespace s21

#endif  // S21_CONTAINERS_H_S21_LIST_H
