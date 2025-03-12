#ifndef S21_CONTAINERS_H_S21_LIST_H
#define S21_CONTAINERS_H_S21_LIST_H

#include "components/s21_sequence_containers.h"
/**
 * @file s21_list.h
 * @brief Implementation of list container for s21_containers library
 * @details This container provides a doubly-linked list implementation with
 * constant time insertion and removal operations anywhere within the sequence.
 * Unlike vectors, lists do not support random access to elements but allow for
 * efficient insertion and deletion at any position.
 * @author countesz
 * @date 2025
 */

namespace s21 {

template <typename T>
class list : public SequenceContainer<list<T>, T> {
 private:
  // List Member type
  using value_type = typename SequenceContainer<list<T>, T>::value_type;
  using reference = typename SequenceContainer<list<T>, T>::reference;
  using const_reference =
      typename SequenceContainer<list<T>, T>::const_reference;
  using size_type = typename SequenceContainer<list<T>, T>::size_type;

  struct Node_ {
    value_type value;
    Node_* next;
    Node_* prev;

    // Constructor for a fake node
    explicit Node_(Node_* nextNode = nullptr, Node_* prevNode = nullptr);
    // Constructor for a real node
    explicit Node_(value_type val, Node_* nextNode = nullptr,
                   Node_* prevNode = nullptr);
  };

  Node_* fake;
  size_type size_;
  void initFakeNode();  // Initialize dummy node structure

 public:
  // List Functions
  list() noexcept;             // Default constructor
  explicit list(size_type n);  // Fill constructor
  list(std::initializer_list<value_type> const&
           items);                   // Initializer list constructor
  list(const list& other) noexcept;  // Copy constructor
  list(list&& other) noexcept;       // Move constructor
  ~list();                           // Destructor

  // Assignment operators
  list<T>& operator=(list<T>&& other) noexcept;       // Move assignment
  list<T>& operator=(const list<T>& other) noexcept;  // Copy assignment

  // Access and modification methods
  Node_* getHead() const;
  Node_* getTail() const;

  // List Iterators
  class ListIterator {
   public:
    ListIterator();                      // Default iterator constructor
    explicit ListIterator(Node_* node);  // Constructor from node pointer
    ListIterator& operator++();          // Prefix increment
    ListIterator operator++(int);        // Postfix increment
    ListIterator& operator--();          // Prefix decrement
    ListIterator operator--(int);        // Postfix decrement
    reference operator*();               // Dereference operator
    bool operator==(const ListIterator& other) const;  // Equality check
    bool operator!=(const ListIterator& other) const;  // Inequality check
    Node_* getNode() const;  // Get underlying node pointer

   protected:
    Node_* current;  // Pointer to current node
  };

  // Separate class for const iterator
  class ListConstIterator {
   public:
    ListConstIterator();  // Default const iterator
    explicit ListConstIterator(
        Node_* node);  // Node pointer constructor
                       // cppcheck-suppress noExplicitConstructor
    ListConstIterator(const ListIterator& other);
    ListConstIterator& operator++();    // Prefix increment
    ListConstIterator operator++(int);  // Postfix increment
    ListConstIterator& operator--();    // Prefix decrement
    ListConstIterator operator--(int);  // Postfix decrement
    const_reference operator*();        // Const dereference operator
    bool operator==(const ListConstIterator& other) const;  // Equality check
    bool operator!=(const ListConstIterator& other) const;  // Inequality check
    Node_* getNode() const;  // Get underlying node pointer

   protected:
    Node_* current;  // Pointer to current node
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  iterator begin() noexcept;  // Iterator to first element
  iterator end() noexcept;    // Iterator to end marker (fake node)
  const_iterator begin() const noexcept;

  const_iterator end() const noexcept;

  // List Element access
  const_reference front() const override;  // Access first element
  const_reference back() const override;   // Access last element

  // List Capacity
  bool empty() const noexcept override;      // Check if list is empty
  size_type size() const noexcept override;  // Get current number of elements
  size_type max_size() const noexcept override;  // Get maximum possible size

