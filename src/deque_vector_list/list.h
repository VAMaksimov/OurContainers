#ifndef LIST
#define LIST


#include <iostream>
#include <string>
#include <limits>

// ToDo SORT!!

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
    const_reference front() const;

    const_reference back() const;
    bool empty();


    size_type size();
    size_type max_size();

    void clear();
    void erase(iterator pos);
    void push_back(const_reference value);
    void push_front(const_reference value);
    void pop_front();
    void pop_back();
    void swap(list& other);
    void merge(list& other);
    void splice(const_iterator pos, list& other);
    void reverse();
    void unique();
    void sort();

    
    /** Operators */
    reference operator=(list &&l);
    reference operator[](const int index);

    iterator insert(iterator pos, const_reference value) {
        Node<value_type>* newNode = new Node<value_type>(value);

        if (pos == nullptr) {
            if (tail != nullptr) {
                tail->pNext = newNode;
                newNode->pPrev = tail;
            } else {
                head = newNode;
            }
            tail = newNode;
        } else {
            Node<value_type>* current = pos.current;

            newNode->pNext = current;
            newNode->pPrev = current->pPrev;

            if (current->pPrev != nullptr) {
                current->pPrev->pNext = newNode;
            } else {
                head = newNode;
            }

            current->pPrev = newNode;
        }

        Size++;
        return iterator(newNode);
    }

    iterator begin() {
        return iterator(head);
    }
    iterator end() {
        return iterator(tail);
    }

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

            ListIterator begin() {
                return ListIterator(head);
            }

            ListIterator end() {
                return (this->cend+1);
            }
        
            ListConstIterator cbegin() const {
                return ListConstIterator(head);
            }
        
            ListConstIterator cend() const {
                return (this->cend+1);
            }

        };

};

/** @brief увеличиваем резмер списка на один и записываем в новое поле аргумент
 * @param data переданный аргумент
*/
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

/** @brief уборка
*/
template <typename value_type>
void list<value_type>::clear() {
    while (head != nullptr) {
        pop_front();
    }
}

/** @brief Перегрузка для быстрого доступа вместо геттера
 * @param data 
*/
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

/** @brief Перегрузка для быстрого доступа вместо геттера
 * @param номер элемента в списке
*/
template <typename value_type>
value_type &list<value_type>::operator[](const int index)
{
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

/** @brief Простой конструктор, который выделяет память под заданное количество элементов
 * @param n то самое количество элементов
*/
template <typename value_type>
list<value_type>::list(size_type n) : Size(0), head(nullptr), tail(nullptr) {
    if ((int)n < 0) { 
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

/** @brief Самый кайфовый конструктор, который может принимать сразу целый массив
 * @param "std::initializer_list<value_type> const &items" как раз и есть этот массив
*/
template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const &items) : Size(0), head(nullptr), tail(nullptr) {
    for (const auto& item : items) {
        Node<value_type>* newNode = new Node<value_type>(item); 
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

/** @brief Конструктор копирования
 * @param &l константный список, по образу которого будет создан новый
*/
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

/** @brief Стандартный конструктор
*/
template <typename value_type>
list<value_type>::list() : Size(0), head(nullptr), tail(nullptr) {}

/** @brief Конструктор переноса
 * @param &&l дает возможнность просто перепривязать указатель к новому обьекту
*/
template <typename value_type>
list<value_type>::list(list &&l) : head(l.head), Size(l.Size), tail(l.tail) {
    l.head = nullptr;
    l.Size = 0;
}

/** @brief Деструктор
*/
template <typename value_type>
list<value_type>::~list() {
    while (head != nullptr) {
        pop_front();
    }
}

/** @brief Возвращает константную ссылку на первый элемент списка. 
 * Если список пуст, выбрасывает исключение std::out_of_range в случае,
 * если head == nullptr.
*/
template <typename value_type>
const value_type & list<value_type>::front() const {
    if (head == nullptr) {
        throw std::out_of_range("List is empty"); 
    }
    return head->data;
}

/** @brief То же, что и предыдущее, только с хвостом
*/
template <typename value_type>
const value_type & list<value_type>::back() const {
    if (tail == nullptr) {
        throw std::out_of_range("List is empty"); 
    }
    return tail->data;
}

/** @brief Удаление первого элемента в списке без возврата значений
 */
template <typename value_type>
void list<value_type>::pop_front() {
    if (head == nullptr) {
        throw std::out_of_range("List is empty"); 
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

/** @brief Удаление последнего элемента
 */
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

/** @brief Обмен содержимым для двух списков без копирования 
 * @param list& other это указатель на другой список
*/
template <typename value_type>
void list<value_type>::swap(list& other) {
    if (head == nullptr) {
        throw std::out_of_range("List is empty"); 
    }
    std::swap(this->head, other.head);
    std::swap(this->tail, other.tail);
    std::swap(this->Size, other.Size);
}

/** @brief Обмен содержимым для двух списков без копирования 
 * @param list& other это указатель на другой список
*/
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
    this->sort();
    other.head = nullptr;
    other.tail = nullptr; 
    other.Size = 0;
}

/** @brief вставляет элементы из одного двусвязного списка (other) 
 * в текущий список (this) на указанную позицию (pos).
 *
 * @param pos итератор, указывающий на позицию в текущем списке,
 * перед которой будут вставлены элементы из другого списка.
 * @param other указатель на другой двусвязный список, элементы которого 
 * будут перемещены в текущий список.
 */
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

/** @brief Удаляет элемент по итератору, который в него поуступил 
 * @param pos значение итератора
*/
template <typename value_type>
void list<value_type>::erase(iterator pos) {
    if (pos == end()) {
        return;
    }

    Node<value_type>* nodeToDelete = pos.current;

    if (nodeToDelete->pPrev != nullptr) {
        nodeToDelete->pPrev->pNext = nodeToDelete->pNext;
    } else {
        head = nodeToDelete->pNext; 
    }

    if (nodeToDelete->pNext != nullptr) {
        nodeToDelete->pNext->pPrev = nodeToDelete->pPrev; 
    } else {
        tail = nodeToDelete->pPrev; 
    }

    delete nodeToDelete;
    --Size;
}

/** @brief Инверсия списка 
*/
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

/** @brief Возвращает размер списка
*/
template <typename value_type>
size_t list<value_type>::size() {
    return Size;
}

/** @brief Отвечает на вопрос пустой список или нет
*/
template <typename value_type>
bool list<value_type>::empty() {
    return !!(Size == 0);
}

/** @brief оставляем только одно вхождение каждого элемента, если они идут подряд
*/
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

/** @brief Метод для получения максимального количества элементов, 
 * которые контейнер может хранить. Этот метод возвращает значение 
 * типа size_type, которое представляет максимальный размер контейнера, 
 * определяемый реализацией стандартной библиотеки и доступной памятью.
*/
template <typename value_type>
size_t list<value_type>::max_size() {
    return std::numeric_limits<size_type>::max();
}

/** @brief Оператор присваивания
 * @param l передаем двойной указатель на этот список и погнали
*/
template <typename value_type>
value_type & list<value_type>::operator=(list&& l) {
    if (this != &l) { 
        clear(); 

        head = l.head;
        tail = l.tail;
        Size = l.Size;

        l.head = nullptr;
        l.tail = nullptr;
        l.Size = 0;
    }
    return *this;
}   

#endif