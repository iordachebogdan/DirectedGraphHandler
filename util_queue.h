//
// Created by Bogdan Iordache on 3/6/2018.
//

#ifndef DIRECTEDGRAPHHANDLER_UTIL_QUEUE_H
#define DIRECTEDGRAPHHANDLER_UTIL_QUEUE_H

#include "util_stack.h"

namespace util {

    //implementation of queue using util::Stack
    template<typename T>
    class Queue {
      public:
        //constructors
        Queue();
        Queue(const Queue& rhs);

        //assignment operator
        Queue& operator = (const Queue& rhs);

        //destructor
        virtual ~Queue();

        //method that returns the size of the queue
        size_t size() const;

        //method that returns true if the queue is empty
        bool empty() const;

        //methods for accessing the front of the queue
        T& front();
        const T& front() const;

        //method to push an element into the queue
        void push(const T& value);

        //method to erase the front of the queue
        void pop();

        //method that erases all elements from the queue
        void clear();
      private:
        mutable Stack<T> s1_, s2_;
        void flush() const;
    };

    template <typename T>
    Queue<T>::Queue() {}

    template <typename T>
    Queue<T>::Queue(const Queue &rhs) {
        s1_ = rhs.s1_;
        s2_ = rhs.s2_;
    }

    template <typename T>
    Queue<T>& Queue<T>::operator=(const Queue &rhs) {
        s1_ = rhs.s1_;
        s2_ = rhs.s2_;
        return (*this);
    }

    template <typename T>
    Queue<T>::~Queue() {}

    template <typename T>
    size_t Queue<T>::size() const {
        return s1_.size() + s2_.size();
    }

    template<typename T>
    bool Queue<T>::empty() const {
        return (size() == 0);
    }

    template<typename T>
    const T& Queue<T>::front() const {
        flush();
        return s1_.top();
    }

    template<typename T>
    T& Queue<T>::front() {
        flush();
        return s1_.top();
    }

    template<typename T>
    void Queue<T>::push(const T &value) {
        s2_.push(value);
    }

    template<typename T>
    void Queue<T>::pop() {
        flush();
        s1_.pop();
    }

    template<typename T>
    void Queue<T>::clear() {
        s1_.clear();
        s2_.clear();
    }

    template<typename T>
    void Queue<T>::flush() const {
        if (!s1_.empty())
            return;
        while (!s2_.empty()) {
            s1_.push(s2_.top());
            s2_.pop();
        }
    }

}

#endif //DIRECTEDGRAPHHANDLER_UTIL_QUEUE_H
