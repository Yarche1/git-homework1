#include "SmartArray.hpp"

// Стек (LIFO)
template <typename T>
class Stack {
private:
    SmartArray<T> data;

public:
    void push(const T& value) { data.PushBack(value); }
    void pop() { 
        if (!data.Empty()) data.PopBack(); 
    }
    T& top() { return data.Back(); }
    bool empty() const { return data.Empty(); }
    size_t size() const { return data.Size(); }
};

// Очередь (FIFO)
template <typename T>
class Queue {
private:
    SmartArray<T> data;

public:
    void push(const T& value) { data.PushBack(value); }
    void pop() { 
        if (!data.Empty()) data.RemoveAt(0); 
    }
    T& front() { return data.Front(); }
    bool empty() const { return data.Empty(); }
    size_t size() const { return data.Size(); }
};
