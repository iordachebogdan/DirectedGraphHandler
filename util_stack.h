//
// Created by Bogdan Iordache on 3/5/2018.
//

#ifndef DIRECTEDGRAPHHANDLER_UTIL_STACK_H
#define DIRECTEDGRAPHHANDLER_UTIL_STACK_H

#include "util_vector.h"

namespace util {

    //implementation of stack using util::Vector
    template<typename T>
    class Stack : protected Vector<T> {
      public:
        //constructors
        Stack();
        Stack(const Stack& rhs);

        //assignment operator
        Stack& operator = (const Stack& rhs);

        //destructor
        virtual ~Stack();

        //method that returns the size of the stack
        size_t size() const;

        //method that returns true if the stack is empty
        bool empty() const;

        //methods for accessing the top of the stack
        T& top();
        const T& top() const;

        //method to push an element into the stack
        void push(const T& value);

        //method to erase the top of the stack
        void pop();

        //method that erases all elements from the stack
        void clear();
    };

    template<typename T>
    Stack<T>::Stack() : Vector<T>() {}

    template<typename T>
    Stack<T>::Stack(const Stack& rhs) : Vector<T>(rhs) {}

    template<typename T>
    Stack<T>& Stack<T>::operator = (const Stack &rhs) {
        Vector<T>::operator=(rhs);
        return (*this);
    }

    template<typename T>
    Stack<T>::~Stack() {
        Vector<T>::~Vector();
    }

    template<typename T>
    size_t Stack<T>::size() const {
        return Vector<T>::size();
    }

    template<typename T>
    bool Stack<T>::empty() const {
        return Vector<T>::empty();
    }

    template<typename T>
    const T& Stack<T>::top() const {
        return Vector<T>::front();
    }

    template<typename T>
    T& Stack<T>::top() {
        return Vector<T>::back();
    }

    template<typename T>
    void Stack<T>::push(const T &value) {
        Vector<T>::push_back(value);
    }

    template<typename T>
    void Stack<T>::pop() {
        Vector<T>::pop_back();
    }

    template<typename T>
    void Stack<T>::clear() {
        Vector<T>::clear();
    }
}

#endif //DIRECTEDGRAPHHANDLER_UTIL_STACK_H
