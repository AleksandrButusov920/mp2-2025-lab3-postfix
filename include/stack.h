#ifndef STACK_H
#define STACK_H

#include <stdexcept>

template <typename T>
class Stack {
private:
    T* data;
    int capacity;
    int topIndex;

    void resize() {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        for (int i = 0; i <= topIndex; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Stack(int initialCapacity = 10) : capacity(initialCapacity), topIndex(-1) {
        data = new T[capacity];
    }

    ~Stack() {
        delete[] data;
    }

    Stack(const Stack& other) : capacity(other.capacity), topIndex(other.topIndex) {
        data = new T[capacity];
        for (int i = 0; i <= topIndex; i++) {
            data[i] = other.data[i];
        }
    }

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            topIndex = other.topIndex;
            data = new T[capacity];
            for (int i = 0; i <= topIndex; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    void push(const T& value) {
        if (topIndex + 1 >= capacity) {
            resize();
        }
        data[++topIndex] = value;
    }

    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return data[topIndex--];
    }

    T top() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return data[topIndex];
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    int size() const {
        return topIndex + 1;
    }

    void clear() {
        topIndex = -1;
    }
};

#endif // STACK_H