//
// Created by dennis gega on 7/8/25.
//

#ifndef VECTOR_H
#define VECTOR_H
#include <optional>
#include <stdexcept>

template<typename T>
class Vector {
public:
    Vector(int capacity);
    ~Vector();
    [[nodiscard]] int size() const { return m_size; };
    [[nodiscard]] int capacity() const { return m_capacity; };
    [[nodiscard]] bool is_empty() const { return m_size == 0; };
    T at(int index) const;
    void push(T item);
    void insert(int index, T item);
    void prepend(T item);
    T pop();
    void remove(int index);

    std::optional<T> find(T item);


private:
    T m_array[16];
    int m_size = 0;
    int m_capacity = 16;
    void resize(int new_capacity);
};

template<typename T>
T Vector<T>::at(int index) const {
    if (index > 0 && index < m_capacity) {
        return m_array[index];
    } else {
        throw std::out_of_range("Error: index out of range\n");
    }
}

template<typename T>
void Vector<T>::push(T item) {
    m_size++;
    if (m_size == m_capacity) {
        resize(m_capacity * m_capacity);
    }
    m_array[m_size] = item;
}

template<typename T>
void Vector<T>::insert(int index, T item) {
    if (index > 0 && index < m_capacity) {
        m_size++;
        if (m_size == m_capacity) {
            resize(m_capacity * m_capacity);
        }
        T tmp = m_array[index];
        m_array[index] = item;
        for (int i = index; i <= m_size; i++) {
            T curr = m_array[i];
            m_array[i] = tmp;
            tmp = curr;
        }
    } else {
        throw std::out_of_range("Error: index out of range\n");
    }
}

template<typename T>
void Vector<T>::prepend(T item) {
    insert(0, item);
}

template<typename T>
T Vector<T>::pop() {
    if (m_size == 0) {
        throw std::out_of_range("Error: vector empty\n");
    }
    T value = m_array[m_size--];
    if (m_size <= m_capacity / 4) {
        resize(m_capacity / 2);
    }
}

template<typename T>
void Vector<T>::remove(int index) {
    if (m_size == 0) {
        throw std::out_of_range("Error: vector empty\n");
    } else if (index >= m_size) {
        throw std::out_of_range("Error: index out of range\n");
    }
    T tmp = m_array[index + 1];
    for (int i = index; i < m_size; i++) {
        m_array[i] = tmp;
        tmp = m_array[i + 1];
    }
    m_size--;
    if (m_size <= m_capacity / 4) {
        resize(m_capacity / 2);
    }
}

template<typename T>
std::optional<T> Vector<T>::find(T item) {
    for (int i = 0; i < m_size; i++) {
        if (m_array[i] == item) {
            return m_array[i];
        }
    }
    return std::nullopt;
}

template<typename T>
void Vector<T>::resize(const int new_capacity) {
    T new_array[new_capacity];

    int num_items = std::min(m_size, new_capacity);
    for (int i = 0; i < num_items; i++) {
        new_array[i] = m_array[i];
    }
    delete[] m_array;

    m_array = new_array;
    m_capacity = new_capacity;
}

template<typename T>
Vector<T>::Vector(int capacity = 16) : m_size(0), m_capacity(16) {
    while (m_capacity * 2 < capacity) {
        m_capacity *= 2;
    }
    m_array = new T[m_capacity];
}

template<typename T>
Vector<T>::~Vector() {
    delete[] m_array;
}


#endif //VECTOR_H
