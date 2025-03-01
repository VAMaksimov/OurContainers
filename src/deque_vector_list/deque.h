#ifndef DEQUE
#define DEQUE

#include <iostream>
#include <vector>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

template <typename T>
class deque
{
private:
    static const size_t BLOCK_SIZE = 16;

    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = std::size_t;

    struct Node {
        value_type data[BLOCK_SIZE];
        Node* pNext;
        Node* pPrev;
        size_type count;

        Node() : pNext(nullptr), pPrev(nullptr), count(0) {}
    };

    Node* head;
    Node* tail;
    size_type Size;

    void create_new_node(Node*& node) {
        node = new Node();
        if (tail) {
            tail->pNext = node;
            node->pPrev = tail;
        } else {
            head = node;
        }
        tail = node;
    }

public:
    class DequeIterator;
    class DequeConstIterator;

    using iterator = DequeIterator;
    using const_iterator = DequeConstIterator;

    // Конструкторы
    deque();
    explicit deque(size_type n);
    deque(const deque &other);
    deque(deque &&other);
    deque(std::initializer_list<value_type> const &items);

    // Деструктор
    ~deque();

    // Методы
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;
    reference front();
    reference back();
    bool empty() const;
    size_type size() const;
    void clear();
    void push_back(const_reference value);
    void push_front(const_reference value);
    void pop_front();
    void pop_back();
    void shrink_to_fit();
    void swap(deque &other);
    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

    class DequeIterator {
    private:
        Node* current_node;
        size_type index;

    public:
        DequeIterator(Node* node, size_type idx) : current_node(node), index(idx) {}

        reference operator*() {
            return current_node->data[index];
        }

        DequeIterator& operator++() {
            if (index + 1 < current_node->count) {
                ++index;
            } else {
                current_node = current_node->pNext;
                index = 0;
            }
            return *this;
        }

        DequeIterator operator++(int) {
            DequeIterator temp = *this;
            ++(*this);
            return temp;
        }

        DequeIterator& operator--() {
            if (index > 0) {
                --index;
            } else {
                current_node = current_node->pPrev;
                index = current_node->count - 1;
            }
            return *this;
        }

        DequeIterator operator--(int) {
            DequeIterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const DequeIterator& other) const {
            return current_node == other.current_node && index == other.index;
        }

        bool operator!=(const DequeIterator& other) const {
            return !(*this == other);
        }
    };

    class DequeConstIterator {
    private:
        const Node* current_node;
        size_type index;

    public:
        DequeConstIterator(const Node* node, size_type idx) : current_node(node), index(idx) {}

        const_reference operator*() const {
            return current_node->data[index];
        }

        DequeConstIterator& operator++() {
            if (index + 1 < current_node->count) {
                ++index;
            } else {
                current_node = current_node->pNext;
                index = 0;
            }
            return *this;
        }

        DequeConstIterator operator++(int) {
            DequeConstIterator temp = *this;
            ++(*this);
            return temp;
        }

        DequeConstIterator& operator--() {
            if (index > 0) {
                --index;
            } else {
                current_node = current_node->pPrev;
                index = current_node->count - 1;
            }
            return *this;
        }

        DequeConstIterator operator--(int) {
            DequeConstIterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const DequeConstIterator& other) const {
            return current_node == other.current_node && index == other.index;
        }

        bool operator!=(const DequeConstIterator& other) const {
            return !(*this == other);
        }
    };
};

/** Протестировано */
template <typename value_type>
deque<value_type>::deque() : head(nullptr), tail(nullptr), Size(0) {}

/** Протестировано */
template <typename value_type>
deque<value_type>::deque(size_type n) : head(nullptr), tail(nullptr), Size(n) {
    size_type full_blocks = n / BLOCK_SIZE;
    size_type remaining_elements = n % BLOCK_SIZE;

    for (size_type i = 0; i < full_blocks; ++i) {
        Node* node;
        create_new_node(node);
        std::fill(node->data, node->data + BLOCK_SIZE, value_type());
        node->count = BLOCK_SIZE;
    }

    if (remaining_elements > 0) {
        Node* node;
        create_new_node(node);
        std::fill(node->data, node->data + remaining_elements, value_type());
        node->count = remaining_elements;
    }
}

template <typename value_type>
deque<value_type>::deque(const deque &other) : head(nullptr), tail(nullptr), Size(other.Size) {
    Node* current = other.head;
    while (current) {
        Node* new_node;
        create_new_node(new_node);
        std::copy(current->data, current->data + current->count, new_node->data);
        new_node->count = current->count;
        current = current->pNext;
    }
}

