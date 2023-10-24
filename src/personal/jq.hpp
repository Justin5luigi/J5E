#pragma once

#include <vector>
#include <queue>

template <typename T>
class JQ 
{
    private:
        std::queue<T> jqueue;
    public:
        void Enqueue(T item) { jqueue.push(item); }
        
        T& Dequeue() 
        {
            T& itemToReturn = jqueue.front();
            jqueue.pop();
            return itemToReturn;
        }

        bool IsEmpty() { return jqueue.empty(); }

        T& PeekFront() { return jqueue.front(); }

};

