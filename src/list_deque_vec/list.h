#include <iostream>
#include <string>


template <typename T>
class list
{
private:
    
    template <typename N>
    class Node
    {

    public:
        T data;
        Node *pNext;
        Node *pPrev;
        Node(N data = N(), Node* pNext = nullptr, Node* pPrev = nullptr) : data(data), pNext(pNext), pPrev(pPrev) {}
    };

    int Size;
    Node<T> *head;
    Node<T> *tail;
    
public:
    // iterator begin();
    // iterator end();
    class ListIterator;
    class ListConstIterator;
    /** Member type */
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = ListIterator;
    using const_iterator = ListConstIterator;
    using size_type = size_t;

    /** Constructors */
    list();
    explicit list(size_type n);
    list(std::initializer_list<value_type> const &items);
    list(const list &l);
    list(list &&l);

    /** Destructor */
    ~list();
    
    /** Metods */
    // const_reference front();
    // const_reference back()
    // T & front() const;
    // bool empty();


    // size_type size();
    // size_type max_size();

    void clear();
    // iterator insert(iterator pos, const_reference value);
    // void erase(iterator pos);
    void push_back(const_reference value);
    void push_front(const_reference value);
    void pop_front();
    void pop_back();
    void swap(list& other);
    void merge(list& other);
    void splice(const_iterator pos, list& other);
    void reverse();
    void unique();
    // void sort();

    
    /** Operators */
    // operator=(list &&l);
    // list<T>& operator=(const list<T>& other);
    // list<T>& operator=(list<T>&& other);
    reference operator[](const int index);

    class ListIterator {
        private:
            Node<T>* current;
    
        public:

            ListIterator(Node<value_type>* node) : current(node) {}

            reference operator*() {
                return current->data;
            }

            ListIterator& operator++() {
                if (current) {
                    current = current->pNext;
                }
                return *this;
            }

            ListIterator operator++(int) {
                ListIterator temp = *this;
                ++(*this);
                return temp;
            }

            ListIterator& operator--() {
                if (current) {
                    current = current->pPrev;
                }
                return *this;
            }

            ListIterator operator--(int) {
                ListIterator temp = *this;
                --(*this);
                return temp;
            }

            bool operator==(const ListIterator& other) const {
                return current == other.current;
            }

            bool operator!=(const ListIterator& other) const {
                return current != other.current;
            }
        };
    
        ListIterator begin() {
            return ListIterator(head);
        }
    
        ListIterator end() {
            return ListIterator(nullptr);
        }
    
    class ListConstIterator {
        private:
            const Node<T>* current;
    
        public:
            ListConstIterator(const Node<T>* node) : current(node) {}
    
            const T& operator*() const {
                return current->data;
            }
    
            ListConstIterator& operator++() {
                if (current) {
                    current = current->pNext;
                }
                return *this;
            }
    
            ListConstIterator operator++(int) {
                ListConstIterator temp = *this;
                ++(*this);
                return temp;
            }
    
            ListConstIterator& operator--() {
                if (current) {
                    current = current->pPrev;
                }
                return *this;
            }
    
            ListConstIterator operator--(int) {
                ListConstIterator temp = *this;
                --(*this);
                return temp;
            }
    
            bool operator==(const ListConstIterator& other) const {
                return current == other.current;
            }
    
            bool operator!=(const ListConstIterator& other) const {
                return current != other.current;
            }
        };
    
        
        // ListIterator begin() {
        //     return ListIterator(head);
        // }
    
        // ListIterator end() {
        //     return ListIterator(nullptr);
        // }
    
        // ListConstIterator cbegin() const {
        //     return ListConstIterator(head);
        // }
    
        // ListConstIterator cend() const {
        //     return ListConstIterator(nullptr);
        // }

};

template <typename value_type>
void list<value_type>::push_back(const_reference data) {
    Node<value_type>* newNode = new Node<value_type>(data);
    if (tail == nullptr) { 
        head = tail = newNode;
    } else {
        tail->pNext = newNode; 
        newNode->pPrev = tail; 
        tail = newNode;
    }
    ++Size; 
}

template <typename value_type>
void list<value_type>::clear() {
    while (head != nullptr) {
        pop_front();
    }
}

template <typename value_type>
void list<value_type>::push_front(const_reference data) {
    Node<value_type>* new_head = new Node<value_type>(data);

    if (head == nullptr) { 
        head = tail = new_head;
    } else {
        new_head->pNext = head;
        head->pPrev = new_head;
        head = new_head;
    }

    ++Size;
}



template <typename value_type>
value_type &list<value_type>::operator[](const int index) {
    if (index < 0 || index >= Size) {
        throw std::out_of_range("Index out of range");
    } else {
        Node<value_type> *result = this->head;
        for (int counter = 0; counter < index; ++counter) {
            result = result->pNext;
        }

    return result->data;
    }
}