template <typename value_type>
deque<value_type>::deque(deque &&other) : head(other.head), tail(other.tail), Size(other.Size) {
    other.head = nullptr;
    other.tail = nullptr;
    other.Size = 0;
}

template <typename value_type>
deque<value_type>::deque(std::initializer_list<value_type> const &items) : head(nullptr), tail(nullptr), Size(items.size()) {
    auto it = items.begin();
    while (it != items.end()) {
        push_back(*it);
        ++it;
    }
}

template <typename value_type>
deque<value_type>::~deque() {
    clear();
    Node* current = head;
    while (current) {
        Node* next = current->pNext;
        delete current;
        current = next;
    }
}

template <typename value_type>
typename deque<value_type>::reference deque<value_type>::operator[](size_type pos) {
    size_type block_index = pos / BLOCK_SIZE;
    size_type element_index = pos % BLOCK_SIZE;

    Node* current = head;
    for (size_type i = 0; i < block_index; ++i) {
        current = current->pNext;
    }

    return current->data[element_index];
}

template <typename value_type>
typename deque<value_type>::const_reference deque<value_type>::operator[](size_type pos) const {
    size_type block_index = pos / BLOCK_SIZE;
    size_type element_index = pos % BLOCK_SIZE;

    Node* current = head;
    for (size_type i = 0; i < block_index; ++i) {
        current = current->pNext;
    }

    return current->data[element_index];
}

template <typename value_type>
typename deque<value_type>::reference deque<value_type>::front() {
    return head->data[0];
}

template <typename value_type>
typename deque<value_type>::reference deque<value_type>::back() {
    return tail->data[tail->count - 1];
}

template <typename value_type>
bool deque<value_type>::empty() const {
    return Size == 0;
}

template <typename value_type>
typename deque<value_type>::size_type deque<value_type>::size() const {
    return Size;
}

template <typename value_type>
void deque<value_type>::clear() {
    Size = 0;
    Node* current = head;
    while (current) {
        Node* next = current->pNext;
        current->count = 0;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}

template <typename value_type>
void deque<value_type>::push_back(const_reference value) {
    if (tail == nullptr || tail->count == BLOCK_SIZE) {
        Node* new_node;
        create_new_node(new_node);
    }
    tail->data[tail->count++] = value;
    ++Size;
}

template <typename value_type>
void deque<value_type>::push_front(const_reference value) {
    if (head == nullptr || head->count == BLOCK_SIZE) {
        Node* new_node = new Node();
        new_node->pNext = head;
        if (head) {
            head->pPrev = new_node;
        } else {
            tail = new_node;
        }
        head = new_node;
    } else {
        for (size_type i = head->count; i > 0; --i) {
            head->data[i] = head->data[i - 1];
        }
        head->data[0] = value;
        ++head->count;
    }
    ++Size;
}

template <typename value_type>
void deque<value_type>::pop_front() {
    if (head) {
        if (--head->count == 0) {
            Node* temp = head;
            head = head->pNext;
            if (head) {
                head->pPrev = nullptr;
            } else {
                tail = nullptr;
            }
            delete temp;
        }
        --Size;
    }
}

template <typename value_type>
void deque<value_type>::pop_back() {
    if (tail) {
        if (--tail->count == 0) {
            Node* temp = tail;
            tail = tail->pPrev;
            if (tail) {
                tail->pNext = nullptr;
            } else {
                head = nullptr;
            }
            delete temp;
        }
        --Size;
    }
}

template <typename value_type>
void deque<value_type>::shrink_to_fit() {
    Node* current = head;
    while (current) {
        Node* next = current->pNext;
        if (current->count == 0 && current != tail) {
            if (current->pPrev) {
                current->pPrev->pNext = current->pNext;
            }
            if (current->pNext) {
                current->pNext->pPrev = current->pPrev;
            }
            delete current;
        }
        current = next;
    }
}

template <typename value_type>
typename deque<value_type>::iterator deque<value_type>::begin() {
    return iterator(head, 0);
}

template <typename value_type>
typename deque<value_type>::iterator deque<value_type>::end() {
    return iterator(tail, tail ? tail->count : 0);
}

template <typename value_type>
typename deque<value_type>::const_iterator deque<value_type>::cbegin() const {
    return const_iterator(head, 0);
}

template <typename value_type>
typename deque<value_type>::const_iterator deque<value_type>::cend() const {
    return const_iterator(tail, tail ? tail->count : 0);
}

template <typename T>
void deque<T>::swap(deque &other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(Size, other.Size);
}


#endif // DEQUE
