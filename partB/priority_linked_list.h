//#ifndef PRIORITY_LINKED_LIST_H_
//#define PRIORITY_LINKED_LIST_H_
#pragma once

#include <iostream>
#include "date_wrap.h"
#include <string>

using mtm::DateWrap;
using std::string;


template<class T, class S>
class Node {
public:
    Node(const T& t_element, const S& s_priority);
    ~Node();

    T element;
    S priority;
    Node* next;
};


template <class T, class S>
class PriorityLinkedList {
private:
    Node<T, S>* head;
    int size;

public:
    PriorityLinkedList<T, S>() : size(0) { head = NULL; }
    ~PriorityLinkedList();
    void insert(const T& t_element, const S& s_priority);
    void deleteNodeByElement(const T& t_element);
    bool isElementInLinkedList(const T& t_element);
    int getSize() const;
};



template<class T, class S>
inline Node<T, S>::Node(const T& t_element, const S& s_priority) : element(t_element), priority(s_priority) {}

template<class T, class S>
inline Node<T, S>::~Node()
{
    //delete[] element;
    //delete[] priority;
}

/*
template<class T, class S>
inline PriorityLinkedList<T, S>::PriorityLinkedList() : size(0)
{
    head = NULL;
}
*/
template<class T, class S>
inline PriorityLinkedList<T, S>::~PriorityLinkedList()
{
    Node<T, S>* ptr = head;
    while (ptr != NULL) {
        Node<T, S>* to_delete = ptr;
        ptr = ptr->next;
        to_delete->~Node();
    }
}

template<class T, class S>
inline void PriorityLinkedList<T, S>::insert(const T& t_element, const S& s_priority)
{
    Node<T, S> *node_to_add = new Node<T, S>(t_element, s_priority);
    node_to_add->next = NULL;
    
    if (!head) {
        head = node_to_add;
    }
    else if (head->priority > s_priority) {
        node_to_add->next = head;
        head = node_to_add;
    }
    else {
        while (head->next != NULL && head->next->priority <= s_priority) {
            head = head->next;
        }
        // add the node between the current node and the next of it
        if (head->next) {
            Node<T, S> *temp = head->next;
            head->next = node_to_add;
            node_to_add->next = temp;
        }
        else {
            head->next = node_to_add;
        }
    }
    size++;
}

template<class T, class S>
inline void PriorityLinkedList<T, S>::deleteNodeByElement(const T& t_element)
{
    if (head->element == t_element) {
        Node<T, S>* to_delete = head;
        head = to_delete->next;
        size--;
        to_delete->~Node();
    }
    Node<S, T>* current_node = head;
    Node<S, T>* previous_node = current_node;
    while (current_node->element != t_element) {
        previous_node = current_node;
        current_node = current_node->next;
    }

    if (current_node->next) {
        Node<S, T>* next_current_node_temp = current_node->next;
        previous_node->next = next_current_node_temp;
        current_node->~Node();
    }
    else {
        current_node->~Node();
        previous_node->next = NULL;
    }
    size--;
}

template<class T, class S>
inline bool PriorityLinkedList<T, S>::isElementInLinkedList(const T& t_element)
{
    for (Node<S, T>* ptr = head; ptr != NULL; ptr = ptr->next) {
        if (head->element == t_element) {
            return true;
        }
    }
    return false;
}

template<class T, class S>
inline int PriorityLinkedList<T, S>::getSize() const
{
    return size;
}

//#endif //PRIORITY_LINKED_LIST_H_
