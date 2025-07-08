//
// Created by dennis gega on 7/8/25.
//

#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>

template<typename T>
class Vector {
public:
    Vector();
    [[nodiscard]] int size() const { return m_size; };
    [[nodiscard]] int capacity() const { return m_capacity; };
    [[nodiscard]] bool is_empty() const { return m_size == 0; };
    T at(int index) const;
    void push(T item);
    void insert(int index, T item);
    void prepend(T item);
    T pop();
    T remove(int index);
    T find(T item);


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




#endif //VECTOR_H
