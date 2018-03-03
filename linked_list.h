//
// Created by Bogdan Iordache on 3/3/2018.
//

#ifndef DIRECTEDGRAPHHANDLER_LINKED_LIST_H
#define DIRECTEDGRAPHHANDLER_LINKED_LIST_H

#include <exception>
#include <cstdlib>

namespace linked_list {

    template<typename T>
    class LinkedList {
      private:
        class LinkedListNode;

      public:
        class iterator {
          public:
            iterator(LinkedListNode* ptr);
            iterator operator++();
            T& operator*();
            T* operator->();
            bool operator == (const iterator& other);
            bool operator != (const iterator& other);
          private:
            LinkedListNode* ptr_;
        };

        LinkedList();
        ~LinkedList();
        LinkedList(const LinkedList& other);
        LinkedList& operator = (const LinkedList& other);

        bool empty() const;
        void push_back(const T& x);
        void clear();
        iterator begin() const;
        iterator end() const;
        T& front();
        T& back();
      private:
        LinkedListNode *first_, *last_;

        class LinkedListNode {
          public:
            LinkedListNode();
            LinkedListNode(const LinkedListNode& other);
            LinkedListNode& operator = (const LinkedListNode& other);

            T data;
            LinkedListNode* next;
        };
    };

    template<typename T>
    LinkedList<T>::LinkedListNode::LinkedListNode() : next(NULL) {}

    template <typename T>
    LinkedList<T>::LinkedListNode::LinkedListNode(const LinkedList<T>::LinkedListNode &other) {
        data = other.data;
        next = other.next;
    }

    template<typename T>
    typename LinkedList<T>::LinkedListNode& LinkedList<T>::LinkedListNode::operator=(
            const LinkedList<T>::LinkedListNode &other) {
        data = other.data;
        next = other.next;
    }

    template<typename T>
    LinkedList<T>::iterator::iterator(LinkedListNode *ptr) : ptr_(ptr) {}

    template<typename T>
    typename LinkedList<T>::iterator LinkedList<T>::iterator::operator++() {
        if (ptr_ != NULL)
            ptr_ = ptr_->next;
        return iterator(ptr_);
    }

    template<typename T>
    T& LinkedList<T>::iterator::operator*() {
        return ptr_->data;
    }

    template<typename T>
    T* LinkedList<T>::iterator::operator->() {
        return &(ptr_->data);
    }

    template<typename  T>
    bool LinkedList<T>::iterator::operator==(const iterator &other) {
        return ptr_ == other.ptr_;
    }

    template<typename  T>
    bool LinkedList<T>::iterator::operator!=(const iterator &other) {
        return ptr_ != other.ptr_;
    }

    template<typename T>
    LinkedList<T>::LinkedList() : first_(NULL), last_(NULL) {}

    template<typename T>
    LinkedList<T>::~LinkedList() {
        clear();
    }

    template<typename T>
    LinkedList<T>::LinkedList(const LinkedList<T>& other) {
        if (other.empty())
            (*this) = LinkedList();
        else {
            (*this) = LinkedList();
            for (LinkedList<T>::iterator it = other.begin(); it != other.end(); ++it)
                push_back(*it);
        }
    }

    template<typename T>
    LinkedList<T>& LinkedList<T>::operator=(const LinkedList &other) {
        clear();
        (*this) = LinkedList();
        for (LinkedList<T>::iterator it = other.begin(); it != other.end(); ++it)
            push_back(*it);
    }

    template<typename T>
    bool LinkedList<T>::empty() const {
        return first_ == NULL;
    }

    template<typename T>
    void LinkedList<T>::push_back(const T &x) {
        if (first_ == NULL) {
            first_ = last_ = new LinkedListNode();
            first_->data = x;
        }
        else {
            LinkedListNode* new_last = new LinkedListNode();
            new_last->data = x;
            last_->next = new_last;
            last_ = new_last;
        }
    }

    template<typename T>
    void LinkedList<T>::clear() {
        while (first_ != NULL) {
            LinkedListNode* temp = first_;
            first_ = first_->next;
            delete temp;
        }
        last_ = NULL;
    }

    template<typename T>
    typename LinkedList<T>::iterator LinkedList<T>::begin() const {
        return iterator(first_);
    }

    template<typename T>
    typename LinkedList<T>::iterator LinkedList<T>::end() const {
        return iterator(NULL);
    }

    template<typename T>
    T& LinkedList<T>::front() {
        return first_->data;
    }

    template<typename T>
    T& LinkedList<T>::back() {
        return last_->data;
    }

}

#endif //DIRECTEDGRAPHHANDLER_LINKED_LIST_H