  // List Modifiers
  void clear() noexcept;  // Remove all elements
  iterator insert(iterator pos,
                  const_reference value);  // Insert element at position
  void erase(iterator pos);                // Remove element at position
  void push_back(const_reference value);   // Add to end
  void pop_back();                         // Remove from end
  void push_front(const_reference value);  // Add to front
  void pop_front();                        // Remove from front
  void swap(
      list& other) noexcept override;  // Exchange contents with another list
  void merge(list& other);             // Merge sorted lists
  void splice(const_iterator pos,
              list& other);  // Transfer elements from other list
  void reverse() noexcept;   // Reverse element order
  void unique();             // Remove consecutive duplicates
  void sort();               // Sort elements (using bubble sort)

  // many_insert methods

  template <typename... Args>
  iterator insert_many(const_iterator pos,
                       Args&&... args);  // Insert multiple elements

  template <typename... Args>
  void insert_many_back(Args&&... args);  // Append multiple elements

  template <typename... Args>
  void insert_many_front(Args&&... args);  // Prepend multiple elements

 private:
  // Utils
  Node_* createNode(const_reference value, Node_* next,
                    Node_* prev);    // Node allocation
  void copyFrom(const list& other);  // Deep copy helper

  // for merge() and splice()
  void transferNode(iterator pos, list& other,
                    iterator src);    // Move single node
  void appendRemaining(list& other);  // Append remaining nodes from other list

  void extractNodes(list& other, Node_*& first, Node_*& last,
                    size_type& movedSize);
  void linkNodes(Node_* posPrev, Node_* posNext, Node_* first, Node_* last,
                 size_type movedSize);

