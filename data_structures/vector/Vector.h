//
// Created by dennis gega on 7/8/25.
//

#ifndef VECTOR_H
#define VECTOR_H
#include <optional>
#include <stdexcept>

/**
 * @brief A dynamic array implementation with amortized constant time insertion/deletion at its end
 * and constant time insertion/deletion elsewhere. Allocates space for at least 16 items.
 */
template<typename T>
class Vector {
public:
    explicit Vector(int capacity);
    ~Vector();

    /**
     * @brief Gets size of vector.
     * @return return number of items stored in vector.
     */
    [[nodiscard]] int size() const { return m_size; };

    /**
     * @brief Gets capacity of vector.
     * @return return number of items that can be stored currently in vector.
     */
    [[nodiscard]] int capacity() const { return m_capacity; };

    /**
     * @brief Checks if vector is empty.
     * @return return true number of items stored in vector is nonzero, returns false otherwise.
     */
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

/**
 * @brief Gets the item stored at index in vector.
 * @param index The index of the selected item.
 * @return The item at the selected index, if the index is out of range an error is thrown.
 */
template<typename T>
T Vector<T>::at(int index) const {
    if (index > 0 && index < m_capacity) {
        return m_array[index];
    } else {
        throw std::out_of_range("Error: index out of range\n");
    }
}

/**
 * @brief Insert item at the end of vector.
 * @param item Item to be appended to end of vector.
 */
template<typename T>
void Vector<T>::push(T item) {
    m_size++;
    if (m_size == m_capacity) {
        resize(m_capacity * m_capacity);
    }
    m_array[m_size] = item;
}

/**
 * @brief Insert item at index in vector, shift all following items to the right in memory.
 * @param index The index where the new item will be inserted.
 * @param item The item to be inserted into the vector.
 */
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

/**
 * @brief Insert item at beginning of vector, insert wrapper.
 * @param item The item to be inserted at the beginning of the vector.
 */
template<typename T>
void Vector<T>::prepend(T item) {
    insert(0, item);
}

/**
 * @brief Remove last item from vector.
 * @return The item that has just been removed.
 */
template<typename T>
T Vector<T>::pop() {
    if (m_size == 0) {
        throw std::out_of_range("Error: vector empty\n");
    }
    T value = m_array[m_size--];
    if (m_size <= m_capacity / 4) {
        resize(m_capacity / 2);
    }
    return value;
}

/**
 * @brief Remove item in index of vector.
 * @param index The index of the item to be removed.
 */
template<typename T>
void Vector<T>::remove(const int index) {
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

/**
 * @brief Look for item in vector and return it if present.
 * @param item The item to look for.
 * @return Item in vector if found, std::nullopt if item is not in vector.
 */
template<typename T>
std::optional<T> Vector<T>::find(T item) {
    for (int i = 0; i < m_size; i++) {
        if (m_array[i] == item) {
            return m_array[i];
        }
    }
    return std::nullopt;
}

/**
 * @brief Copy contents of m_array into an array of size new_capacity, then set new array to m_array.
 * @param new_capacity The size of the new array.
 */
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

    /**
     * @brief Create a vector of minimum size 16.
     * @param capacity Initial capacity of vector
     */
template<typename T>
Vector<T>::Vector(const int capacity) : m_size(0), m_capacity(16) {
    while (m_capacity * 2 < capacity) {
        m_capacity *= 2;
    }
    m_array = new T[m_capacity];
}

/**
 * @brief Delete instance of vector from memory.
 */
template<typename T>
Vector<T>::~Vector() {
    delete[] m_array;
}


#endif //VECTOR_H
