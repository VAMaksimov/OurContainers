#ifndef S21_CONTAINERS_H_S21_LIST_H
#define S21_CONTAINERS_H_S21_LIST_H

#include "components/s21_sequence_containers.h"

namespace s21 {
template <typename T>
class list : public SequenceContaner<list<T>, T> {
 public:
  //  List Member type
  using value_type = typename SequenceContaner<list<T>, T>::value_type;
  using reference = typename SequenceContaner<list<T>, T>::reference;
  using const_reference =
      typename SequenceContaner<list<T>, T>::const_reference;
  using size_type = typename SequenceContaner<list<T>, T>::size_type;

  struct Node_ {
    value_type value;
    Node_* next;
    Node_* prev;

    // Constructor fake Node
    explicit Node_(Node_* next_node = nullptr, Node_* prev_node = nullptr)
        : value(), next(next_node), prev(prev_node) {}
    // Constructor real Node
    explicit Node_(value_type val, Node_* next_node = nullptr,
                   Node_* prev_node = nullptr)
        : value(val), next(next_node), prev(prev_node) {}
  };
  // Сonstructors
  list() noexcept;
  explicit list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& other) noexcept;
  list(list&& other) noexcept;
  // Destructor
  ~list();

  // Operators

  list<T>& operator=(list<T>&& other) noexcept;
  list<T>& operator=(const list<T>& other) noexcept;

  // Mutators and accesors
  size_type getSize() const { return size; }
  Node_* getHead() const { return fake->next; }
  Node_* getTail() const { return fake->prev; }

  // Iterators
  // Изменим ListIterator: изменяем область видимости current на protected
  class ListIterator {
   public:
    ListIterator() = default;
    ListIterator(Node_* node) : current(node) {}
    ~ListIterator() = default;

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

   protected:
    Node_* current;
  };
  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator() : ListIterator(nullptr) {}
    ListConstIterator(Node_* node) : ListIterator(node) {}
    ListConstIterator(const ListIterator& other) : ListIterator(other) {}
    const_reference operator*() { return this->current->value; }
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  iterator begin() const noexcept { return iterator(fake->next); }
  iterator end() const noexcept { return iterator(fake); }

  // Methoods
  void clear();
  void swap(list& other) noexcept;

 private:
  Node_* fake;
  size_type size;
  void initFakeNode();
};

template <typename T>
inline void list<T>::initFakeNode() {
  fake = new Node_();
  fake->next = fake;
  fake->prev = fake;
}

// Constructors default
template <typename T>
inline list<T>::list() noexcept : size(0) {
  initFakeNode();
}

// Constructors param
template <typename T>
inline list<T>::list(size_type n) : size(0) {
  initFakeNode();
  for (size_type i = 0; i < n; ++i) {
    Node_* newNode = new Node_(value_type());
    if (fake->next == fake) {
      fake->next = fake->prev = newNode;
    } else {
      newNode->prev = fake->prev;
      fake->prev->next = newNode;
    }
    fake->prev = newNode;
    newNode->next = fake;
    ++size;
  }
}

// Constructor {}
template <typename T>
inline list<T>::list(std::initializer_list<value_type> const& items) : size(0) {
  initFakeNode();
  for (const auto& item : items) {
    Node_* newNode = new Node_(item);
    newNode->next = fake;
    newNode->prev = fake->prev;
    fake->prev->next = newNode;
    fake->prev = newNode;
    ++size;
  }
}

// constructor move
template <typename T>
inline list<T>::list(list&& other) noexcept {
  if (other.fake != nullptr) {
    fake = other.fake;
    size = other.size;

    other.fake = nullptr;
    other.size = 0;
    other.initFakeNode();
  };
}

// Constructor copy
template <typename T>
inline list<T>::list(const list& other) noexcept : size(other.size) {
  initFakeNode();
  Node_* currentNode = other.getHead();
  while (currentNode != other.fake) {
    Node_* newNode = new Node_(currentNode->value);
    newNode->prev = fake->prev;
    fake->prev->next = newNode;
    fake->prev = newNode;
    newNode->next = fake;
    currentNode = currentNode->next;
  }
}

// Destructor
template <typename T>
inline list<T>::~list() {
  clear();
  delete fake;
}

template <typename T>
inline void list<T>::clear() {
  while (fake->next != fake) {
    Node_* temp = fake->next;
    fake->next = temp->next;
    delete temp;
  }
  fake->prev = fake;
  size = 0;
}

/*Operators*/

template <typename T>
inline list<T>& list<T>::operator=(list<T>&& other) noexcept {
  if (this != &other) {
    // Очищаем текущий объект
    clear();
    delete fake;

    if (other.fake != nullptr) {
      // Перемещаем данные из other в текущий объект
      fake = other.fake;
      size = other.size;

      // Обнуляем other
      other.fake = nullptr;
      other.size = 0;
      other.initFakeNode();
    }
  }
  return *this;
}

template <typename T>
inline list<T>& list<T>::operator=(const list<T>& other) noexcept {
  if (this != &other) {
    list<T> temp(other);
    swap(temp);
  }
  return *this;
}

/* methods ListIterator*/

// template <typename T>
// inline list<T>::ListIterator::ListIterator(Node_* node) : current(node) {}

// template <typename T>
// inline typename list<T>::ListIterator& list<T>::ListIterator::operator++() {
//   current = current->next;
//   return *this;
// }

// template <typename T>
// inline typename list<T>::ListIterator list<T>::ListIterator::operator++(int)
// {
//   ListIterator temp = *this;
//   ++(*this);
//   return temp;
// }

// template <typename T>
// inline typename list<T>::ListIterator& list<T>::ListIterator::operator--() {
//   current = current->prev;
//   return *this;
// }

// template <typename T>
// inline typename list<T>::ListIterator list<T>::ListIterator::operator--(int)
// {
//   ListIterator temp = *this;
//   --(*this);
//   return temp;
// }

// template <typename T>
// inline bool list<T>::ListIterator::operator==(const ListIterator& other)
// const {
//   return current == other.current;
// }

// template <typename T>
// inline bool list<T>::ListIterator::operator!=(const ListIterator& other)
// const {
//   return current != other.current;
// }

// template <typename T>
// inline typename list<T>::iterator list<T>::begin() const noexcept {
//   return iterator(fake->next);
// }

// template <typename T>
// inline typename list<T>::iterator list<T>::end() const noexcept {
//   return iterator(fake);
// }

// template <typename T>
// inline typename list<T>::const_iterator list<T>::begin() const noexcept {
//   return const_iterator(fake->next);
// }

// template <typename T>
// inline typename list<T>::const_iterator list<T>::end() const noexcept {
//   return const_iterator(fake);
// }

// template <typename T>
// inline typename list<T>::reference list<T>::ListIterator::operator*() const {
//   return current->value;
// }

/*Capacity*/
template <typename T>
void list<T>::swap(list& other) noexcept {
  std::swap(this->fake, other.fake);
  std::swap(this->size, other.size);
}

}  // namespace s21
#endif  // S21_CONTAINERS_H_S21_LIST_H