  // for many_insert
  template <typename... Args>
  void emplaceBack(
      Args&&... args);  // // insert element at end. Better than push_back()
};

template <typename T>
list<T>::Node_::Node_(Node_* nextNode, Node_* prevNode)
    : value(), next(nextNode), prev(prevNode) {}

template <typename T>
list<T>::Node_::Node_(value_type val, Node_* nextNode, Node_* prevNode)
    : value(val), next(nextNode), prev(prevNode) {}

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

/*List Iterators*/

/* ListIterator*/
template <typename T>
list<T>::ListIterator::ListIterator() : current(nullptr) {}

template <typename T>
list<T>::ListIterator::ListIterator(Node_* node) : current(node) {}

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator++() {
  current = current->next;
  return *this;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator++(int) {
  ListIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator--() {
  current = current->prev;
  return *this;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator--(int) {
  ListIterator temp = *this;
  --(*this);
  return temp;
}

template <typename T>
typename list<T>::reference list<T>::ListIterator::operator*() {
  return current->value;
}

template <typename T>
bool list<T>::ListIterator::operator==(const ListIterator& other) const {
  return current == other.current;
}

template <typename T>
bool list<T>::ListIterator::operator!=(const ListIterator& other) const {
  return current != other.current;
}

template <typename T>
typename list<T>::Node_* list<T>::ListIterator::getNode() const {
  return current;
}

/*ListConstIterator*/

template <typename T>
list<T>::ListConstIterator::ListConstIterator() : current(nullptr) {}

template <typename T>
list<T>::ListConstIterator::ListConstIterator(Node_* node) : current(node) {}
// cppcheck-suppress noExplicitConstructor
template <typename T>
list<T>::ListConstIterator::ListConstIterator(const ListIterator& other)
    : current(other.getNode()) {}

template <typename T>
typename list<T>::ListConstIterator& list<T>::ListConstIterator::operator++() {
  current = current->next;
  return *this;
}

template <typename T>
typename list<T>::ListConstIterator list<T>::ListConstIterator::operator++(
    int) {
  ListConstIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
typename list<T>::ListConstIterator& list<T>::ListConstIterator::operator--() {
  current = current->prev;
  return *this;
}

template <typename T>
typename list<T>::ListConstIterator list<T>::ListConstIterator::operator--(
    int) {
  ListConstIterator temp = *this;
  --(*this);
  return temp;
}

template <typename T>
typename list<T>::const_reference list<T>::ListConstIterator::operator*() {
  return current->value;
}

template <typename T>
bool list<T>::ListConstIterator::operator==(
    const ListConstIterator& other) const {
  return current == other.current;
}

template <typename T>
bool list<T>::ListConstIterator::operator!=(
    const ListConstIterator& other) const {
  return current != other.current;
}

template <typename T>
typename list<T>::Node_* list<T>::ListConstIterator::getNode() const {
  return current;
}

///////////
template <typename T>
typename list<T>::iterator list<T>::begin() noexcept {
  return iterator(fake->next);
}

template <typename T>
typename list<T>::iterator list<T>::end() noexcept {
  return iterator(fake);
}

template <typename T>
typename list<T>::const_iterator list<T>::begin() const noexcept {
  return const_iterator(fake->next);
}
template <typename T>
typename list<T>::const_iterator list<T>::end() const noexcept {
  return const_iterator(fake);
}

/*List Element access*/
template <typename T>
inline typename list<T>::const_reference list<T>::front() const {
  return fake->next->value;
}

template <typename T>
inline typename list<T>::const_reference list<T>::back() const {
  return fake->prev->value;
}

/*List Capacity*/
template <typename T>
inline bool list<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
inline typename list<T>::size_type list<T>::size() const noexcept {
  return size_;
}

template <typename T>
inline typename list<T>::size_type list<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(Node_) / 2;
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

/* many_insert methods
****************
The following functions are used to manage the insertion of multiple elements
into the list.
`insert_many` takes a position and a variable number of arguments, creates a
temporary list,and splices it into the original list at the specified position.
`insert_many_front` inserts multiple elements at the front of the list by
calling `insert_many`
`insert_many_back` inserts multiple elements at the back of the list by
calling `insert_many` with the end iterator.

*/

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  list<T> temp;
  (temp.emplaceBack(std::forward<Args>(args)), ...);

  if (temp.empty()) return iterator(pos.getNode());

  iterator first = temp.begin();
  splice(pos, temp);
  return first;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  const_iterator it = begin();
  insert_many(it, std::forward<Args>(args)...);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  const_iterator it = end();
  insert_many(it, std::forward<Args>(args)...);
}

/*Utils
************
transferNode(),appendRemaining(),extractNodes(),extractNodes(),linkNodes() -
auxiliary functions for merge() and splice()
*************
emplaceBack()- inserts elements at the end of the list. More efficient than
push_back(), because it does not additionally call copy/move constructors.
*/

template <typename T>
typename list<T>::Node_* list<T>::createNode(const_reference value, Node_* next,
                                             Node_* prev) {
  return new Node_(value, next, prev);
}

/*
transferNode() - transfers a single node from another list to this list at the
specified position. It removes the node from the source list, updates the source
list's size, and inserts the node at the position in the current list, updating
its size as well.
*/
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

/*
appendRemaining() - appends all nodes from the source list to the end of the
current list. It extracts all nodes from the source list and links them to the
end of the current list. The source list becomes empty after this operation.
*/
template <typename T>
void list<T>::appendRemaining(list& other) {
  if (other.empty()) return;

  Node_* first;
  Node_* last;
  size_type movedSize;
  extractNodes(other, first, last, movedSize);
  linkNodes(fake->prev, fake, first, last, movedSize);
}

/*
extractNodes() - extracts all nodes from the source list, returning the first
and last nodes along with the number of nodes extracted. The source list is
reset to an empty state. This is used for efficient transfer of nodes between
lists.
*/
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

/*
linkNodes() - connects a sequence of nodes between two existing nodes in the
list. It takes the nodes before and after the insertion point, the first and
last nodes of the sequence to insert, and the number of nodes being inserted.
This is used for efficient node transfer operations.
*/
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
typename list<T>::Node_* list<T>::getHead() const {
  return fake->next;
}
template <typename T>
typename list<T>::Node_* list<T>::getTail() const {
  return fake->prev;
}

template <typename T>
template <typename... Args>
void list<T>::emplaceBack(Args&&... args) {
  Node_* newNode = new Node_(T(std::forward<Args>(args)...), fake, fake->prev);
  fake->prev->next = newNode;
  fake->prev = newNode;
  ++size_;
}

}  // namespace s21

#endif  // S21_CONTAINERS_H_S21_LIST_H
