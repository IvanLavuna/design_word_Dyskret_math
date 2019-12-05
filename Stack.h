//
// Created by ivan on 18.11.19.
//
// STACK
//
#ifndef DATA_STRUCTURES_STACK_H
#define DATA_STRUCTURES_STACK_H

#include "List.h"
#include <cassert>
#include <initializer_list>

#define MAX_SIZE 20000

namespace STACKspace
{
    template<class T>
    class Stack
    {
    private:
        List<T> m_stack;

        int m_size;

    public:
        Stack(): m_size(0) { }

        Stack(std::initializer_list<T> list);

        ~Stack();

        Stack& push(T data);

        Stack& pop();

        T top();

        int size(){ return m_size; }

        bool empty(){return m_size == 0;}
    };
}

using namespace STACKspace;

template<class T>
Stack<T>::~Stack()
{
    while(m_size!=0)
    {
        pop();
    }
}

template<class T>
Stack<T>::Stack(std::initializer_list<T> list) : Stack<T>::Stack()
{
    for(auto i = list.begin();i!=list.end();i++)
    {
        push(*i);
    }
}

template <class T>
Stack<T>& Stack<T>::push(T data)
{
    assert(m_size < MAX_SIZE && "STACK IS OVERLOADED");
    m_stack.push_back(data);
    m_size++;
}

template <class T>
Stack<T>& Stack<T>::pop()
{
    assert(m_size>0);
    m_stack.remove_last();
    m_size--;
}

template<class T>
T Stack<T>::top()
{
    assert(m_size > 0);

    return *(m_stack.mend());
}

#endif //DATA_STRUCTURES_STACK_H