/** Constructors */
template <typename value_type>
list<value_type>::list(size_type n) : head(nullptr), tail(nullptr), Size(0) {
    if (n < 0) { 
        throw std::out_of_range("Size n is less than 0");
    }

    for (size_type i = 0; i < n; ++i) {
        Node<value_type>* newNode = new Node<value_type>(value_type());
        if (head == nullptr) { 
            head = tail = newNode; 
        } else {
            tail->pNext = newNode; 
            newNode->pPrev = tail; 
            tail = newNode; 
        }
        ++Size; 
    }
}

template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const &items) : head(nullptr), tail(nullptr), Size(0) {
    for (const auto& item : items) {
        Node<value_type>* newNode = new Node<value_type>(item); 
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->pNext = newNode;
            newNode->pPrev = tail;
            tail = newNode; 
        }
    }
}

template <typename value_type>
list<value_type>::list(const list &l) : head(nullptr), Size(0) {
    Node<value_type>* current = l.head;
    Node<value_type>* lastNode = nullptr;

    while (current != nullptr) {
        Node<value_type>* newNode = new Node(current->data);
        if (head == nullptr) {
            head = newNode;
        } else {
            lastNode->pNext = newNode;
        }
        lastNode = newNode; 
        current = current->pNext; 
        ++Size;
    }
}

template <typename value_type>
list<value_type>::list() : head(nullptr), Size(0), tail(nullptr) {}

template <typename value_type>
list<value_type>::list(list &&l) : head(l.head), Size(l.Size), tail(l.tail) {
    l.head = nullptr;
    l.Size = 0;
}

template <typename value_type>
list<value_type>::~list() {
    while (head != nullptr) {
        pop_front();
    }
}

template <typename value_type>
void list<value_type>::pop_front() {
    if (head == nullptr) { 
        return;
    }

    Node<value_type>* tmp = head; 
    head = head->pNext;
    if (head != nullptr) {
        head->pPrev = nullptr;
    } else {
        tail = nullptr;
    }

    delete tmp;
    --Size;
}

template <typename value_type>
void list<value_type>::pop_back() {
    if (tail == nullptr) {
        return;
    }

    Node<value_type>* tmp = tail;
    tail = tail->pPrev;

    if (tail != nullptr) {
        tail->pNext = nullptr;
    } else {
        head = nullptr;
    }

    delete tmp;
    --Size;
}

template <typename value_type>
void list<value_type>::swap(list& other) {
    std::swap(this->head, other.head);
    std::swap(this->tail, other.tail);
    std::swap(this->Size, other.Size);
}

template <typename value_type>
void list<value_type>::merge(list& other) {
    if (this == &other) {
        return;
    }

    if (head == nullptr) { 
        head = other.head;
        tail = other.tail;
    } else if (other.head != nullptr) {
        tail->pNext = other.head; 
        other.head->pPrev = tail;
        tail = other.tail;
    }

    Size += other.Size;
    other.head = nullptr;
    other.tail = nullptr; 
    other.Size = 0;
}

template <typename value_type>
void list<value_type>::splice(const_iterator pos, list& other) {
    if (this == &other) {
        return;
    }

    if (other.head == nullptr) {
        return; 
    }

    Node<value_type>* posNode = const_cast<Node<value_type>*>(pos.node);
    Node<value_type>* otherHead = other.head;
    Node<value_type>* otherTail = other.tail;
    if (posNode == head) {
        head = otherHead; 
    } else {
        posNode->pPrev->pNext = otherHead;
        otherHead->pPrev = posNode->pPrev;
    }

    if (posNode != nullptr) {
        posNode->pPrev = otherTail;
        otherTail->pNext = posNode; 
    } else {
        tail = otherTail; 
    }

    Size += other.Size; 
    other.head = nullptr; 
    other.tail = nullptr;
    other.Size = 0;
}

template <typename value_type>
void list<value_type>::reverse() {
    Node<value_type>* current = head;
    Node<value_type>* temp = nullptr;

    while (current != nullptr) {
        temp = current->pPrev;
        current->pPrev = current->pNext;
        current->pNext = temp;
        current = current->pPrev;
    }

   
    if (temp != nullptr) {
        tail = head;
        head = temp->pPrev;
    }
}

template <typename value_type>
void list<value_type>::unique() {
    if (head == nullptr) {
        return; 
    }

    Node<value_type>* current = head;

    while (current != nullptr) {
        Node<value_type>* nextNode = current->pNext;

        while (nextNode != nullptr && nextNode->data == current->data) {
            Node<value_type>* temp = nextNode; 
            nextNode = nextNode->pNext; 
            delete temp; 
            Size--; 
        }

        current->pNext = nextNode; 

        if (nextNode != nullptr) {
            nextNode->pPrev = current; 
        } else {
            tail = current; 
        }

        current = current->pNext; 
    }
}