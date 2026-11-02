#pragma once

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>

class StackEmptyError : public std::runtime_error {
public:
    StackEmptyError() : std::runtime_error("Stack is empty") {}
};

template <typename T> 
class Stack {
public:
    Stack() {
        stack = new T[INIT_SIZE];
        size = INIT_SIZE;
        count = 0;
    }

    ~Stack() {
        delete[] stack;
    }

    // Copy constructor 
    Stack(const Stack& other) 
        : stack(new T[other.size]), size(other.size), count(other.count) 
    {
        try {
            std::copy(other.stack, other.stack + other.count, stack);
        }
        catch (...) {
            delete[] stack;
            throw;
        }
    }

    // Move constructor
    Stack(Stack&& other) noexcept 
        : stack(other.stack), size(other.size), count(other.count) 
    {
        other.stack = nullptr;
        other.size = other.count = 0;
    }

    bool empty() const {
        return count == 0;
    }

    bool full() const {
        return count == size;
    }

    void push(const T& value) {
        if (full()) {
            extend();
        }
        stack[count] = value;
        count++;
    }

    T pop() {
        T headvalue = std::move(head());
        --count;
        return headvalue;
    }

    T& head() {
        if (empty()) {
            throw StackEmptyError();
        }
        return stack[count - 1];
    }

    const T& head() const {
        if (empty()) {
            throw StackEmptyError();
        }
        return stack[count - 1];
    }

private:
    static constexpr size_t INIT_SIZE = 8;

    void extend() {
        size = size << 1;
        T* new_stack = new T[size];

        try {
            std::copy(stack, stack + count, new_stack);
        }
        catch (...) {
            delete[] new_stack;
            size /= 2;
            throw;
        }

        delete[] stack;
        stack = new_stack;
    }
    size_t size;
    size_t count;
    T* stack;
};