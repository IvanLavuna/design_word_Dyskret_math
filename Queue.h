//
// Created by ivan on 18.11.19.
//
// QUEUE
//

#ifndef DATA_STRUCTURES_QUEUE_H
#define DATA_STRUCTURES_QUEUE_H

#include <cassert>
#include <initializer_list>
#include "List.h"

#define MAX_SIZE 20000

namespace QUEUEspace
{
    template<class T>
    class Queue
    {
    private:
        LISTspace::List<T> m_queue;

        int m_size;

    public:
        Queue() : m_size(0) {};

        Queue(std::initializer_list<T> list);

        ~Queue();

        Queue& push(T data);

        Queue& pop();

        T front();

        int size() {return m_size;}

        bool empty(){return m_size == 0;}

        Queue& erase();

    };
}


using namespace QUEUEspace;

template<class T>
Queue<T>::Queue(std::initializer_list<T> list) : Queue<T>::Queue()
{
    for(auto i = list.begin();i<list.end();i++)
    {
        push(*i);
    }
}

template<class T>
Queue<T>::~Queue()
{
    while(m_size!=0)
    {
        pop();
    }
}

template <class T>
Queue<T>& Queue<T>::push(T data)
{
    assert(m_size < MAX_SIZE && "QUEUE IS OVERLOADED");
    m_queue.push_back(data);
    m_size++;
}

template <class T>
Queue<T>& Queue<T>::pop()
{
    assert(m_size > 0);
    m_queue.remove_first();
    m_size--;
}

template <class T>
T Queue<T>::front()
{
    assert(m_size > 0);

    return *(m_queue.begin());
}

template<class T>
Queue<T>& Queue<T>::erase()
{
    while(m_size!=0)
    {
        pop();
    }
}

#endif //DATA_STRUCTURES_QUEUE_H
