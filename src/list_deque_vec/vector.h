#include <iostream>
#include <stdexcept>
#include <initializer_list>

template <typename T>
class vector {
private:
    T* data;          
    size_t capacity;  
    size_t size;     

    void resize(size_t new_capacity) {
        if (new_capacity == 0) {
            delete[] data;
            data = nullptr;
            capacity = 0; 
            return;
        }

        value_type* new_data = nullptr;
        try {
            new_data = new value_type[new_capacity];
        } catch (const std::bad_alloc& e) {
            throw std::runtime_error("Memory allocation failed: " + std::string(e.what()));
        }

        if (data != nullptr) {
            for (size_t i = 0; i < size; ++i) {
                new_data[i] = data[i]; 
            }
        }
    }

public:
    using value_type = T;
    // using reference = T &;
    // using const_reference = const T &;
    // using iterator = T *;
    // using const_iterator = const T *;
    using size_type = size_t;
    /** Constructors */
    vector();
    vector(size_type n);
    vector(std::initializer_list<value_type> const &items);
    // vector(const vector &v);
    // vector(vector &&v);
    ~vector();
    // reference operator=(vector &&v);

    /** Element access */
    // reference at(size_type pos);
    // reference operator[](size_type pos);
    // const_reference front();
    // const_reference back();
    // T* data();

    /** Iterators */
    // iterator begin();
    // iterator end();

    /** Vector capacity */
    // bool empty();
    // size_type size();
    // size_type max_size();
    // void reserve(size_type size);
    // size_type capacity();
    // void shrink_to_fit();

    /** Vector modifiers */
    // void clear();
    // iterator insert(iterator pos, const_reference value);
    // void erase(iterator pos);
    // void push_back(const_reference value);
    // void pop_back();
    // void swap(vector& other);
};

template <typename value_type>
vector<value_type>::vector() : data(nullptr), capacity(0), size(0) {}

template <typename value_type>
vector<value_type>::~vector() {
    delete[] data;
    this->capacity = 0;
    this->size = 0;
}

template <typename value_type>
vector<value_type>::vector(size_type n) {
    if (n < 0) {
        throw std::invalid_argument("Size cannot be negative");
    }
    resize(n); 
    for (size_t i = 0; i < n; ++i) {
        data[i] = value_type(); 
    }
    size = n; // Устанавливаем текущий размер
}

template <typename value_type>
vector<value_type>::vector(std::initializer_list<value_type> const &items) {
    size = items.size();
    resize(size);
    size_t index = 0;
    for (const auto& item : items) {
        data[index++] = item; 
    }
}

int main() {
    vector<int> vec;
    vector<int> vec1(5);
    vector<int> vec2 = {1, 2, 3, 4};

    // vec.push_back(1);
    // vec.push_back(2);
    // vec.push_back(3);

    // for (size_t i = 0; i < vec.size(); ++i) {
    //     std::cout << vec[i] << " ";
    // }
    // std::cout << std::endl;

    // vec.pop_back();

    // for (size_t i = 0; i < vec.getSize(); ++i) {
    //     std::cout << vec[i] << " ";
    // }
    // std::cout << std::endl;

    return 0;
}

